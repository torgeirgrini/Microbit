#include "uart.h"
#define UART ((NRF_UART_REG*)0x40002000)


typedef struct {

    volatile uint32_t STARTRX;
    volatile uint32_t STOPRX;
    volatile uint32_t STARTTX;
    volatile uint32_t STOPTX;
    volatile uint32_t RESERVED0[3];
    volatile uint32_t SUSPEND;
    volatile uint32_t RESERVED1[56];

    volatile uint32_t CTS;
    volatile uint32_t NCTS;
    volatile uint32_t RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t TXDRDY;
    volatile uint32_t RESERVED3[1];
    volatile uint32_t ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t RXTO;

    volatile uint32_t RESERVED10[110];
    volatile uint32_t INTEN;
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED5[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED6[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED7[1];
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED8[1];
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED9[17];
    volatile uint32_t CONFIG;

}NRF_UART_REG;


void uart_init() {

    GPIO->PIN_CNF[TXD_PIN] = 1;
    GPIO->PIN_CNF[RXD_PIN] = 0;
    UART->PSELTXD = TXD_PIN;
    UART->PSELRXD = RXD_PIN;
    UART->BAUDRATE = BAUD_RATE;
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;
    UART->ENABLE = 4;
    UART->STARTRX = 1;
}

void uart_send(char letter) {
    UART->STARTTX = 1;
    UART->TXD = letter;
    while(!UART->TXDRDY);
    UART->TXDRDY = 0;
    UART->STOPTX = 1;
}

char uart_read() {
    if(!UART->RXDRDY) {
        return '\0';
    }
    UART->RXDRDY = 0;
    return UART->RXD;
    
}
