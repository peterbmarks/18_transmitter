//  _  ___  _   _____ _     _
// / |/ _ \/ | |_   _| |__ (_)_ __   __ _ ___
// | | | | | |   | | | '_ \| | '_ \ / _` / __|
// | | |_| | |   | | | | | | | | | | (_| \__ \
// |_|\___/|_|   |_| |_| |_|_|_| |_|\__, |___/
//                                  |___/
//
// Copyright (c) Jonathan P Dawson 2023
// filename: transmitter.cpp
// description: Ham Transmitter for Pi Pico
// License: MIT
//

// Microphone example, transmit audio from microphone input

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include <cmath>
#include <stdio.h>
#include <ctype.h>

#include "transmit.h"
#include "psu_mode.h"

// example application
int main() {
  // The PIO oscillator emits one bit per system clock and the NCO maths assume
  // a 125 MHz system clock. RP2040 boots at 125 MHz, but RP2350 (Pico 2) boots
  // at 150 MHz, so pin the clock to 125 MHz on every board to keep the RF
  // output on frequency.
  set_sys_clock_khz(125000, true);

  stdio_init_all();
  disable_power_save();

  // Hard code frequency and mode
  uint32_t frequency = 14.175e6;
  tx_mode_t mode = USB;


  // start transmitter using microphone
  transmit(mode, frequency);
}
