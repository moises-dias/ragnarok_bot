import cv2 as cv
import numpy as np


class Vision:

    # constructor
    def __init__(self):
        # load the image we're trying to match
        # https://docs.opencv.org/4.2.0/d4/da8/group__imgcodecs.html
        self.first_message = cv.imread('images/msg1.jpeg', cv.IMREAD_UNCHANGED)
        self.second_message = cv.imread('images/msg2.jpeg', cv.IMREAD_UNCHANGED)
        self.weight = cv.imread('images/peso.jpeg', cv.IMREAD_UNCHANGED)
        self.two_box = cv.imread('images/2.jpeg', cv.IMREAD_UNCHANGED)
        self.one_box = cv.imread('images/1.jpeg', cv.IMREAD_UNCHANGED)
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
    
    def checkMsgOnScreen(self, game_image, im_type, threshold=0.9):
        if im_type == 'first_message':
            needle_image = self.first_message
        elif im_type == 'second_message':
            needle_image = self.second_message
        elif im_type == 'one_box':
            needle_image = self.one_box
        elif im_type == 'two_box':
            needle_image = self.two_box
        else:
            needle_image = self.weight

        result = cv.matchTemplate(game_image, needle_image, cv.TM_CCOEFF_NORMED)
        #if im_type == 'weight':
        #    print(np.max(result))
        return np.any(result >= threshold)