import cv2 as cv
import numpy as np


class Vision:

    def __init__(self):
        self.first_message = cv.imread('images/msg1.jpeg', cv.IMREAD_UNCHANGED)
        self.second_message = cv.imread('images/msg2.jpeg', cv.IMREAD_UNCHANGED)
        self.numbers = []
        for i in range(10):
            self.numbers.append(cv.imread(f'images/{i}.jpeg', cv.IMREAD_UNCHANGED))

        # There are 6 methods to choose from:
        # TM_CCOEFF, TM_CCOEFF_NORMED, TM_CCORR, TM_CCORR_NORMED, TM_SQDIFF, TM_SQDIFF_NORMED

    def findNumbers(self, game_image, threshold=0.9):
        matches = {}
        for i, number_img in enumerate(self.numbers):
            result = cv.matchTemplate(game_image, number_img, cv.TM_CCOEFF_NORMED)
            locations = np.where(result >= threshold)
            locations = list(zip(*locations[::-1]))
            for loc in locations: 
                matches[loc[0]] = i
        result = []
        for key in sorted(matches):
            result.append(matches[key])
            result = [str(r) for r in result]
        return result
    
    def checkMsgOnScreen(self, game_image, type, threshold=0.9):
        if type == 'first_message':
            needle_image = self.first_message
        else:
            needle_image = self.second_message

        result = cv.matchTemplate(game_image, needle_image, cv.TM_CCOEFF_NORMED)
        return np.any(result >= threshold)