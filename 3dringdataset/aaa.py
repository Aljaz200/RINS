 
import shutil
import os

def duplicate_images(input_images, output_folder, num_images=97):
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    image_count = 4  # Starting from fakering4

    # Loop through the images and copy them
    for i in range(num_images):
        image_index = i % len(input_images)  # To cycle through the 3 images
        image_path = input_images[image_index]
        new_name = f'fakering{image_count}.png'
        new_path = os.path.join(output_folder, new_name)

        shutil.copy(image_path, new_path)
        image_count += 1

    print(f"Images duplicated and saved in '{output_folder}'")

# Example usage
input_images = [
    "/home/tau/colcon_ws/3dringdataset/images/train/fakering1.png",  # Replace with your actual image paths
    "/home/tau/colcon_ws/3dringdataset/images/train/fakering2.png",
    "/home/tau/colcon_ws/3dringdataset/images/train/fakering3.png"
]

output_folder = "dataset"  # Folder where duplicated images will be saved
duplicate_images(input_images, output_folder)
