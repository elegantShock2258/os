#include "./window.h"
// #include "../../../../meta/framebuffer/images/a.c"

void renderWindow(Window *window, u32 *bf, u32 w, u32 h) {
    u32 *t = window->windowFb;
    
    for (u32 i = 0; i < window->height; i++) {
        u32 fb_y = i + window->y;
        if (fb_y >= h) break;  

        u32 *start = bf + fb_y * w + window->x;
        u32 copy_width = window->width;

        if (window->x + copy_width > w)
            copy_width = w - window->x;

        if (window->x < 0) {
            t -= window->x; 
            copy_width += window->x; 
            start = bf + fb_y * w; 
        }

        if (copy_width > 0) {
            memcpy(start, t, copy_width * sizeof(u32));
        }

        t += window->width; 
    }
}


Node *WindowRoot;
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

void windowManagerInit(u32 *fb, u32 *bf, u32 w, u32 h) {
  // create first window, ill put one window will w-full h-full and bg-red

  Window *ws = kmalloc(sizeof(Window));
  ws->x = 40;
  ws->y = 40;
  ws->width = 192;
  ws->height = 108;
  ws->windowFb = kmalloc(ws->width * ws->height * sizeof(u32));

  memset(ws->windowFb, COLOR(0, 255, 0), ws->width * ws->height);

  renderWindow(ws, bf, w, h);
 

  // WindowRoot = createNode(ws, &(ws->zIndex));
  // im gonna count the mouse seperate from the windows
  while (1) {
    // traverse the window tree
    // _VBE_render();
    // inOrderOperation(WindowRoot, bf, &w,&h);
    // _VBE_putcursor(MouseDriver.mouse_x, MouseDriver.mouse_y);
    // renderWindow(ws, bf, w, h);

    memcpy(fb, bf, h * w);
    sleep(100); // somehow gui doesnt update without this
  }
}