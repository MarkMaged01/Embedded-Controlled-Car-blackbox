#include "GY87.h"
#include <math.h>
#include <stdio.h>
#include "hardware/i2c.h"
#include "mpu6050.h"

// MPU6050 device address
#define MPU6050_ADDR 0x68

// Initialize GY87 sensor
bool GY87_init(i2c_inst_t *i2c) {
    if (mpu6050_init(i2c, MPU6050_ADDR)==false) {
        return false; // Initialization failed
    }
    return true; // Initialization successful
}

// Read accelerometer and gyroscope data
void GY87_readSensors(i2c_inst_t *i2c, float *ax, float *ay, float *az, float *gx, float *gy, float *gz) {
    mpu6050_read_accel(i2c, MPU6050_ADDR, ax, ay, az);
    mpu6050_read_gyro(i2c, MPU6050_ADDR, gx, gy, gz);
}
