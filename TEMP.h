#define BMP180_ADDR 0x77
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
// #include "gy87.h"

void setup_bmp180() {
    // No special initialization needed
}

void read_bmp180_temp(float *temperature) {
    uint8_t buffer[2];
    uint16_t raw_temp;

    // Start temperature conversion
    i2c_write_blocking(i2c0, BMP180_ADDR, (uint8_t[]){0xF4, 0x2E}, 2, false);
    sleep_ms(5); // Wait for conversion

    // Read raw temperature
    i2c_write_blocking(i2c0, BMP180_ADDR, (uint8_t[]){0xF6}, 1, true);
    i2c_read_blocking(i2c0, BMP180_ADDR, buffer, 2, false);
    raw_temp = (buffer[0] << 8) | buffer[1];

    // Convert to actual temperature
    *temperature = raw_temp / 10.0; // Simplified conversion
}