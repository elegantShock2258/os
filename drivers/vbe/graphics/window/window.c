#include "./window.h"
// #include "../../../../meta/framebuffer/images/a.c"

void renderWindow(Window *window, u32 *bf, u32 w, u32 h) {
  u32 *t = window->windowFb;

  for (u32 i = 0; i < window->height; i++) {
    u32 fb_y = i + window->y;
    if (fb_y >= h)
      break;

    u32 *start = bf + fb_y * w + window->x;
    u32 copy_width = window->width;

    if ((window->x + copy_width) > w)
      copy_width = w - window->x;

    if (window->x < 0) {
      t -= window->x;
      copy_width += window->x;
      start = bf + fb_y * w;
    }

    if (copy_width > 0) {
      memcpy(start, t, copy_width);
    }

    t += window->width;
  }
}

void inOrderOperation(Node *root, u32 *bf, u32 *w, u32 *h) {
  if (root != NULL) {
    inOrderOperation(root->left, bf, w, h);
    renderWindow(root->key, bf, *w, *h);
    inOrderOperation(root->right, bf, w, h);
  }
}

int _AVL_comparitor(void *a, void *b) {
  Window *wa = (Window *)a;
  Window *wb = (Window *)b;

  return wa->height - wb->height;
}

Node WindowRoot; // idk why but using a Node* doesnt sit well with it
void windowManagerInit(u32 *fb, u32 *bf, u32 w, u32 h) {
  // create first window, ill put one window will w-full h-full and bg-red

  Window *ws = kmalloc(sizeof(Window));
  ws->x = 0;
  ws->y = 0;
  ws->width = 1920;
  ws->height = 1080;
  ws->windowFb = kmalloc((ws->width) * (ws->height) * sizeof(u32));
  for (u32 i = 0; i < ws->width * ws->height; i++) {
    ws->windowFb[i] = COLOR(0, 255, 0); // Ensure all pixels are properly set
  }

  ws->zIndex = 1;

  WindowRoot = *(Node *)kmalloc(sizeof(Node));
  WindowRoot.key = (void *)ws;
  WindowRoot.left = NULL;
  WindowRoot.right = NULL;
  WindowRoot.height = &(ws->zIndex);
  while (1) {
  // traverse the window tree

  // _VBE_fillScreen(COLOR(255, 0, 255));
  inOrderOperation(&WindowRoot, bf, &w, &h);
  _VBE_putcursor(MouseDriver.mouse_x, MouseDriver.mouse_y);

  memcpy(fb, bf, h * w);
  sleep(100); // somehow gui doesnt update without this
  }
}
