#ifndef GY87_H
#define GY87_H

#include <stdbool.h>
#include "hardware/i2c.h"

// Initialize GY87 sensor
bool GY87_init(i2c_inst_t *i2c);

// Read accelerometer and gyroscope data
void GY87_readSensors(i2c_inst_t *i2c, float *ax, float *ay, float *az, float *gx, float *gy, float *gz);

#endif // GY87_H
