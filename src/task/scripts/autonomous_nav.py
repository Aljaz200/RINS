#!/usr/bin/env python3

import cv2
import numpy as np
import os

DILATION = 5
DISTANCE_THRESHOLD = 5.0
PASSPIX_T = 0.6
CHUNK_SIZE = 30
PP = PASSPIX_T * (CHUNK_SIZE**2)

KERNEL = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (DILATION, DILATION))

#CHANGE
map_path = "/home/aljaz/Desktop/colcon_ws/src/task/maps/map.pgm"
print(map_path)
PGM_PIC = cv2.imread(map_path, cv2.IMREAD_GRAYSCALE)
if PGM_PIC is None:
    raise FileNotFoundError(f"Map image not found at: {map_path}")

#np.ones((DILATION, DILATION), dtype=np.uint8)

# steps for autonomous navigation
#
# 1. load and dilate map, split into equal windows, for every window with more than T1 threshold of white pixels,
# calculate the average position of a white pixel and check if it lands on a white pixel.
#
# 2. we now have an array of points. use A* to generate the visit order for optimal visiting

def compute_distance_transform(I):
    # Step 1: Read the grayscale image
    _, binary_image = cv2.threshold(I, 127, 255, cv2.THRESH_BINARY)
    distance_transform = cv2.distanceTransform(binary_image, cv2.DIST_L2, 5)
    return distance_transform

def split(I: np.ndarray):
    h, w = I.shape
    xx = w // CHUNK_SIZE
    #if w % CHUNK_SIZE != 0:
    #    xx += 1
    yy = h // CHUNK_SIZE
    #if h % CHUNK_SIZE != 0:
    #    yy += 1
    results = []
    for i in range(yy):
        for j in range(xx):
            jj = (j+1)*CHUNK_SIZE
            ii = (i+1)*CHUNK_SIZE
            if i == yy-1:
                ii += CHUNK_SIZE
            if j == xx-1:
                jj += CHUNK_SIZE
            part = I[(i*CHUNK_SIZE):ii, (j*CHUNK_SIZE):jj]
            results.append((part, (j*CHUNK_SIZE, i*CHUNK_SIZE)))
    return results

def calc_points(chunks, dt):
    pts = []
    for chunk in chunks:
        part = chunk[0]
        cy, cx = (part == 255).nonzero()
        if len(cx) < PP:
            continue
        coors = np.array([cx, cy]).T
        coor = np.average(coors, axis=0)
        p = np.round(coor).astype(np.int64)
        if part[p[1], p[0]] != 255:
            continue
        p += np.array(chunk[1])
        if dt[p[1], p[0]] >= DISTANCE_THRESHOLD:
            pts.append(p)
        else:
            print(f"[AUTONOMOUS NAV] ignoring point {p}, because it is too close to black point {dt[p[1], p[0]]} < {DISTANCE_THRESHOLD}")
    return np.array(pts)

def obtain_pixel_points_from_image(I = PGM_PIC):
    print(I.shape)
    print(I.dtype)
    img = I.copy().astype(np.uint8)
    img[img < 230] = 0
    img[img != 0] = 255
    img = cv2.bitwise_not(img)
    img = cv2.dilate(img, KERNEL, borderValue=1)
    img = cv2.bitwise_not(img)
    dt = compute_distance_transform(img)
    chunks = split(img)
    pts = calc_points(chunks, dt)
    img = cv2.cvtColor(img, cv2.COLOR_GRAY2RGB)
    for pt in pts:
        img[pt[1], pt[0]] = (255, 0, 0)
    #CHANGE
    map_path = "//home/aljaz/Desktop/colcon_ws/src/task/maps/temp.png"
    success = cv2.imwrite(map_path, img)
    print("Shranjevanje uspešno:", success)
    print("woah pts!", pts)
    return pts

def generate_path_greedy(start, pts: list):
    print("gen", pts)
    cur = start
    path = []
    while len(pts) > 0:
        m = float("inf")
        curpt = None
        for p in pts:
            diff = np.sum((np.array(cur) - np.array(p)) ** 2)
            if diff < m:
                m = diff
                curpt = p
        cur = curpt
        pts.remove(curpt)
        path.append(curpt)
    return path
