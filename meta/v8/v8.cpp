#include <bits/stdc++.h>
#include "./cef/"

using namespace std;

#define W 1920
#define H 1080
class OffscreenRenderHandler : public CefRenderHandler {
public:
  OffscreenRenderHandler(int width, int height)
      : width_(width), height_(height) {}

  void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override {
    rect = CefRect(0, 0, width_, height_);
  }

  void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type,
               const RectList &dirtyRects, const void *buffer, int width,
               int height) override {
    // Copy the buffer into your framebuffer
    memcpy(framebuffer, buffer, width * height * 4); // Assuming RGBA format
  }

private:
  int width_, height_;
  uint8_t *framebuffer; // Your framebuffer pointer
  IMPLEMENT_REFCOUNTING(OffscreenRenderHandler);
};

int main() { return 1; }