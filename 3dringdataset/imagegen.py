import cv2
import numpy as np
import os
from PIL import Image, ImageEnhance, ImageOps
import random

def remove_black_color(image_path, output_path):
    # Open image
    image = Image.open(image_path).convert("RGBA")

    # Convert image to numpy array
    image_array = np.array(image)

    # Create a mask for black color (or near-black)
    black_mask = (image_array[:, :, :3] == [0, 0, 0]).all(axis=2)

    # Set black pixels to transparent (alpha = 0)
    image_array[black_mask] = [0, 0, 0, 0]

    # Convert back to image
    result_image = Image.fromarray(image_array, "RGBA")

    # Save the result
    result_image.save(output_path, "PNG")


def augment_image(image):
    # Convert to PIL for transformations
    pil_img = Image.fromarray(image).convert("RGBA")

    # Random perspective transformation
    width, height = pil_img.size
    src_pts = np.float32([
        [random.randint(0, width // 4), random.randint(0, height // 4)],
        [random.randint(3 * width // 4, width), random.randint(0, height // 4)],
        [random.randint(0, width // 4), random.randint(3 * height // 4, height)],
        [random.randint(3 * width // 4, width), random.randint(3 * height // 4, height)]
    ])
    dst_pts = np.float32([
        [0, 0], [width, 0], [0, height], [width, height]
    ])
    matrix = cv2.getPerspectiveTransform(src_pts, dst_pts)
    image = cv2.warpPerspective(np.array(pil_img), matrix, (width, height), borderMode=cv2.BORDER_CONSTANT, borderValue=(0, 0, 0, 0))
    pil_img = Image.fromarray(image, "RGBA")

    # Random rotation
    angle = random.randint(-30, 30)
    pil_img = pil_img.rotate(angle, expand=True)

    # Random flipping
    if random.random() > 0.5:
        pil_img = pil_img.transpose(Image.FLIP_LEFT_RIGHT)
    if random.random() > 0.5:
        pil_img = pil_img.transpose(Image.FLIP_TOP_BOTTOM)

    # Convert back to numpy array
    image = np.array(pil_img)

    # Create a mask for black color (or near-black)
    black_mask = (image[:, :, :3] == [0, 0, 0]).all(axis=2)

    # Set black pixels to transparent (alpha = 0)
    image[black_mask] = [0, 0, 0, 0]

    return Image.fromarray(image, "RGBA")

def generate_dataset(input_images, output_folder, num_images=1000):
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    for i in range(num_images):
        base_image = Image.open(random.choice(input_images)).convert("RGBA")
        augmented_image = augment_image(np.array(base_image))
        output_path = os.path.join(output_folder, f'fakering{i+4}.png')
        augmented_image.save(output_path, "PNG")

    print(f"Dataset generated with {num_images} images in '{output_folder}'")


# Example usage
input_images = ["/home/tau/colcon_ws/3dringdataset/images/train/fakering1.png", "/home/tau/colcon_ws/3dringdataset/images/train/fakering2.png", "/home/tau/colcon_ws/3dringdataset/images/train/fakering3.png"]  # Replace with your actual file paths
output_folder = "dataset"
generate_dataset(input_images, output_folder)
