import os
import shutil
from PIL import Image

# --- Paths ---
output_dir = "bird_dataset"
images_out = os.path.join(output_dir, "images")
labels_out = os.path.join(output_dir, "labels")
os.makedirs(images_out, exist_ok=True)
os.makedirs(labels_out, exist_ok=True)

# --- Load mapping files ---
with open("classes.txt", "r") as f:
    class_map = {line.split()[1]: i for i, line in enumerate(f)}

with open("images.txt", "r") as f:
    image_map = {int(line.split()[0]): line.strip().split()[1] for line in f}

with open("bounding_boxes.txt", "r") as f:
    bbox_map = {int(line.split()[0]): list(map(float, line.strip().split()[1:])) for line in f}

# --- Process each image ---
for idx, rel_img_path in image_map.items():
    bbox = bbox_map.get(idx)
    if bbox is None:
        continue  # skip if no bounding box

    # Full image path
    src_path = os.path.join("images", rel_img_path)  # assuming images/ is root
    if not os.path.exists(src_path):
        print(f"Missing image: {src_path}")
        continue

    # Open image to get width and height
    with Image.open(src_path) as img:
        width, height = img.size

    # Convert bbox from [x_min, y_min, x_max, y_max] to YOLO format
    x_cen, y_cen, x_wid, y_wid = bbox
    x_center = (x_cen) / width
    y_center = (y_cen) / height
    bbox_width = (x_wid) / width
    bbox_height = (y_wid) / height

    # Determine class id from folder name
    folder_name = rel_img_path.split('/')[0]
    class_id = class_map[folder_name]

    # Write YOLO label file
    image_name = os.path.basename(rel_img_path)
    label_name = os.path.splitext(image_name)[0] + ".txt"
    with open(os.path.join(labels_out, label_name), "w") as f:
        f.write(f"{class_id} {x_center:.6f} {y_center:.6f} {bbox_width:.6f} {bbox_height:.6f}\n")

    # Copy image
    shutil.copy(src_path, os.path.join(images_out, image_name))

# --- Create data.yaml ---
with open(os.path.join(output_dir, "data.yaml"), "w") as f:
    f.write(f"path: {os.path.abspath(output_dir)}\n")
    f.write(f"train: images\n")
    f.write(f"val: images\n")
    f.write("nc: 200\n")
    f.write("names: [")
    f.write(", ".join(f'"{name}"' for name in class_map))
    f.write("]\n")

print("✅ Conversion complete! You can now train YOLOv8 using this dataset.")

