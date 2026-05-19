#pragma once
#include "./window.h"
#include "../../../../tests/testing.c"

// TODO: implement dnd, and BOX model too, i need padding, margin on each window
// and window toolbar to close/minimise it

SceneGraph *SceneGraphInit() {
  SceneGraph *sg = (SceneGraph *)kmalloc(sizeof(SceneGraph));
  sg->Background = NULL;
  sg->SystemPanel = NULL;
  sg->Applications = NULL;
  sg->Tooltips = NULL;

  return sg;
}

void renderWindow(Window *window, VbeDriverState *VbeDriver) {
  u32 *t = window->windowFb;

  for (u32 i = 0; i < window->height; i++) {
    u32 fb_y = i + window->y;
    if (fb_y >= VbeDriver->vbe_h)
      break;

    u32 *start = VbeDriver->bf + fb_y * VbeDriver->vbe_w + window->x;
    u32 copy_width = window->width;

    if ((window->x + copy_width) > VbeDriver->vbe_w)
      copy_width = VbeDriver->vbe_w - window->x;

    if (window->x < 0) {
      t -= window->x;
      copy_width += window->x;
      start = VbeDriver->bf + fb_y * VbeDriver->vbe_w;
    }

    if (copy_width > 0) {
      memcpy(start, t, copy_width);
    }

    t += window->width;
  }
}

void renderLayer(Window *layer, VbeDriverState *vbe) {
  // go through each node
  // go to child nodes
  // render childs
  Window *ptr = layer;
  while (ptr != NULL) {
    // logf("printing window %d\n",ptr->zIndex);
    renderWindow(ptr, vbe);
    ptr = ptr->next;
  }
}

void traverseSceneGraph(SceneGraph *sg, VbeDriverState *vbe) {
  // TODO: switch to opaque front and back pass
  // render bg
  // logf("rendering bg layer\n");
  renderLayer(sg->Background, vbe);
  //  // render system panel
  renderLayer(sg->SystemPanel, vbe);
  //  // render applications
  renderLayer(sg->Applications, vbe);
  //  // render tooltips
  renderLayer(sg->Tooltips, vbe);
}
