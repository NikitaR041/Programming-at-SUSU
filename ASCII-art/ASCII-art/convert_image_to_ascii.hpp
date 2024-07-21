#ifndef CONVERT_IMAGE_TO_ASCII_HPP
#define CONVERT_IMAGE_TO_ASCII_HPP

#include <iostream>
#include <vector>
#include <graphics.h>
#include <uchar.h>

using namespace std;

vector<char8_t> convert_image_to_ascii(IMAGE *image, int width, int height);

#endif  /* CONVERT_IMAGE_TO_ASCII_HPP */