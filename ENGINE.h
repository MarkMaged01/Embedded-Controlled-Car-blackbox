#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "hardware/pwm.h" // Include the hardware PWM library for controlling PWM functionality.

#define ENGINE_PIN 14 // Define the GPIO pin connected to the engine (PWM output).

// Function to configure the PWM settings for the engine.
void setup_engine_pwm() {
    gpio_set_function(ENGINE_PIN, GPIO_FUNC_PWM); // Set the GPIO pin function to PWM.
    uint slice_num = pwm_gpio_to_slice_num(ENGINE_PIN); // Get the PWM slice number for the given GPIO pin.
    pwm_set_wrap(slice_num, 255); // Set the PWM counter wrap value, which determines the duty cycle range (0-255).
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0); // Set the initial duty cycle to 0 (engine off).
    pwm_set_enabled(slice_num, true); // Enable the PWM output for the selected slice.
}

// Function to set the engine speed using PWM.
void set_engine_speed(uint8_t duty_cycle) {
    uint slice_num = pwm_gpio_to_slice_num(ENGINE_PIN); // Get the PWM slice number for the given GPIO pin.
    pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle); // Set the PWM duty cycle to control the engine speed (0-255).
}