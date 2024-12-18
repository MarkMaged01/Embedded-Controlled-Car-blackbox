#include "mpu6050.h"
#include <stdio.h>
#include "hardware/i2c.h"

bool mpu6050_init(i2c_inst_t *i2c, uint8_t addr) {
    uint8_t data[2];
    printf("Initializing MPU6050...\n");

    // Wake up the MPU6050 by writing 0 to the power management register
    data[0] = 0x6B; // PWR_MGMT_1 register
    data[1] = 0x00; // Set to 0 to wake up
    if (i2c_write_blocking(i2c, addr, data, 2, true) != 2) {
        return false;
    }
    return true;
}

void mpu6050_read_accel(i2c_inst_t *i2c, uint8_t addr, float *ax, float *ay, float *az) {
    uint8_t reg = 0x3B; // ACCEL_XOUT_H
    uint8_t buffer[6];
    i2c_write_blocking(i2c, addr, &reg, 1, true);
    i2c_read_blocking(i2c, addr, buffer, 6, false);

    // Convert raw data to g's
    *ax = (int16_t)((buffer[0] << 8) | buffer[1]) / 16384.0;
    *ay = (int16_t)((buffer[2] << 8) | buffer[3]) / 16384.0;
    *az = (int16_t)((buffer[4] << 8) | buffer[5]) / 16384.0;
}

void mpu6050_read_gyro(i2c_inst_t *i2c, uint8_t addr, float *gx, float *gy, float *gz) {
    uint8_t reg = 0x43; // GYRO_XOUT_H
    uint8_t buffer[6];
    i2c_write_blocking(i2c, addr, &reg, 1, true);
    i2c_read_blocking(i2c, addr, buffer, 6, false);

    // Convert raw data to degrees/second
    *gx = (int16_t)((buffer[0] << 8) | buffer[1]) / 131.0;
    *gy = (int16_t)((buffer[2] << 8) | buffer[3]) / 131.0;
    *gz = (int16_t)((buffer[4] << 8) | buffer[5]) / 131.0;
}
