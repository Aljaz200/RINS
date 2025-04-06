import os
import cv2

class FaceSaver:
    def __init__(self, directory):
        self.directory = directory
        self.counter = 0
        if not os.path.exists(directory):
            os.makedirs(directory)

    def save(self, image, rect, prefix="", id=None):
        x, y, w, h = rect

        if id is None:
            counter = self.counter
        else:
            counter = id

        if prefix != "":
            prefix += "_"

        # Save original image
        original_image_path = os.path.join(self.directory, f'{prefix}image_{counter}.png')
        cv2.imwrite(original_image_path, image)

        # Draw rectangle on the image
        image_with_rect = image.copy()
        cv2.rectangle(image_with_rect, (x, y), (x + w, y + h), (0, 255, 0), 2)
        image_with_rect_path = os.path.join(self.directory, f'{prefix}image_rect_{counter}.png')
        cv2.imwrite(image_with_rect_path, image_with_rect)

        # Crop the image to the rectangle
        cropped_image = image[y:y+h, x:x+w]
        cropped_image_path = os.path.join(self.directory, f'{prefix}image_crop_{counter}.png')
        cv2.imwrite(cropped_image_path, cropped_image)

        # Increment counter for next image
        if id is None:
            self.counter += 1
