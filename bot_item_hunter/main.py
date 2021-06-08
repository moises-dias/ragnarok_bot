import cv2 as cv
import numpy as np
import os
from time import time, sleep
from windowcapture import WindowCapture
from vision import Vision
import serial

# Change the working directory to the folder this script is in.
# Doing this because I'll be putting the files from each video in their own folder on GitHub
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# initialize the WindowCapture class
wincap = WindowCapture('WorldRAG | Gepard Shield 3.0 (^-_-^)')

# initialize the Vision class
vision = Vision('poring_p.jpg')

loop_time = time()
ser = serial.Serial('COM6', 9600)
while(True):

    while not ser.in_waiting:
        pass
    _ = ser.readline()
    
    # get an updated image of the game
    screenshot = wincap.get_screenshot()

    # display the processed image
    points = vision.find(screenshot, 0.5, 'rectangles')
    
    if(len(points) > 0):
        print(f"poring identificado em: x={points[0][0]}, y={points[0][1]}")
        # send monster coordinate to arduino
        ser.write(bytes('t', encoding='utf-8'))
        sleep(0.02)
        ser.write(bytes(str(points[0][0]), encoding='utf-8'))
        sleep(0.02)
        ser.write(bytes(str(points[0][1]), encoding='utf-8'))
        sleep(0.02)
    else:
        # no monster found, tell arduino to look around
        ser.write(bytes('x', encoding='utf-8'))
        sleep(0.02)

    # press 'q' with the output window focused to exit.
    # waits 1 ms every loop to process key presses
    if cv.waitKey(1) == ord('q'):
        cv.destroyAllWindows()
        break

print('Done.')
