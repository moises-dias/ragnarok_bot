import cv2 as cv
import numpy as np
import os
from time import time, sleep
from windowcapture import WindowCapture
from vision import Vision
import serial

loop_time = time()
ser = serial.Serial('COM3', 9600)

# while(True):

sleep(1)
ser.write(bytes('off\n', encoding='utf-8'))
sleep(1)
ser.write(bytes('on\n', encoding='utf-8'))
sleep(1)
ser.write(bytes('off\n', encoding='utf-8'))
sleep(1)
ser.write(bytes('on\n', encoding='utf-8'))
sleep(1)
ser.write(bytes('off\n', encoding='utf-8'))
sleep(1)
ser.write(bytes('on\n', encoding='utf-8'))


print('Done.')
