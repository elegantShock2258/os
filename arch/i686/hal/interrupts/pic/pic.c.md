# pic.c

## Description
Implementation of the Programmable Interrupt Controller (8259 PIC) driver. Responsible for remapping hardware interrupts.

## Imports
- [[serial.c.md]]

## Functions
- `void PIC_Configure(u8 offsetPic1, u8 offsetPic2)`: Sends ICW commands to initialize master and slave PICs.
- `void PIC_SendEndOfInterrupt(int irq)`
- `void PIC_Disable()`, `PIC_Mask()`, `PIC_Unmask()`
- `u16 PIC_ReadIrqRequestRegister()`, `u16 PIC_ReadInServiceRegister()`
