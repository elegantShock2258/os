#include <bits/stdc++.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define COLOR(r, g, b) ((b) | (g << 8) | (r << 16))
typedef struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Color;

using namespace std;
// unsigned int *printEDI() {
//   unsigned int edi_value;

//   asm("mov %0, %%edi" : "=r"(edi_value));
//   return (unsigned int *)edi_value;
// }
#define pitch 7680
#define bpp 32
#define colorDepth 4

unsigned int fb[1920 * 1080] = {0};
void _VBE_drawRect(int x, int y, int width, int height, int color) {

  unsigned int pixelsPerRow = 1920 ;

  for (unsigned int row = 0; row < height; ++row) {
    auto start = fb + (y + row) * pixelsPerRow + x;
    // cout << "init: " << start << '\t';
    __asm__ __volatile__(
        "cld\n\t"       // Clear direction flag
        "rep stosl\n\t" // Store DWORD (32 bits) from EAX to [EDI]
        :
        : "D"(start),    // EDI: Destination address (start of the row)
          "a"(color),    // EAX: Color value to store
          "c"(width)     // ECX:
        : "memory", "cc" // Clobbered registers
    );
    // cout << "end: " << printEDI() << endl;
  }
}

int main() {
  _VBE_drawRect(900, 900, 100, 100, COLOR(255, 255, 255));
  int width = 1920;
  int height = 1080;

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int index = (y * width + x);
      auto c = *((Color *)&fb[index]);
      unsigned int r = c.r;
      unsigned int g = c.g;
      unsigned int b = c.b;

      std::cout << r << "," << g << "," << b << endl;
    }
  }
}