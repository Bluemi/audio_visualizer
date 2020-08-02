#!/usr/bin/python3

import sys
import cv2
import os.path


def print_usage():
    print('usage:\n\tletter_creator IMAGE')


def format_float(f):
    if f == 0:
        return '0.f'
    return str(f) + 'f'


def main():
    if len(sys.argv) != 2:
        print_usage()
        return

    img_path = sys.argv[1]
    img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)

    points = []
    for y, line in enumerate(img):
        for x, pixel in enumerate(line):
            if pixel < 128:
                xf = x/img.shape[1]
                yf = 1.0 - y/img.shape[0]
                points.append((xf, yf))

    os.makedirs('output', exist_ok=True)

    output_filename = os.path.join('output', os.path.splitext(os.path.basename(img_path))[0] + '.cpp')
    if os.path.exists(output_filename):
        raise Exception('output file "{}" already exists'.format(output_filename))

    with open(output_filename, 'w') as f:
        for point in points:
            f.write('\t_points.push_back(glm::vec3(0.f, {}, {}));\n'.format(format_float(point[1]), format_float(point[0])))

if __name__ == '__main__':
    main()
