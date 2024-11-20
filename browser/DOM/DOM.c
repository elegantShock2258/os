#pragma once

#include "./DOM.h"
#include "../../arch/i686/hal/memory/kheap/kheap.c"
#include "../../arch/i686/hal/io/printf.c"

Node* Text(char* data){
    Node* text = kmalloc(sizeof(Node));
    text->type = {.Text=data};
    text->children = NULL;
    return text;
}

