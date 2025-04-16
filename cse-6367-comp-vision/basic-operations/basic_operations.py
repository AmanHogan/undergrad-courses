import numpy as np
import matplotlib.pyplot as plt
import cv2

class ImageOperator:
    
    def __init__(self):
        pass
    
    @classmethod
    def crop_image(cls):
        pass

    @classmethod
    def test_hue(cls):
        pass

    @classmethod
    def test_saturation(cls):
        pass

    @classmethod
    def test_value(sls):
        pass

    @classmethod
    def grayscale(cls, image, average=True):
        
        blue = image[:,:, 0]
        green = image[:,:, 1]
        red = image[:,:, 2]
        
        grey = blue/3 + green/3 + red/3

        return grey