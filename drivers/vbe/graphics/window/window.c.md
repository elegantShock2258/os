# window.c

## Description
Implementation of the Windowing system. It uses an AVL tree to order windows by Z-index (height) and renders them in order from bottom to top using an inorder traversal.

## Imports
- [[window.h.md]]

## Variables
- `Node WindowRoot`

## Functions
- `void renderWindow(Window *window, u32 *bf, u32 w, u32 h)`: Copies a window's framebuffer into the main backbuffer (`bf`), clipping if necessary.
- `void inOrderOperation(Node *root, u32 *bf, u32 *w, u32 *h)`: Traverses the window tree and calls `renderWindow` sequentially.
- `int _AVL_comparitor(void *a, void *b)`: Compares windows by their Z-index/height.
- `void windowManagerInit(u32 *fb, u32 *bf, u32 w, u32 h)`: Sets up the root window (desktop), constructs the AVL tree, and loops infinitely to render all windows, the mouse cursor, and blits to the screen.
