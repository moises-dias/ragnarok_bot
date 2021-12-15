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

ser = serial.Serial('COM3', 9600)
opening = False

def serial_send(msg):
    ser.write(bytes(msg, encoding='utf-8'))

def write_to_file(msg):
    with open("log.txt", "a") as myfile:
        myfile.writelines("\n " + msg + " started at " + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
        print(f"{msg} started at " + str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")))

write_to_file('init program')

while(True):
    sleep(1)
    
    screenshot = wincap.get_screenshot()

    if vision.checkMsgOnScreen(screenshot['first_message'], 'first_message'):
        write_to_file('captcha')
        serial_send('cee')
        sleep(6)

        screenshot = wincap.get_screenshot()

        while not vision.checkMsgOnScreen(screenshot['second_message'], 'second_message'):
            print('enter')
            serial_send('e')
            sleep(2)
            screenshot = wincap.get_screenshot()

        while vision.checkMsgOnScreen(screenshot['second_message'], 'second_message'):
            result = vision.findNumbers(screenshot['captcha_numbers'])
            to_send = ''.join(result) + 'ee'
            print(to_send, 'three numbers and two enters')
            serial_send(to_send)
            sleep(5)
            screenshot = wincap.get_screenshot()

        print('finished')
        serial_send('f')

    elif vision.checkMsgOnScreen(screenshot['ygg_hundreds'], '4', threshold=0.8) and not vision.checkMsgOnScreen(screenshot['ygg_units'], '0', threshold=0.8): # mais que 100
        print('full inventory?...') 
        sleep(3)
        screenshot = wincap.get_screenshot()
        if not (vision.checkMsgOnScreen(screenshot['ygg_hundreds'], '4', threshold=0.8) and not vision.checkMsgOnScreen(screenshot['ygg_units'], '0', threshold=0.8)):
            continue
        write_to_file('full inventory')
        serial_send('t')
        sleep(20)
        print('terminou de guardar itens!')

    elif not opening and vision.checkMsgOnScreen(screenshot['box_hundreds'], '2'):
        write_to_file('opening boxes')
        serial_send('b')
        opening = True

    elif opening and not (vision.checkMsgOnScreen(screenshot['box_hundreds'], '1') or vision.checkMsgOnScreen(screenshot['box_hundreds'], '2')):
        write_to_file('stop opening boxes')
        serial_send('b')
        opening = False
    elif vision.checkMsgOnScreen(screenshot['iradethor'], 'iradethor', threshold=0.75):
        serial_send('i')
        # print('iradethor')
        sleep(1)
    # else:
    #     print('nothing...')



    if cv.waitKey(1) == ord('q'):
        cv.destroyAllWindows()
        break

print('Done.')
