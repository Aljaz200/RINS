import os
import pickle
import numpy as np
import cv2
import ailia
import sys
import logging

# Logger setup
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

# Add utils folder to path
# sys.path.append(os.path.join(os.path.dirname(__file__), 'utils'))

from padim_utils import preprocess, infer, normalize_scores, calculate_anormal_scores, visualize, denormalization, get_params
from detector_utils import load_image

class PADIMDetector:
    def __init__(self, arch='resnet18', threshold=0.7, image_resize=256, image_size=256 , keep_aspect=False, anomaly_threshold=17):
        self.ARCH = arch
        self.THRESHOLD = threshold
        self.IMAGE_RESIZE = image_resize
        self.IMAGE_SIZE = image_size
        self.KEEP_ASPECT = keep_aspect
        
        self.anomaly_threshold = anomaly_threshold
        
        self.net = None
        self.params = None
        self.train_outputs = None

    def setup_model(self, feat_file, model_url='https://storage.googleapis.com/ailia-models/padim/'):
        weight_path, model_path, self.params = get_params(self.ARCH)
        
        # Create net instance
        self.net = ailia.Net(model_path, weight_path, env_id=0)
        
        # Load train set features
        logger.info('Loading train set feature from: %s' % feat_file)        
        with open(feat_file, 'rb') as f:
            self.train_outputs = pickle.load(f)
        logger.info('Loaded.')

    def infer_single_image(self, image):
        # Check if image is a path or numpy array
        if isinstance(image, str):
            # Load and preprocess image from path
            img = load_image(image)
        elif isinstance(image, np.ndarray):
            # Use the provided numpy array image
            img = image
        else:
            raise ValueError("Invalid image type. Expected path or numpy array.")
        
        img = cv2.cvtColor(np.array(img), cv2.COLOR_BGR2RGB)
        img = preprocess(img, self.IMAGE_RESIZE, keep_aspect=self.KEEP_ASPECT, crop_size=self.IMAGE_SIZE)
        
        # Run inference
        dist_tmp = infer(self.net, self.params, self.train_outputs, img, self.IMAGE_SIZE)
        scores = normalize_scores([dist_tmp], self.IMAGE_SIZE)
        anormal_scores = calculate_anormal_scores([dist_tmp], self.IMAGE_SIZE)
        heat_map, mask, vis_img = visualize(denormalization(img[0]),  scores[0], "z_score")
        
        heat_map = cv2.normalize(heat_map, None, 0, 255, cv2.NORM_MINMAX)
        heat_map = np.uint8(heat_map)
        heat_map = cv2.applyColorMap(heat_map, cv2.COLORMAP_JET)
                
        print(anormal_scores)
        
        vis_img = vis_img.astype(np.float32)
        vis_img = cv2.cvtColor(vis_img, cv2.COLOR_RGB2BGR)

        # Display result with cv2
        if anormal_scores[0] > self.anomaly_threshold:
            cv2.imshow('Heat Map', heat_map.astype(np.uint8))
            cv2.imshow('Predicted Mask', mask.astype(np.uint8))
            cv2.imshow('Segmentation Result', vis_img)
            cv2.waitKey(0)
            cv2.destroyAllWindows()
        
        
        if anormal_scores[0] > self.anomaly_threshold:
            logger.info('Anomaly detected.')
            return vis_img, True
        else:
            logger.info('No anomaly detected.')
            return img, False

if __name__ == '__main__':
    # Parameters
    IMAGE_PATH = './mustache.png'
    FEAT_FILE = 'train.pkl'

    # Initialize and setup the detector
    detector = PADIMDetector()
    detector.setup_model(FEAT_FILE)

    # Inference on a single image
    detector.infer_single_image(IMAGE_PATH)
    logger.info('Script finished successfully.')