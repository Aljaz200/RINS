 
import os

output_folder = "text_files"
os.makedirs(output_folder, exist_ok=True)

for i in range(1, 1005):
    filename = os.path.join(output_folder, f"fakering{i}.txt")
    with open(filename, "w") as file:
        file.write("0 0.5 0.5 1 1")

print("Files generated successfully!")
