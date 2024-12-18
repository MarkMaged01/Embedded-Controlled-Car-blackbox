#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

// HC-05 Configuration
#define UART_ID uart0
#define BAUD_RATE 9600
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE
#define UART_TX_PIN 0 // TX Pin (Pico GP0)
#define UART_RX_PIN 1 // RX Pin (Pico GP1)

// Initialize UART for HC-05
void hc05_init() {
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

// Function to send a string via HC-05
void hc05_send(const char *data) {
    uart_puts(UART_ID, data);
}

// Function to receive a string via HC-05
// This reads until a newline (\n) or a buffer limit is reached.
int hc05_receive(char *buffer, int buffer_size) {
    int index = 0;

    while (index < buffer_size - 1) {
        // Check if data is available to read
        if (uart_is_readable(UART_ID)) {
            char ch = uart_getc(UART_ID);
            if (ch == '\n') { // End of message
                break;
            }
            buffer[index++] = ch;
        }
    }

    buffer[index] = '\0'; // Null-terminate the string
    return index; // Return the number of bytes read
}

// Example usage
int main() {
    stdio_init_all(); // Initialize stdio for debug output

    hc05_init(); // Initialize HC-05

    char receive_buffer[128];

    while (true) {
        // Check for incoming data
        if (uart_is_readable(UART_ID)) {
            int bytes_received = hc05_receive(receive_buffer, sizeof(receive_buffer));
            printf("Received: %s\n", receive_buffer);

            // Echo the received data back
            hc05_send("Echo: ");
            hc05_send(receive_buffer);
            hc05_send("\n");
        }

        sleep_ms(100); // Small delay to avoid spamming
    }

    return 0;
}
