#include "pico/stdlib.h"

#define LED_PIN 25

void setup_led() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void turn_on_led() {
    gpio_put(LED_PIN, 1);
}