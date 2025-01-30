#include<convert_image_to_ascii.hpp>

// Преобразование изображения в формат ASCII
vector<char8_t> convert_image_to_ascii(IMAGE *image, int width, int height) {
   vector<char8_t> ascii_data;

   for (int y=0; y<height; y++) {
      for (int x=0; x<width; x++) {
         int pixel_color=imagegetpixel(image, x, y);
         int r=RED_VALUE(pixel_color);
         int g=GREEN_VALUE(pixel_color);
         int b=BLUE_VALUE(pixel_color);
         
         // Преобразование RGB в оттенок серого
         double gray=0.2989*r+0.5870*g+0.1140*b;

         const char8_t *ascii_char;
         if (gray < 51) {
            ascii_char=u8"\u2588"; //Full block
         } else if (gray < 102) {
            ascii_char=u8"\u2593"; //Dark shade
         } else if (gray < 153) {
            ascii_char=u8"\u2592"; //Medium shade
         } else if (gray < 204) {
            ascii_char=u8"\u2591"; //Light shade
         } else {
            ascii_char=u8" "; //Пробел
         }

         // Добавление UTF-8 символа
         for (const char8_t *p=ascii_char; *p != '\0'; ++p) {
            ascii_data.push_back(*p);
         }
      }
      // Добавление перевода строки в конце каждой строки изображения
      ascii_data.push_back(u8'\n');
   }
   return ascii_data;
}