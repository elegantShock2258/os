#pragma once
#include "../../utils/kernel_utils.c"
#include "../io/printf.c"
#include "../hal.h"
typedef struct {
   char     VbeSignature[4];         // == "VESA"
   uint16_t VbeVersion;              // == 0x0300 for VBE 3.0
   uint16_t OemStringPtr[2];         // isa vbeFarPtr
   uint8_t  Capabilities[4];
   uint16_t VideoModePtr[2];         // isa vbeFarPtr
   uint16_t TotalMemory;             // as # of 64KB blocks
   uint8_t  _Reserved[492];
} VbeInfoBlock  __attribute__((packed));
extern int Video_getVBEInfo(VbeInfoBlock *info);
void vbe_info(){

}
int getVBEConrollerInfo(VbeInfoBlock* info, char* name){

    return strcmp(info->VbeSignature,"VESA");
}