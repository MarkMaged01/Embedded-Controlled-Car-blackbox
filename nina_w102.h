// nina_w102.h - Header file for NINA-W102 library

#ifndef NINA_W102_H
#define NINA_W102_H

#include "pico/stdlib.h"

// UART configuration for NINA-W102
#define NINA_UART_ID uart1
#define NINA_BAUD_RATE 115200
#define NINA_TX_PIN 9  // GPIO for UART TX
#define NINA_RX_PIN 8  // GPIO for UART RX

// Function prototypes
void nina_init();
void nina_send_command(const char *command);
void nina_read_response();
void nina_configure(const char *name, const char *baud_rate);

#endif // NINA_W102_H
