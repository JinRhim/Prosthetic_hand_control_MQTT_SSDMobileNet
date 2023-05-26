"""
Written by Zhenyu Lin 
3/1/2023 

The program will convert the video into frame files 
You can choose how many images per fraom you want 
If you choose 1 frame per image, it will create lots of duplicate image
Choose 3 frame per image for static videos
Choose 1 frame per image for dynamic videos with lots of motions
"""

import cv2
import os
filename = input("Input file name: ")
frame_per_image = int(input("frame per image: "))
cap = cv2.VideoCapture(filename)
success, image = cap.read()
# Create a directory to store the frames
if not os.path.exists("frames"):
    os.makedirs("frames")

# Iterate over each frame of the video
frame_count = 0
while True:
    # Read the frame
    ret, frame = cap.read()
    # If there are no more frames, break the loop
    if not ret:
        break
    # Save the frame as an image
    if (frame_count % frame_per_image == 0):
        frame_path = os.path.join("frames", f"frame_{frame_count}.jpg")
        cv2.imwrite(frame_path, frame)
    # Increment the frame count
    frame_count += 1
# Release the VideoCapture object
cap.release()
