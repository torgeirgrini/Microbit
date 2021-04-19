#include "gpio.h"
#include "uart.h"
#include <stdio.h>
#include <unistd.h>

ssize_t _write(int fd, const void *buf, size_t count)
{
	char *letter = (char *)(buf);
	for (int i = 0; i < count; i++)
	{
		uart_send(*letter);
		letter++;
	}
	return count;
}

int main()
{
	uart_init();

	// Configure LED Matrix
	for (int i = 4; i <= 15; i++)
	{
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	int sleep = 0;
	int status = 0;
	while (1)
	{

		if (!(GPIO->IN & (1 << 26)))
		{
			uart_send('b');
		}
		if (!(GPIO->IN & (1 << 17)))
		{
			uart_send('a');
		}

		char c = uart_read();
		// Check if button B is pressed;
		// turn on LED matrix if it is.
		if (!status && c != '\0')
		{
			GPIO->OUTSET = (1 << 13);
			GPIO->OUTSET = (1 << 14);
			GPIO->OUTSET = (1 << 15);
			status = 1;
		}

		// Check if button A is pressed;
		// turn off LED matrix if it is.
		else if (status && c != '\0')
		{
			GPIO->OUTCLR = (1 << 13);
			GPIO->OUTCLR = (1 << 14);
			GPIO->OUTCLR = (1 << 15);
			status = 0;
		}

		sleep = 1000;
		while (sleep)
		{
			sleep--;
		}

		//iprintf("The average grade in TTK%d was in %d and %d: %c\n\r",4235,2019,2018,'C');
	}

	return 0;
}