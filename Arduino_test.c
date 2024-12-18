// // #include <stdio.h>
// // #include "pico/stdlib.h"
// // #include "hardware/spi.h"
// // #include "hardware/i2c.h"
// // #include "hardware/uart.h"

// // // SPI Defines
// // // We are going to use SPI 0, and allocate it to the following GPIO pins
// // // Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
// // #define SPI_PORT spi0
// // #define PIN_MISO 16
// // #define PIN_CS   17
// // #define PIN_SCK  18
// // #define PIN_MOSI 19

// // // I2C defines
// // // This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// // // Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
// // #define I2C_PORT i2c0
// // #define I2C_SDA 8
// // #define I2C_SCL 9

// // // UART defines
// // // By default the stdout UART is `uart0`, so we will use the second one
// // #define UART_ID uart1
// // #define BAUD_RATE 115200

// // // Use pins 4 and 5 for UART1
// // // Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
// // #define UART_TX_PIN 4
// // #define UART_RX_PIN 5

// // int main()
// // {
// //     stdio_init_all();

// //     // SPI initialisation. This example will use SPI at 1MHz.
// //     spi_init(SPI_PORT, 1000*1000);
// //     gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
// //     gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
// //     gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
// //     gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

// //     // Chip select is active-low, so we'll initialise it to a driven-high state
// //     gpio_set_dir(PIN_CS, GPIO_OUT);
// //     gpio_put(PIN_CS, 1);
// //     // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

// //     // I2C Initialisation. Using it at 400Khz.
// //     i2c_init(I2C_PORT, 400*1000);

// //     gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
// //     gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
// //     gpio_pull_up(I2C_SDA);
// //     gpio_pull_up(I2C_SCL);
// //     // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

// //     // Set up our UART
// //     uart_init(UART_ID, BAUD_RATE);
// //     // Set the TX and RX pins by using the function select on the GPIO
// //     // Set datasheet for more information on function select
// //     gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
// //     gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

// //     // Use some the various UART functions to send out data
// //     // In a default system, printf will also output via the default UART

// //     // Send out a string, with CR/LF conversions
// //     uart_puts(UART_ID, " Hello, UART!\n");

// //     // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

// //     while (true) {
// //         printf("Hello, world!\n");
// //         sleep_ms(1000);
// //     }
// // }

// // /**
// //  * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
// //  *
// //  * SPDX-License-Identifier: BSD-3-Clause
// //  */

// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "mpu6050true.c"
// #include "IR.h"
// #include "hardware_control.h"
// // #define SDA_PIN 4
// // #define SCL_PIN 5
// #define BUZZER_PIN 15
// #define LED_PIN 25
// #define MOTOR_PIN 16
// // #define DHT11_PIN 17
// #define irei 20

// int main()
// {
//     stdio_init_all(); // Initialize standard I/O for UART communication

// infrared_sensor_init(irei);
// setup_pwm(BUZZER_PIN, 1000); // 1 kHz for the buzzer
// setup_pwm(LED_PIN, 1000);    // 1 kHz for LED brightness
// setup_pwm(MOTOR_PIN, 500);   // 500 Hz for motor speed control

// int16_t accel_x, accel_y, accel_z;
// // int temperature, humidity;

// // Initial state variables
// bool led_on = false;
// bool buzzer_on = true;
// bool motor_on = false;
// bool accident = false;
// set_pwm_duty(BUZZER_PIN, 0.5);
// set_pwm_duty(LED_PIN, 0.0);
// while (true)
// {
// if (infrared_sensor_is_triggered(irei))
// {
//     printf("Infrared sensor not triggered!\n");
//     // set_pwm_duty(BUZZER_PIN, buzzer_on ? 0.5 : 0.0);
//     // set_pwm_duty(BUZZER_PIN,  0.5);
//     // set_pwm_duty(LED_PIN ,0.0 );       // 80% brightness if on, else off
// }
// else
// {
//     printf("Infrared sensor triggered.\n");
//     accident = true;
// }

