#ifndef SAVE_TO_PNG_TXT_H
#define SAVE_TO_PNG_TXT_H

#include<iostream>
#include <string>
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>
#include <uchar.h>

using namespace std;
using namespace filesystem;

extern string filename;
void save_to_png_txt(const vector<char8_t>& ascii_data, int width, int height);

#endif  /* SAVE_TO_PNG_TXT */