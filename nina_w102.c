// nina_w102.c - Implementation file for NINA-W102 library
#include "nina_w102.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>
#include <stdlib.h>

void nina_init() {
    // Debug message to check initialization
    printf("Initializing UART for NINA-W102...\n");

    // Initialize UART for communication with the NINA-W102 module
    uart_init(NINA_UART_ID, NINA_BAUD_RATE);
    gpio_set_function(NINA_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(NINA_RX_PIN, GPIO_FUNC_UART);

    // Wait for the NINA-W102 module to initialize
    sleep_ms(2000);

    // Debug message to confirm initialization
    printf("UART initialized successfully.\n");
}


void nina_send_command(const char *command) {
    printf("Sending command: %s\n", command); // Debug output
    uart_puts(NINA_UART_ID, command);
    uart_puts(NINA_UART_ID, "\r\n"); // Append CRLF
    sleep_ms(100); // Delay to allow the module to process
    printf("Command sent.\n");
}

void nina_read_response() {
    printf("Reading response...\n");
    while (uart_is_readable(NINA_UART_ID)) {
        char c = uart_getc(NINA_UART_ID);
        printf("%c", c); // Print character for debugging
    }
    printf("\nResponse read complete.\n");
}



void nina_configure(const char *name, const char *baud_rate) {
    // Send basic configuration commands
    nina_send_command("AT");          // Test communication
    nina_read_response();

    char command[50];

    // Set baud rate
    snprintf(command, sizeof(command), "AT+UART=%s,1,0", baud_rate);
    nina_send_command(command);
    nina_read_response();

    // Set Bluetooth name
    snprintf(command, sizeof(command), "AT+NAME=%s", name);
    nina_send_command(command);
    nina_read_response();

    // Set role to slave
    nina_send_command("AT+ROLE=0");
    nina_read_response();

    // Make device discoverable
    nina_send_command("AT+DISCOVERABLE=1");
    nina_read_response();

    // Reset the module
    nina_send_command("AT+RESET");
    nina_read_response();
}
