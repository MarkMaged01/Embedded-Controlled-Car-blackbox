#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define MPU6050_ADDR 0x68 // MPU6050 I2C address

void setup_mpu6050()
{
    // Initialize I2C on instance i2c0 with a clock speed of 100 kHz
    i2c_init(i2c0, 400000);
    gpio_set_function(12, GPIO_FUNC_I2C); // SDA pin (A4)
    gpio_set_function(13, GPIO_FUNC_I2C); // SCL pin (A5)
    gpio_pull_up(12);
    gpio_pull_up(13);

    uint8_t buffer[2];

    // Wake up the MPU6050 (clear sleep mode)
    buffer[0] = 0x6B; // Power Management 1 register
    buffer[1] = 0x00; // Clear sleep mode
    i2c_write_blocking(i2c0, MPU6050_ADDR, buffer, 2, false);

    // i2c_write_blocking(i2c0, MPU6050_ADDR, buffer, 2, false);

    // Set accelerometer range to ±4g (scale factor = 8192)
    buffer[0] = 0x1C; // Accelerometer Configuration register
    buffer[1] = 0x08; // Set to ±4g
    i2c_write_blocking(i2c0, MPU6050_ADDR, buffer, 2, false);

    // Set gyroscope range to ±500°/s (scale factor = 65.5)
    buffer[0] = 0x1B; // Gyroscope Configuration register
    buffer[1] = 0x08; // Set to ±500°/s
    i2c_write_blocking(i2c0, MPU6050_ADDR, buffer, 2, false);
}

void read_mpu6050(float *accel, float *gyro)
{
    uint8_t buffer[14];

    // Start reading from register 0x3B
    i2c_write_blocking(i2c0, MPU6050_ADDR, (uint8_t[]){0x3B}, 1, true);

    // Read 14 bytes from the sensor
    i2c_read_blocking(i2c0, MPU6050_ADDR, buffer, 14, false);

    // Convert accelerometer data (16-bit two's complement)
    accel[0] = (buffer[0] << 8 | buffer[1]) / 16384.0; // X-axis
    accel[1] = (buffer[2] << 8 | buffer[3]) / 16384.0; // Y-axis
    accel[2] = (buffer[4] << 8 | buffer[5]) / 16384.0; // Z-axis

    // Convert gyroscope data (16-bit two's complement)
    gyro[0] = (int16_t)(buffer[8] << 8 | buffer[9]) / 65.5;   // X-axis
    gyro[1] = (int16_t)(buffer[10] << 8 | buffer[11]) / 65.5; // Y-axis
    gyro[2] = (int16_t)(buffer[12] << 8 | buffer[13]) / 65.5; // Z-axis
    printf("Accelerometer: X=%.2f, Y=%.2f, Z=%.2f\n", accel[0], accel[1], accel[2]);
    printf("Gyroscope: X=%.2f, Y=%.2f, Z=%.2f\n", gyro[0], gyro[1], gyro[2]);
    // Debug: Print raw data
    printf("Raw data: ");
    for (int i = 0; i < 14; i++)
    {
        printf("%02X ", buffer[i]);
    }
    printf("\n");
}
void check_mpu6050_registers()
{
    uint8_t reg_value;
    i2c_write_blocking(i2c0, MPU6050_ADDR, (uint8_t[]){0x6B}, 1, true); // Power Management 1
    i2c_read_blocking(i2c0, MPU6050_ADDR, &reg_value, 1, false);
    printf("Power Management 1 (0x6B): 0x%02X\n", reg_value);

    i2c_write_blocking(i2c0, MPU6050_ADDR, (uint8_t[]){0x1C}, 1, true); // Accelerometer Config
    i2c_read_blocking(i2c0, MPU6050_ADDR, &reg_value, 1, false);
    printf("Accelerometer Config (0x1C): 0x%02X\n", reg_value);

    i2c_write_blocking(i2c0, MPU6050_ADDR, (uint8_t[]){0x1B}, 1, true); // Gyroscope Config
    i2c_read_blocking(i2c0, MPU6050_ADDR, &reg_value, 1, false);
    printf("Gyroscope Config (0x1B): 0x%02X\n", reg_value);
}
