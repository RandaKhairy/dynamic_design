/*
 * TMU.c
 *
 *  Created on: Oct 12, 2019
 *      Author: Randa
 */

#include "TMU.h"

TMU_Servicing_Functions FUNC_Buffer[Max_buffer_size]={0};

uint8 g_bufferIndex=0;
uint8 g_Timer_start_flag=0;
uint8 g_Timer_ID;

void TMU_init(const uint8 Timer_ID)
{
	//Call timer initialization function
	PORTC |= (1u << PC0);
	TIMER_init(Timer_ID);
	g_Timer_ID=Timer_ID;
}

void TMU_start(const TMU_Servicing_Functions FUNC)
{
	FUNC_Buffer[g_bufferIndex]= FUNC;
	FUNC_Buffer[g_bufferIndex].Tolerance=FUNC_Buffer[g_bufferIndex].delay;
	FUNC_Buffer[g_bufferIndex].index=g_bufferIndex;
	FUNC_Buffer[g_bufferIndex].Activation=Active;
	g_bufferIndex++;

	if(g_Timer_start_flag==0)
	{
		// Call timer start function
		TIMER_start(g_Timer_ID);
		g_Timer_start_flag=1;
	}
}

void TMU_stop(uint8 index)
{
	g_bufferIndex--;
	FUNC_Buffer[index]=FUNC_Buffer[g_bufferIndex];
}

void TMU_Dispacher(void)
{
	static uint8 time_count=0;
	uint8 loop_index;
	uint8 delay;

	if(1u==g_TIMER_flag)
	{
		time_count++;
	}


	for(loop_index=0;loop_index<g_bufferIndex;loop_index++)
	{
		delay = FUNC_Buffer[loop_index].delay;

		if((time_count >= FUNC_Buffer[loop_index].Tolerance) && (time_count < (delay+FUNC_Buffer[loop_index].Tolerance)))
		{
			void (*PTR)(void) = FUNC_Buffer[loop_index].Pointer;
			(PTR)();

			FUNC_Buffer[loop_index].Tolerance += delay;

			if(FUNC_Buffer[loop_index].Periodicity == One_Shot)
			{
				TMU_stop(FUNC_Buffer[loop_index].index);
			}
		}
	}
}

void TMU_Deinit(const uint8 Timer_ID)
{
	//Call timer stop function
	TIMER_stop(g_Timer_ID);
}

