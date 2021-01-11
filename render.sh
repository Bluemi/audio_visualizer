#!/bin/bash

TMP_FILE=./video/tmp.mp4

ffmpeg -r 60 -f image2 -s 1920x1080 -i video/capture/Capture_%06d.png -vf vflip -vcodec libx264 -crf 25  -pix_fmt yuv420p "$TMP_FILE"
ffmpeg -i "$TMP_FILE" -i "res/Suzys Gone.wav" -shortest video/suzys_gone.mp4
