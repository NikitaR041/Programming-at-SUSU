#include <save_to_png_txt.h>

void save_to_png_txt(const vector<char8_t> &ascii_data, int width, int height) {
   string filename1=filename;
   filename1.erase(filename1.find('.'));
   ofstream outfile("Arts/" + filename1+ ".txt");
   if (!outfile.is_open()) {
      cerr << "Failed to open file for writing" << endl;
      return;
   }
   outfile.write("\xEF\xBB\xBF", 3);
   outfile.write((const char *)ascii_data.data(), ascii_data.size());
   outfile.close();
}