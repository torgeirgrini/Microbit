#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "gpio.h"

#define RXD_PIN 25
#define TXD_PIN 24
#define BAUD_RATE 0x00275000

void uart_init();
void uart_send(char letter);
char uart_read();


#endif