import cv2 as cv
import os
from time import sleep
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

ser = serial.Serial('COM5', 9600)
opening = False

while(True):
    sleep(2)
    
    screenshot = wincap.get_screenshot()

    if vision.checkMsgOnScreen(screenshot[229:280, 415:612], 'first_message'):
        print('checagem de captcha!')
        print('lock and two enters')
        ser.write(bytes('lee', encoding='utf-8'))
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

        print('unlock')
        ser.write(bytes('u', encoding='utf-8')) # unlock
    elif vision.checkMsgOnScreen(screenshot[113:126, 23:42], 'weight', threshold=0.8):
        print('inventario cheio? confirmando...') 
        sleep(2)
        screenshot = wincap.get_screenshot()
        if not vision.checkMsgOnScreen(screenshot[113:126, 23:42], 'weight', threshold=0.8):
            continue
        print('inventario cheio!')
        if opening: # se estiver abrindo caixas manda parar
            print('parando de abrir caixas')
            ser.write(bytes('b', encoding='utf-8')) # boxes
            opening = False
        ser.write(bytes('s', encoding='utf-8')) # storage
        sleep(20)
        print('terminou de guardar itens!')
    elif not opening and vision.checkMsgOnScreen(screenshot[19:30, 297:305], 'two_box'):
        print('abrindo caixas!')
        ser.write(bytes('b', encoding='utf-8')) # boxes
        opening = True
    elif opening and not (vision.checkMsgOnScreen(screenshot[19:30, 297:305], 'one_box') or vision.checkMsgOnScreen(screenshot[19:30, 297:305], 'two_box')):
        print('parando de abrir caixas')
        ser.write(bytes('b', encoding='utf-8')) # boxes
        opening = False
    else:
        print('nothing...')



    if cv.waitKey(1) == ord('q'):
        cv.destroyAllWindows()
        break

print('Done.')
