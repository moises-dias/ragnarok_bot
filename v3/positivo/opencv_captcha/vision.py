import cv2 as cv
import numpy as np


class Vision:

    # constructor
    def __init__(self):
        # load the image we're trying to match
        # https://docs.opencv.org/4.2.0/d4/da8/group__imgcodecs.html
        self.images = {
            "first_message": cv.imread('images/msg1.jpeg', cv.IMREAD_UNCHANGED),
            "second_message": cv.imread('images/msg2.jpeg', cv.IMREAD_UNCHANGED),
            "iradethor": cv.imread('images/iradethor.jpeg', cv.IMREAD_UNCHANGED),
            "dc": cv.imread('images/dc.jpeg', cv.IMREAD_UNCHANGED)
        }
        for i in range(10):
            self.images[str(i)] = cv.imread(f'images/{i}.jpeg', cv.IMREAD_UNCHANGED)

        # There are 6 methods to choose from:
        # TM_CCOEFF, TM_CCOEFF_NORMED, TM_CCORR, TM_CCORR_NORMED, TM_SQDIFF, TM_SQDIFF_NORMED

    def findNumbers(self, game_image, threshold=0.9):
        matches = {}
        numbers = list(self.images.values())[-10:]
        for i, number_img in enumerate(numbers):
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
        needle_image = self.images[im_type]
        result = cv.matchTemplate(game_image, needle_image, cv.TM_CCOEFF_NORMED)
        return np.any(result >= threshold)