#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
// #include "gy87.h"
#define BUZZER_PIN 15

void setup_buzzer() {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

void activate_buzzer() {
    gpio_put(BUZZER_PIN, 1); // Turn on buzzer
}

void deactivate_buzzer() {
    gpio_put(BUZZER_PIN, 0); // Turn off buzzer
}