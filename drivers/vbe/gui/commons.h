#pragma once
#include "../../../utils/kernel_utils.c"
#define Node(type)                                                             \
  type parent;                                                                 \
  type last;                                                                   \
  type next;                                                                   \
  type prev
#define node_insert(o, p)                                                      \
  do {                                                                         \
    if (p) {                                                                   \
      (o)->parent = (p);                                                       \
      if ((p)->last)                                                           \
        (p)->last->next = (o);                                                 \
      (o)->prev = (p)->last;                                                   \
      (o)->next = 0;                                                           \
      (p)->last = (o);                                                         \
    }                                                                          \
  } while (0)

#define node_remove(o)                                                         \
  do {                                                                         \
    if ((o)->parent) {                                                         \
      if ((o)->parent->last == (o))                                            \
        (o)->parent->last = (o)->prev;                                         \
      if ((o)->prev)                                                           \
        (o)->prev->next = (o)->next;                                           \
      if ((o)->next)                                                           \
        (o)->next->prev = (o)->prev;                                           \
      (o)->next = 0;                                                           \
      (o)->prev = 0;                                                           \
      (o)->parent = 0;                                                         \
    }                                                                          \
  } while (0)

typedef void (*AtomDestructor)(void *atom);
typedef u32 Pixel;
typedef struct {
  AtomDestructor _destructor;
  unsigned int lock;
  bool flag;
  bool allocated;
} Atom;

typedef struct {
  int left;
  int top;
  int right;
  int bottom;
} Rect;

typedef struct {
  void *_destructor;
  unsigned int lock;
  bool flag;
  bool allocated;
  Rect rect;
} RectAtom;

typedef void (*Class)(void);

typedef struct Object {
  union {
    Atom atom;
    RectAtom rectatom;
  } base;
  Class _class;
  Node(Object *);
  struct Window *win;
  int id;
  bool destroying;
  bool armed;
  bool armable;
  bool selected;
  bool selectable;
  bool disabled;
  bool wantmove;
  bool visible;
  bool has_mnemonic;
} Object;

typedef struct Window {
  union {
    Atom atom;
    RectAtom rectatom;
    Object obj;
    struct Textual textual;
  } base;
  u32 flags;
  Handler handler;
  struct BITMAP *icon; // icon in left top part of title bar
  struct WINBORDER *border;
  struct MENU *menu;
  struct BUTTON_BAR *button_bar;
  Node(Window *);
  int modallock;
  bool ismodal;
} Window;

typedef struct Bitmap {
  union {
    RectAtom rectatom;
    Atom atom;
  } base;
  int pitch;
  Rect clip;

  u8 count;             // count of images (256 max allowed)
  u8 current;           // current image being displayed
  u16 delay_array[256]; // jiffies delay before rendering next image
  int count_down;       // jiffy count down of current images (if count > 0)

  Pixel *array;
} Bitmap;

typedef struct Image {
  union {
    Atom atom;
    RectAtom rectatom;
    Object obj;
  } base;
  u32 flags;
  Bitmap *bitmap;
} Image;

typedef struct Caret {
  int height;
  Rect rect;
  Image *caret;
} Caret;

typedef enum Align {
  ALIGN_NONE = 0,
  ALIGN_RIGHT = (1 << 0),
  ALIGN_LEFT = (1 << 1),
  ALIGN_TOP = (1 << 2),
  ALIGN_BOTTOM = (1 << 3),
  ALIGN_HCENTER = (1 << 4),
  ALIGN_VCENTER = (1 << 5),
  ALIGN_CENTER = ALIGN_HCENTER | ALIGN_VCENTER
} Align;

typedef void (*Font_Drawer)(Bitmap *, Rect *, Rect *, u8 *, u32, Pixel, Pixel);

typedef struct Font_Info {
  u16 index;   // Indices in data of each character
  u8 width;    // Width of this character
  u8 flags;    // nothing at the moment
  char deltax; // +/- offset to print char
  char deltay; // +/- offset to print char (allows for drop chars, etc)
  char deltaw; // +/- offset to combine with width above when moving to the next
               // char
  u8 resv;     // reserved
} Font_Info;

typedef struct Font {
  u8 sig[4];    // 'FONT'
  u8 height;    // height of char set
  u8 max_width; // width of widest char in set
  u16 start; // starting asciiz value (first entry in font == this ascii value)
  u16 count; // count of chars in set ( 0 < count <= 256 )
  u16 datalen;          // len of the data section in bytes
  u32 total_size;       // total size of this file in bytes
  u32 flags;            // bit 0 = fixed width font, remaining bits are reserved
  u8 resv[14];          // reserved
  char name[16];        // 15 chars, 1 null
  Font_Drawer drawchar; // Callbacks for handling fonts
  struct Font *prev;    // linked chain of fonts
  struct Font *next;    //
  // struct FONT_INFO info[];  // char info
  // bit8u data[];     // char data
} Font;

typedef struct Textual {
  union {
    Atom atom;
    RectAtom rectatom;
    Object obj;
  } base;
  u32 flags;
  String text;
  Align align;
  bool hovering;
  int textwidth;
  int textheight;
  Pixel fore_color;
  Pixel back_color;
  const Font *font;
  Bitmap *decorator;
  int cur_char_pos;
  Caret caret;
} Textual;
