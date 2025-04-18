set -e
clear ;g++ a.cpp ; ./a.out >> output ; python3 frameBufferVisualizer.py; feh output_image.png