//     if (accident)
//     {
//         // set_pwm_duty(MOTOR_PIN, 0.6);
//         set_pwm_duty(BUZZER_PIN, 0.0);
//         set_pwm_duty(LED_PIN, 1.0);
//     }
//     led_on = !led_on;
//     // buzzer_on = !buzzer_on;
//     motor_on = !motor_on;
//     // 50% duty cycle if on, else off
//     // set_pwm_duty(LED_PIN, led_on ? 0.8 : 0.0);       // 80% brightness if on, else off
//     set_pwm_duty(MOTOR_PIN, motor_on ? 0.6 : 0.6); // 60% speed if on, else off
//     printf("LED: %s, Buzzer: %s, Motor: %s\n",
//            led_on ? "ON" : "OFF",
//            buzzer_on ? "ON" : "OFF",
//            motor_on ? "ON" : "OFF");

//     sleep_ms(1000); // Delay for 1 second
//     mpu6050_print_data();

//     char sensor_data[50];
//     float sensor1 = 23.5 + (rand() % 100) / 100.0;
//     float sensor2 = 45.2 + (rand() % 100) / 100.0;
//     float sensor3 = 78.9 + (rand() % 100) / 100.0;
//     snprintf(sensor_data, sizeof(sensor_data), "%.2f,%.2f,%.2f", sensor1, sensor2, sensor3);

//     // Send data over Bluetooth
//     nina_send_command(sensor_data);
//     sleep_ms(100); // Small delay for output frequency
// }

//     return 0;
// }
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "mpu6050true.c"
#include "IR.h"
#include "hardware_control.h"
// #define SDA_PIN 4
// #define SCL_PIN 5
#define BUZZER_PIN 7
#define LED_PIN 25
#define LED_PIN2 29
#define MOTOR1_speed_PIN 15
#define MOTOR1_PIN1 16
#define MOTOR1_PIN2 17
#define MOTOR2_PIN1 18
#define MOTOR2_PIN2 19
#define MOTOR2_speed_PIN 20

// #define DHT11_PIN 17
#define irei 4
#define irei_back 5

// HC-05 Configuration
#define UART_ID uart0
#define BAUD_RATE 9600
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE
#define UART_TX_PIN 0 // TX Pin (Pico GP0)
#define UART_RX_PIN 1 // RX Pin (Pico GP1)
#define MIN_SPEED 0.1f
#define MAX_SPEED 1.0f

float motor1_speed = 0.1; // Initial speed for Motor 1
float motor2_speed = 0.1; // Initial speed for Motor 2
char last_command = '\0'; // Store the last received command for comparison

// Initialize UART for HC-05
void hc05_init()
{
    // Initialize UART
    uart_init(UART_ID, BAUD_RATE);

    // Set UART pins
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Set UART parameters (data bits, stop bits, parity)
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Enable UART FIFO
    uart_set_fifo_enabled(UART_ID, true);

    printf("HC-05 initialized with baud rate %d\n", BAUD_RATE);
}

uint slice_num_pwm(uint pin, int frequency)
{
    gpio_set_function(pin, GPIO_FUNC_PWM); // Set the pin for PWM
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, 12500); // PWM resolution at 1000 Hz
    pwm_set_clkdiv(slice_num, 4.0); // Clock divider for PWM
    pwm_set_enabled(slice_num, true);
    return slice_num;
}

void motor_set_speed(uint pwm_pin, float speed)
{
    if (speed < 0.0f)
        speed = 0.0f;
    if (speed > 1.0f)
        speed = 1.0f; // Limit speed between 0.0 and 1.0

    uint slice_num = pwm_gpio_to_slice_num(pwm_pin);
    uint duty_cycle = speed * 12500; // Convert speed to PWM duty cycle
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pwm_pin), duty_cycle);
}
void set_motor_speed(float speed)
{
    if (speed > MAX_SPEED)
        speed = MAX_SPEED;
    if (speed < MIN_SPEED)
        speed = MIN_SPEED;

    motor_set_speed(MOTOR1_speed_PIN, speed);
    motor_set_speed(MOTOR2_speed_PIN, speed);
}

