/*
 * main.c
 *
 *  Created on: Oct 13, 2019
 *      Author: Randa
 */

#include <avr/io.h>

void toggelLED1(void)
{
	PORTA ^= (1u << PA0);
}

void toggelLED2(void)
{
	PORTA ^= (1u << PA1);
}

void toggelLED3(void)
{
	PORTA ^= (1u << PA2);
}

int main(void)
{
	DDRA |= (1u << PA0) | (1u << PA1) | (1u << PA2);
	PORTA &= ~((1u << PA0) | (1u << PA1) | (1u << PA2));
}
