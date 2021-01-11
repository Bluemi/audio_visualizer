#!/usr/bin/python3

import sys
import os.path
import string

import numpy as np
import cv2
from tqdm import tqdm


def print_usage():
    print('usage:\n\tletter_creator IMAGE')


def format_float(f):
    if f == 0:
        return '0.f'
    return str(f) + 'f'


def create_img(letter):
    img = np.zeros((64, 64), np.uint8)
    font = cv2.FONT_HERSHEY_SIMPLEX
    bottomLeftCornerOfText = (7,54)
    fontScale = 2
    fontColor = (255,255,255)
    lineType = 1

    cv2.putText(
        img,
        letter, 
        bottomLeftCornerOfText, 
        font, 
        fontScale,
        fontColor,
        lineType
    )
    return img


def add_letter(output_file, width_file, letter):
    img = create_img(letter)

    left, right = None, None

    points = []
    for y, line in enumerate(img):
        for x, pixel in enumerate(line):
            if pixel > 128:
                xf = x/img.shape[1]
                yf = 1.0 - y/img.shape[0]
                points.append((xf, yf))
                if left is None or left > x:
                    left = x
                if right is None or right < x:
                    right = x

    output_file.write('\tif (letter == \'{}\') {{\n'.format(letter))
    for point in points:
        output_file.write('\t\t_points.push_back(glm::vec4(0.f, {}, {}, 1.f));\n'.format(format_float(point[1]), format_float(point[0])))
    output_file.write('\t}\n')

    width = ((right-left) / img.shape[1]) + 0.1
    width_file.write('\tif (letter == \'{}\') {{\n'.format(letter))
    width_file.write('\t\treturn {};\n'.format(format_float(width)))
    width_file.write('\t}\n')



def main():
    output_filename = 'output/letters.cpp'
    width_filename = 'output/width.cpp'

    with open(output_filename, 'w') as output_file:
        with open(width_filename, 'w') as width_file:
            for letter in tqdm('-'):
                add_letter(output_file, width_file, letter)

if __name__ == '__main__':
    main()
