#pragma once
#include "../../io/printf.c"
#include "../../io/serial.c"
#include <stddef.h>
#include <stdint.h>

#define PIT_FREQUENCY 1193182 // The base frequency of the PIT
#define PIT_COMMAND 0x43      // Command register for the PIT
#define PIT_CHANNEL0 0x40 // Channel 0 data port (usually connected to IRQ 0)
volatile u32 _pit_frequency = 1;
void pit_init(uint32_t frequency) {
  uint16_t divisor = PIT_FREQUENCY / frequency;
  _pit_frequency = frequency;
  // Send the command byte
  outb(PIT_COMMAND, 0x36);

  // Send the frequency divisor
  outb(PIT_CHANNEL0, (uint8_t)(divisor & 0xFF));        // Low byte
  outb(PIT_CHANNEL0, (uint8_t)((divisor >> 8) & 0xFF)); // High byte
}
volatile uint32_t ticks = 0;

void timer() { ticks++; }

void sleep(uint32_t milliseconds) {
  uint32_t end_ticks = ticks + ((milliseconds * _pit_frequency) / 1000);
  while (ticks < end_ticks) {
    asm volatile("hlt");
  }
}