// Function to send a string via HC-05
void hc05_send(const char *data)
{
    uart_puts(UART_ID, data);
}

// Function to receive a string via HC-05
// This reads until a newline (\n) or a buffer limit is reached.
int hc05_receive(char *buffer, int buffer_size)
{
    int index = 0;

    while (index < buffer_size - 1)
    {
        // Check if data is available to read
        if (uart_is_readable(UART_ID))
        {
            char ch = uart_getc(UART_ID);
            if (ch == '\n')
            { // End of message
                break;
            }
            buffer[index++] = ch;
        }
    }

    buffer[index] = '\0'; // Null-terminate the string
    return index;         // Return the number of bytes read
}

// Example usage
int main()
{
    stdio_init_all(); // Initialize stdio for debug output

    hc05_init(); // Initialize HC-05
    infrared_sensor_init(irei);
    char receive_buffer[128];
    infrared_sensor_init(irei_back);
    setup_pwm(BUZZER_PIN, 1000); // 1 kHz for the buzzer
    setup_pwm(LED_PIN, 1000);    // 1 kHz for LED brightness
    setup_pwm(LED_PIN2, 1000);
    gpio_init(MOTOR1_PIN1);
    gpio_set_dir(MOTOR1_PIN1, GPIO_OUT);

    gpio_init(MOTOR1_PIN2);
    gpio_set_dir(MOTOR1_PIN2, GPIO_OUT);

    gpio_init(MOTOR2_PIN1);
    gpio_set_dir(MOTOR2_PIN1, GPIO_OUT);

    gpio_init(MOTOR2_PIN2);
    gpio_set_dir(MOTOR2_PIN2, GPIO_OUT);
    int16_t accel_x, accel_y, accel_z;
    // int temperature, humidity;
    setup_pwm(LED_PIN, 1000);
    setup_pwm(LED_PIN2, 1000);
    float motor1_speed = 0.1;
    float motor2_speed = 0.1;
    setup_pwm(MOTOR1_speed_PIN, 1000);
    setup_pwm(MOTOR2_speed_PIN, 1000);
    // Initial state variables
    bool led_on = false;
    bool buzzer_on = true;
    bool motor_on = false;
    bool accident = false;
    set_pwm_duty(BUZZER_PIN, 0.5);
    set_pwm_duty(LED_PIN, 0.0);
    set_pwm_duty(LED_PIN2, 0.0);
    bool front_detect = false;
    bool back_detect = false;
    bool Front_Object_Detected_Once = false;
    bool auto1 = false;
    while (true)
    {
        Front_Object_Detected_Once = false;
        if (infrared_sensor_is_not_triggered(irei) & infrared_sensor_is_not_triggered(irei_back))
        {
            printf("Infrared sensor not triggered!\n");
            // set_pwm_duty(BUZZER_PIN, buzzer_on ? 0.5 : 0.0);
            set_pwm_duty(BUZZER_PIN, 1.0); // buzzer off
            // set_pwm_duty(LED_PIN ,0.0 );
            // set_pwm_duty(LED_PIN ,0.0 );       // 80% brightness if on, else off
            front_detect = false;
            back_detect = false;
        }
        else
        {
            printf("Infrared sensor triggered!\n");
            if (!infrared_sensor_is_not_triggered(irei))
            {
                front_detect = true;
            }
            if (!infrared_sensor_is_not_triggered(irei_back))
            {
                back_detect = true;
            }
            set_pwm_duty(BUZZER_PIN, 0.0);
        }
        if (!infrared_sensor_is_not_triggered(irei) & receive_buffer[0] == 'F')
        {
            gpio_put(MOTOR1_PIN1, 0); // Set MOTOR1_PIN1 to high
            gpio_put(MOTOR1_PIN2, 0);
            gpio_put(MOTOR2_PIN1, 0); // Set MOTOR2_PIN1 to high
            gpio_put(MOTOR2_PIN2, 0);
            set_pwm_duty(LED_PIN, 0.0);
            set_pwm_duty(LED_PIN2, 0.0);
        }
        if (!infrared_sensor_is_not_triggered(irei_back) & receive_buffer[0] == 'B')
        {
            gpio_put(MOTOR1_PIN1, 0); // Set MOTOR1_PIN1 to high
            gpio_put(MOTOR1_PIN2, 0);
            gpio_put(MOTOR2_PIN1, 0); // Set MOTOR2_PIN1 to high
            gpio_put(MOTOR2_PIN2, 0);
            set_pwm_duty(LED_PIN, 0.0);
            set_pwm_duty(LED_PIN2, 0.0);
        }

        if (uart_is_readable(UART_ID))
        {
            int bytes_received = hc05_receive(receive_buffer, sizeof(receive_buffer));
            printf("Received: %s\n", receive_buffer);
            if (receive_buffer[0] == 'F' & !front_detect)
            {
                if (last_command == 'F')
                {
                    motor1_speed += 0.1; // Increment speed by 10%
                    motor2_speed += 0.1;
                    if (motor1_speed > 1.0)
                        motor1_speed = 1.0;
                    if (motor2_speed > 1.0)
                        motor2_speed = 1.0;
                }
                else
                {
                    motor1_speed = 0.9; // Reset to minimum speed
                    motor2_speed = 0.9;
                }
                last_command = 'F';
                gpio_put(MOTOR1_PIN1, 1); // Set MOTOR1_PIN1 to high
                gpio_put(MOTOR1_PIN2, 0);
                gpio_put(MOTOR2_PIN1, 1); // Set MOTOR2_PIN1 to high
                gpio_put(MOTOR2_PIN2, 0);
                set_pwm_duty(LED_PIN, 0.0);
                set_pwm_duty(LED_PIN2, 0.0);
                set_pwm_duty(MOTOR1_speed_PIN, motor1_speed);
                set_pwm_duty(MOTOR2_speed_PIN, motor2_speed);
                set_pwm_duty(LED_PIN, 0.0);
                set_pwm_duty(LED_PIN2, 0.0);
                printf("Forward - Speed: %.1f\n", motor1_speed);
                Front_Object_Detected_Once = false;
            }
            else if (receive_buffer[0] == 'B' & !back_detect)
            {
                if (last_command == 'B')
                {
                    motor1_speed += 0.1;
                    motor2_speed += 0.1;
                    if (motor1_speed > 1.0)
                        motor1_speed = 1.0;
                    if (motor2_speed > 1.0)
                        motor2_speed = 1.0;
                }
                else
                {
                    motor1_speed = 0.9;
                    motor2_speed = 0.9;
                }
                last_command = 'B';

                gpio_put(MOTOR1_PIN1, 0); // Set MOTOR1_PIN1 to high
                gpio_put(MOTOR1_PIN2, 1);
                gpio_put(MOTOR2_PIN1, 0); // Set MOTOR2_PIN1 to high
                gpio_put(MOTOR2_PIN2, 1);
                set_pwm_duty(MOTOR1_speed_PIN, motor1_speed);
                set_pwm_duty(MOTOR2_speed_PIN, motor2_speed);
                set_pwm_duty(LED_PIN, 1.0);
                set_pwm_duty(LED_PIN2, 1.0);
                printf("Backwards - Speed: %.1f\n", motor1_speed);
                Front_Object_Detected_Once = false;
            }
            else if (receive_buffer[0] == 'L')
            {
                gpio_put(MOTOR1_PIN1, 1); // Set MOTOR1_PIN1 to high
                gpio_put(MOTOR1_PIN2, 0);
                gpio_put(MOTOR2_PIN1, 0); // Set MOTOR2_PIN1 to high
                gpio_put(MOTOR2_PIN2, 1);
                set_pwm_duty(LED_PIN, 1.0);
                set_pwm_duty(LED_PIN2, 1.0);
                printf("left\n");
                set_pwm_duty(MOTOR1_speed_PIN, 0.9);
                set_pwm_duty(MOTOR2_speed_PIN, 0.9);
                Front_Object_Detected_Once = false;
            }
            else if (receive_buffer[0] == 'R')
            {
                gpio_put(MOTOR1_PIN1, 0); // Set MOTOR1_PIN1 to high
                gpio_put(MOTOR1_PIN2, 1);
                gpio_put(MOTOR2_PIN1, 1); // Set MOTOR2_PIN1 to high
                gpio_put(MOTOR2_PIN2, 0);
                set_pwm_duty(LED_PIN, 1.0);
                set_pwm_duty(LED_PIN2, 1.0);
                printf("right\n");
                set_pwm_duty(MOTOR1_speed_PIN, 0.9);
                set_pwm_duty(MOTOR2_speed_PIN, 0.9);
                Front_Object_Detected_Once = false;
            }
            else if (receive_buffer[0] == 'S')
            {
                gpio_put(MOTOR1_PIN1, 0); // Set MOTOR1_PIN1 to high
                gpio_put(MOTOR1_PIN2, 0);
                gpio_put(MOTOR2_PIN1, 0); // Set MOTOR2_PIN1 to high
                gpio_put(MOTOR2_PIN2, 0);
                set_pwm_duty(LED_PIN, 0.0);
                set_pwm_duty(LED_PIN2, 0.0);
                printf("stop_og\n");
            }
            else if (receive_buffer[0] == 'A') // Auto mode command
            {

                // if (front_detect && !back_detect && !Front_Object_Detected_Once)
                // {
                //     Front_Object_Detected_Once = true;
                //     gpio_put(MOTOR1_PIN1, 0);
                //     gpio_put(MOTOR1_PIN2, 0);
                //     gpio_put(MOTOR2_PIN1, 0);
                //     gpio_put(MOTOR2_PIN2, 0);
                //     printf("stop\n");
                //     sleep_ms(1000);
                //     gpio_put(MOTOR1_PIN1, 0);
                //     gpio_put(MOTOR1_PIN2, 1);
                //     gpio_put(MOTOR2_PIN1, 0);
                //     gpio_put(MOTOR2_PIN2, 1);
                //     printf("backwards\n");
                //     sleep_ms(2000);
                //     gpio_put(MOTOR1_PIN1, 0);
                //     gpio_put(MOTOR1_PIN2, 0);
                //     gpio_put(MOTOR2_PIN1, 0);
                //     gpio_put(MOTOR2_PIN2, 1);
                //     printf("right\n");
                //     sleep_ms(800);
                //     gpio_put(MOTOR1_PIN1, 1);
                //     gpio_put(MOTOR1_PIN2, 0);
                //     gpio_put(MOTOR2_PIN1, 1);
                //     gpio_put(MOTOR2_PIN2, 0);
                //     printf("Forward\n");
                // }
                // else if (front_detect && back_detect)
                // {
                //     gpio_put(MOTOR1_PIN1, 0);
                //     gpio_put(MOTOR1_PIN2, 0);
                //     gpio_put(MOTOR2_PIN1, 0);
                //     gpio_put(MOTOR2_PIN2, 0);
                //     printf("stop22\n");
                //     uart_write_blocking(UART_ID, (const uint8_t *)"Echo: ", 6);
                //     uart_write_blocking(UART_ID, (const uint8_t *)mpu6050_get_data(), strlen(mpu6050_get_data()));
                //     uart_write_blocking(UART_ID, (const uint8_t *)"\n", 1);
                // }

                printf("auto\n");
                gpio_put(MOTOR1_PIN1, 1);
                gpio_put(MOTOR1_PIN2, 0);
                gpio_put(MOTOR2_PIN1, 1);
                gpio_put(MOTOR2_PIN2, 0);
                printf("Forward_in_auto\n");
                set_pwm_duty(MOTOR1_speed_PIN, 0.76);
                set_pwm_duty(MOTOR2_speed_PIN, 0.76);
                auto1 = true;
            }
            else
            {
                printf("Char undefiened:%d\n", receive_buffer);
            }
            // Echo the received data back
            // hc05_send("Echo: ");
            // hc05_send(mpu6050_get_data());
            // hc05_send("\n");
            // sleep_ms(200); // Add a longer delay between transmissions
            // Example of using uart_write_blocking for sending data
            // mpu6050_print_data();
        }
        printf("Char undefiened:%d\n", receive_buffer[0]);
        sleep_ms(100); // Small delay to avoid spamming
        while (auto1 && !Front_Object_Detected_Once)
        {
            if (!infrared_sensor_is_not_triggered(irei) & infrared_sensor_is_not_triggered(irei_back))
            {
                set_pwm_duty(MOTOR1_speed_PIN, 0.85);
                set_pwm_duty(MOTOR2_speed_PIN, 0.85);
                gpio_put(MOTOR1_PIN1, 0);
                gpio_put(MOTOR1_PIN2, 0);
                gpio_put(MOTOR2_PIN1, 0);
                gpio_put(MOTOR2_PIN2, 0);
                printf("stop\n");
                sleep_ms(1000);

                set_pwm_duty(LED_PIN, 1.0);
                set_pwm_duty(LED_PIN2, 1.0);
                gpio_put(MOTOR1_PIN1, 0);
                gpio_put(MOTOR1_PIN2, 1);
                gpio_put(MOTOR2_PIN1, 0);
                gpio_put(MOTOR2_PIN2, 1);
                printf("backwards\n");
                sleep_ms(700);

                gpio_put(MOTOR1_PIN1, 1);
                gpio_put(MOTOR1_PIN2, 0);
                gpio_put(MOTOR2_PIN1, 0);
                gpio_put(MOTOR2_PIN2, 1);
                printf("right\n");
                sleep_ms(420);

                set_pwm_duty(LED_PIN, 0.0);
                set_pwm_duty(LED_PIN2, 0.0);
                set_pwm_duty(MOTOR1_speed_PIN, 0.75);
                set_pwm_duty(MOTOR2_speed_PIN, 0.75);
                gpio_put(MOTOR1_PIN1, 1);
                gpio_put(MOTOR1_PIN2, 0);
                gpio_put(MOTOR2_PIN1, 1);
                gpio_put(MOTOR2_PIN2, 0);
                printf("Forward\n");
            }

            else if (!infrared_sensor_is_not_triggered(irei) & !infrared_sensor_is_not_triggered(irei_back))
            {
                Front_Object_Detected_Once = true;
                gpio_put(MOTOR1_PIN1, 0);
                gpio_put(MOTOR1_PIN2, 0);
                gpio_put(MOTOR2_PIN1, 0);
                gpio_put(MOTOR2_PIN2, 0);
                printf("stop22\n");
                uart_write_blocking(UART_ID, (const uint8_t *)"Echo: ", 6);
                uart_write_blocking(UART_ID, (const uint8_t *)mpu6050_get_data(), strlen(mpu6050_get_data()));
                uart_write_blocking(UART_ID, (const uint8_t *)"\n", 1);
                auto1 = false;
                
            }
            if (receive_buffer[0] == 'F' || receive_buffer[0] == 'B' || receive_buffer[0] == 'R' || receive_buffer[0] == 'L' || receive_buffer[0] == 'L')
            {
                auto1 = false;
            }
            printf("auto\n");
            gpio_put(MOTOR1_PIN1, 1);
            gpio_put(MOTOR1_PIN2, 0);
            gpio_put(MOTOR2_PIN1, 1);
            gpio_put(MOTOR2_PIN2, 0);
            printf("Forward_in_auto\n");
        }
    }

    return 0;
}
