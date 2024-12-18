#ifndef MPU6050_H
#define MPU6050_H

#include "hardware/i2c.h"
#include <stdbool.h>

// Initialize the MPU6050 sensor
bool mpu6050_init(i2c_inst_t *i2c, uint8_t addr);

// Read accelerometer data
void mpu6050_read_accel(i2c_inst_t *i2c, uint8_t addr, float *ax, float *ay, float *az);

// Read gyroscope data
void mpu6050_read_gyro(i2c_inst_t *i2c, uint8_t addr, float *gx, float *gy, float *gz);

#endif // MPU6050_H
