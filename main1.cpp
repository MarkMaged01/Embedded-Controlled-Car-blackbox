// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "hardware/spi.h"
// #include "hardware/i2c.h"
// #include "hardware/uart.h"

// // SPI Defines
// // We are going to use SPI 0, and allocate it to the following GPIO pins
// // Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
// #define SPI_PORT spi0
// #define PIN_MISO 16
// #define PIN_CS   17
// #define PIN_SCK  18
// #define PIN_MOSI 19

// // I2C defines
// // This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// // Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
// #define I2C_PORT i2c0
// #define I2C_SDA 8
// #define I2C_SCL 9

// // UART defines
// // By default the stdout UART is `uart0`, so we will use the second one
// #define UART_ID uart1
// #define BAUD_RATE 115200

// // Use pins 4 and 5 for UART1
// // Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
// #define UART_TX_PIN 4
// #define UART_RX_PIN 5

// int main()
// {
//     stdio_init_all();

//     // SPI initialisation. This example will use SPI at 1MHz.
//     spi_init(SPI_PORT, 1000*1000);
//     gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
//     gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
//     gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
//     gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

//     // Chip select is active-low, so we'll initialise it to a driven-high state
//     gpio_set_dir(PIN_CS, GPIO_OUT);
//     gpio_put(PIN_CS, 1);
//     // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

//     // I2C Initialisation. Using it at 400Khz.
//     i2c_init(I2C_PORT, 400*1000);

//     gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
//     gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
//     gpio_pull_up(I2C_SDA);
//     gpio_pull_up(I2C_SCL);
//     // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

//     // Set up our UART
//     uart_init(UART_ID, BAUD_RATE);
//     // Set the TX and RX pins by using the function select on the GPIO
//     // Set datasheet for more information on function select
//     gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
//     gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

//     // Use some the various UART functions to send out data
//     // In a default system, printf will also output via the default UART

//     // Send out a string, with CR/LF conversions
//     uart_puts(UART_ID, " Hello, UART!\n");

//     // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

//     while (true) {
//         printf("Hello, world!\n");
//         sleep_ms(1000);
//     }
// }

// /**
//  * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
//  *
//  * SPDX-License-Identifier: BSD-3-Clause
//  */

// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "mpu6050true.c"
// #include "IR.h"
// #include "hardware_control.h"
// // #define SDA_PIN 4
// // #define SCL_PIN 5
// #define BUZZER_PIN 15
// #define LED_PIN 14
// #define MOTOR_PIN 16
// // #define DHT11_PIN 17
// #define irei 20


// int main()
// {
//     stdio_init_all(); // Initialize standard I/O for UART communication
//     infrared_sensor_init(irei);
//     setup_pwm(BUZZER_PIN, 1000); // 1 kHz for the buzzer
//     setup_pwm(LED_PIN, 1000);    // 1 kHz for LED brightness
//     setup_pwm(MOTOR_PIN, 500);   // 500 Hz for motor speed control

//     int16_t accel_x, accel_y, accel_z;
//     // int temperature, humidity;

//     // Initial state variables
//     bool led_on = false;
//     bool buzzer_on = false;
//     bool motor_on = false;
//     while (true)
//     {
//          if (infrared_sensor_is_triggered(irei))
//         {
//             printf("Infrared sensor not triggered!\n");
//         }
//         else
//         {
//             printf("Infrared sensor triggered.\n");
//         }
//         led_on = !led_on;
//         buzzer_on = !buzzer_on;
//         motor_on = !motor_on;
//         set_pwm_duty(BUZZER_PIN, buzzer_on ? 0.5 : 0.0); // 50% duty cycle if on, else off
//         set_pwm_duty(LED_PIN, led_on ? 0.8 : 0.0);       // 80% brightness if on, else off
//         set_pwm_duty(MOTOR_PIN, motor_on ? 0.6 : 0.6);   // 60% speed if on, else off
//         printf("LED: %s, Buzzer: %s, Motor: %s\n",
//                led_on ? "ON" : "OFF",
//                buzzer_on ? "ON" : "OFF",
//                motor_on ? "ON" : "OFF");

//         sleep_ms(1000); // Delay for 1 second
//         mpu6050_print_data();
//         sleep_ms(100); // Small delay for output frequency
//     }

//     return 0;
// }

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>
#define UART_ID uart0
#define BAUD_RATE 9600

// Define the UART pins
#define UART_TX_PIN 0  // GP0
#define UART_RX_PIN 1  // GP1

int main() {
    // Initialize stdio for USB Serial (for debugging)
    stdio_init_all();
    printf("Starting HC-05 Communication...\n");

    // Initialize UART
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Configure UART format
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);

    // Enable FIFO
    uart_set_fifo_enabled(UART_ID, true);

    // Main loop
    while (true) {
        // Check if data is available
        if (uart_is_readable(UART_ID)) {
            // Read a character
            char c = uart_getc(UART_ID);

            // Print the received character via USB Serial
            printf("Received: %c\n", c);

            // Optionally echo back to the HC-05
            uart_putc(UART_ID, c);
        }
        sleep_ms(10);  // Small delay to prevent high CPU usage
    }

    return 0;
}
