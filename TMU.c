/*
 * TMU.c
 *
 *  Created on: Oct 12, 2019
 *      Author: Randa
 */

#include "TMU.h"

TMU_FunctionStart buff[BUFFER_LENGTH]={0};

static uint8 lastIndex = 0;

void TMU_init(const TMU_ConfigType * ConfigPtr)
{
	timers[0].timer = ConfigPtr->Timer;
	TIMER_init();
}

void TMU_start(uint8 index)
{
	buff[lastIndex]= functionsDet[index];
	lastIndex++;
}

void TMU_stop(uint8 index)
{
	buff[index] = buff[lastIndex-1];
	lastIndex--;
	//deleteFunction(index);
}

void TMU_Dispacher(void)
{
	uint8 loop_index;

	for(loop_index=0;loop_index<lastIndex;loop_index++)
	{

	}

}
