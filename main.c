/*
 * main.c
 *
 *  Created on: Oct 13, 2019
 *      Author: Randa
 */

#include "TMU.h"

void Toggle_LED1(void)
{
	PORTA ^= (1<<PA0);
}

void Toggle_LED2(void)
{
	PORTA ^= (1<<PA2);
}

void Toggle_LED3(void)
{
	PORTA ^= (1<<PA4);
}


TMU_Servicing_Functions Functions_array[Max_buffer_size]={
		{Toggle_LED1,3,Periodic,NA,NA,NA},
		{Toggle_LED2,6,Periodic,NA,NA,NA},
		{Toggle_LED3,12,Periodic,NA,NA,NA}
};


int main(void)
{
	DDRA |= (1u << PA0);
	DDRA |= (1u << PA2);
	DDRA |= (1u << PA4);

	PORTA &= ~(1u << PA0);
	PORTA &= ~(1u << PA2);
	PORTA &= ~(1u << PA4);


	DDRC |= (1u << PC0);
	PORTC &= ~(1u << PC0);

	TMU_init(TIMER1);

	TMU_start(Functions_array[0]);
	TMU_start(Functions_array[1]);
	TMU_start(Functions_array[2]);

	while(1)
	{
		TMU_Dispacher();
	}
	return 0;
}
