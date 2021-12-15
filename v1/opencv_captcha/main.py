import cv2 as cv
import os
from time import sleep
from windowcapture import WindowCapture
from vision import Vision
import serial
from datetime import datetime

os.chdir(os.path.dirname(os.path.abspath(__file__)))

wincap = WindowCapture('WorldRAG | Gepard Shield 3.0 (^-_-^)')

vision = Vision()

ser = serial.Serial('COM5', 9600)
opening = False

with open("log.txt", "a") as myfile:
    myfile.write("starting at" + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
    print("starting at" + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))

while(True):
    sleep(1)
    
    screenshot = wincap.get_screenshot()

    if vision.checkMsgOnScreen(screenshot[229:280, 415:612], 'first_message'):
        with open("log.txt", "a") as myfile:
            myfile.write("captcha start at" + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            print("captcha start at" + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
        ser.write(bytes('cee', encoding='utf-8'))
        sleep(6)

        screenshot = wincap.get_screenshot()

        while not vision.checkMsgOnScreen(screenshot[320:341, 397:482], 'second_message'):
            print('enter')
            ser.write(bytes('e', encoding='utf-8'))
            sleep(1)
            screenshot = wincap.get_screenshot()

        while vision.checkMsgOnScreen(screenshot[320:341, 397:482], 'second_message'):
            result = vision.findNumbers(screenshot[266:279, 437:461])
            to_send = ''.join(result) + 'ee'
            print(to_send, 'three numbers and two enters')
            ser.write(bytes(to_send, encoding='utf-8'))
            sleep(5)
            screenshot = wincap.get_screenshot()

        print('finished')
        ser.write(bytes('f', encoding='utf-8')) # finished
    elif vision.checkMsgOnScreen(screenshot[113:126, 23:42], 'weight', threshold=0.8):
        print('inventario cheio? confirmando...') 
        sleep(3)
        screenshot = wincap.get_screenshot()
        if not vision.checkMsgOnScreen(screenshot[113:126, 23:42], 'weight', threshold=0.8):
            continue
        with open("log.txt", "a") as myfile:
            myfile.write("full inventory at" + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            print("full inventory at" + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
        ser.write(bytes('t', encoding='utf-8')) # storage
        sleep(20)
        print('terminou de guardar itens!')
    elif not opening and vision.checkMsgOnScreen(screenshot[19:30, 297:305], 'two_box'):
        with open("log.txt", "a") as myfile:
            myfile.write("opening boxes at" + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            print("opening boxes at" + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
        ser.write(bytes('b', encoding='utf-8')) # boxes
        opening = True
    elif opening and not (vision.checkMsgOnScreen(screenshot[19:30, 297:305], 'one_box') or vision.checkMsgOnScreen(screenshot[19:30, 297:305], 'two_box')):
        with open("log.txt", "a") as myfile:
            myfile.write("stop opening boxes at" + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
            print("stop opening boxes at" + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
        ser.write(bytes('b', encoding='utf-8')) # boxes
        opening = False
    # else:
    #     print('nothing...')



    if cv.waitKey(1) == ord('q'):
        cv.destroyAllWindows()
        break

print('Done.')
