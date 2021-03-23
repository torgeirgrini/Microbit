#include "gpio.h"
#include "uart.h"

int main(){
    uart_init();		
	
	while(1){

        char read = uart_read();
        uart_send(read);

	}

	return 0;
}