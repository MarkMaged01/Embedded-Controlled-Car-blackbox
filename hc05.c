#include "hc05.h"

// Initialize HC-05 Bluetooth module by setting up UART
// void hc05_init(uart_inst_t *uart, uint baud_rate, uint tx_pin, uint rx_pin) {
//     // Initialize the UART for communication
//     uart_init(uart, baud_rate);

//     // Set the GPIO pins for UART TX and RX
//     gpio_set_function(tx_pin, GPIO_FUNC_UART);
//     gpio_set_function(rx_pin, GPIO_FUNC_UART);

//     // Configure UART with 8 data bits, 1 stop bit, and no parity
//     uart_set_format(uart, 8, 1, UART_PARITY_NONE);

//     // Enable FIFO for UART
//     uart_set_fifo_enabled(uart, true);
// }

// Send data to HC-05 via UART
void hc05_send_data(uart_inst_t *uart, const char *data) {
    while (*data) {
        // Send each character from the string
        uart_putc(uart, *data);
        data++;  // Move to the next character
    }
}
