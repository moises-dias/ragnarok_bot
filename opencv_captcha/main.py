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
vision = Vision()

loop_time = time()

while(True):
    sleep(2)
    
    # get an updated image of the game
    screenshot = wincap.get_screenshot()

    if vision.checkMsgOnScreen(screenshot[135:190, 210:420], 'first_message'):
        print('checagem de captcha!')
        print('apertar enter')
    elif vision.checkMsgOnScreen(screenshot[323:338, 400:479], 'second_message'):
        print('numeros disponíveis para serem digitados')
        result = vision.findNumbers(screenshot[172:185, 237:261])
        print('enviar os numeros')
        print(result)
        sleep(3)

    if cv.waitKey(1) == ord('q'):
        cv.destroyAllWindows()
        break

print('Done.')
