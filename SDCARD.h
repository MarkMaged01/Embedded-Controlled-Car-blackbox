#include "pico/stdlib.h"
#include "ff.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
// #include "gy87.h"
#include <string.h>


FATFS fs;
FIL file;
FRESULT fr;

void setup_sd_card() {
    f_mount(&fs, "", 1); // Mount the SD card
}

void log_data(float accel[], float gyro[], float temperature) {
    fr = f_open(&file, "log.txt", FA_WRITE | FA_OPEN_APPEND);
    if (fr == FR_OK) {
        char log_entry[128];
        sprintf(log_entry, "Accel: %.2f, %.2f, %.2f | Gyro: %.2f, %.2f, %.2f | Temp: %.2f\n",
                accel[0], accel[1], accel[2], gyro[0], gyro[1], gyro[2], temperature);
        f_write(&file, log_entry, strlen(log_entry), NULL);
        f_close(&file);
    }
}
    