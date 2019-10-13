/*
 * Timers.c
 *
 *  Created on: Sep 21, 2019
 *      Author: Mariam Taha
 */

#include "TIMER.h"

volatile uint8 TIMER0_Flag_tick = 0;
volatile uint8 TIMER1_Flag_tick = 0;
volatile uint8 TIMER2_Flag_tick = 0;

static void (*g_Timer_callBackPtr)(void) = NULL;
uint8 g_delay = 0;

//Clk set function
static uint8 TIMER_start(uint8 timer)
{
	uint8 retval = OK;
	switch (timer)
	{
	case Timer0:
		if(timers[Timer0].clk_Oscillator == IN_CLK)
		{
			switch (timers[Timer0].prescalar)
			{
			case No_Prescaler:
				TCCR0 |= (1u << FOC0 )| (1u << CS00);
				break;
			case Prescaler_8:
				TCCR0 |= (1u << FOC0) |( 1u << CS01);
				break;
			case Prescaler_64:
				TCCR0 |= (1u << FOC0) | (1u << CS01) |( 1u << CS00);
				break;
			case Prescaler_256:
				TCCR0 |= (1u << FOC0) |( 1u << CS02);
				break;
			case Prescaler_1024:
				TCCR0 |= (1u << FOC0 )|( 1u << CS02 )|( 1u << CS00);
				break;
			default:
				timers[timer].is_configured = UNINITIALISED;
				retval=NOK;
			}
		}
		else if(timers[Timer0].clk_Oscillator == EX_CLK)
		{
			if(timers[Timer0].EX_clk_edge==Falling_edge)
			{
				TCCR0 = (1u << FOC0) |(1u << CS02) | (1u << CS01);
			}
			else if(timers[Timer0].EX_clk_edge==Rising_edge)
			{
				TCCR0 = (1u << FOC0) | (1u << CS02) | (1u << CS01)|( 1u << CS00);
			}
			else
			{
				timers[Timer0].is_configured = UNINITIALISED;
				retval=NOK;
			}
		}
		else
		{
			timers[Timer0].is_configured = UNINITIALISED;
			retval=NOK;
		}
		break;
	case Timer1:
		if(timers[Timer1].clk_Oscillator == IN_CLK)
		{
			switch (timers[Timer1].prescalar)
			{
			case No_Prescaler:
				TCCR1B |= (1u << CS00);
				break;
			case Prescaler_8:
				TCCR1B |= ( 1u << CS01);
				break;
			case Prescaler_64:
				TCCR1B |= (1u << CS01) | ( 1u << CS00);
				break;
			case Prescaler_256:
				TCCR1B |= ( 1u << CS02);
				break;
			case Prescaler_1024:
				TCCR1B |= ( 1u << CS02 ) | ( 1u << CS00);
				break;
			default:
				timers[Timer1].is_configured = UNINITIALISED;
				retval=NOK;
			}
		}
		else if(timers[Timer1].clk_Oscillator == EX_CLK)
		{
			if(timers[Timer1].EX_clk_edge==Falling_edge)
			{
				TCCR1B = (1u << CS02) | (1u << CS01);
			}
			else if(timers[Timer1].EX_clk_edge==Rising_edge)
			{
				TCCR1B = (1u << CS02) | (1u << CS01)|( 1u << CS00);
			}
			else
			{
				timers[Timer1].is_configured = UNINITIALISED;
				retval=NOK;
			}
		}
		else
		{
			timers[Timer1].is_configured = UNINITIALISED;
			retval=NOK;
		}
		break;
	case Timer2:
		//DDRB = 0xff;
		//PORTB = timers[Timer2].prescalar;
		if(timers[Timer2].clk_Oscillator == IN_CLK)
		{
			switch(timers[Timer2].prescalar)
			{
			case No_Prescaler:
				TCCR2 |= (1u << FOC2 )| (1u << CS20);
			break;
			}
		}
	break;
	}
	return retval;
}

//Timer modes initialization function
uint8 TIMER_init(void)
{
	uint8 retval = OK;
	uint8 loop_index;
	if(num_of_timers <= MAX_NUM_OF_TIMERS)
	{
		for(loop_index = 0; loop_index < num_of_timers; ++loop_index)
		{
			switch (timers[loop_index].timer)
			{
			case Timer0:
				TCNT0 = (uint8)timers[loop_index].Timer_reg;
				switch (timers[loop_index].mode)
				{
				case OVERFLOW:
					if(timers[loop_index].interrupt_flag == ON)
					{
						SREG  |= (1 << 7);
						TIMSK |= (1u << TOIE0);
					}
					else if(timers[loop_index].interrupt_flag == NA)
					{
						TIMSK &= ~(1u << TOIE0);
					}
					break;
				case OUTCOMP:
					TCCR0 = (1u << FOC0 | 1u << WGM01);
					OCR0 = (uint8)timers[loop_index].Compare_reg;
					if(timers[loop_index].CTC_flag == Normal_Compare_match)
					{
						if(timers[loop_index].interrupt_flag == ON)
						{
							SREG  |= (1 << 7);
							TIMSK |= (1u << OCIE0);
						}
						else if(timers[loop_index].interrupt_flag == NA)
						{
							TIMSK &= ~(1u << OCIE0);
						}
						else
						{
							timers[loop_index].is_configured = UNINITIALISED;
							retval = NOK;
						}
					}
					// if(timers[loop_index].CTC_flag == Normal_Compare_match) end
					else if(timers[loop_index].CTC_flag == Wave_generation)
					{
						//set OC0 as output pin
						DDRB  = DDRB | (1 << WG_Timer0_PIN);
						TIMSK &= ~(1u << OCIE0);
						switch (timers[loop_index].WG_PIN)
						{
						case WG_TOGGLE_Pin:
							TCCR0 = (1u << COM00);
							break;
						case WG_CLEAR_Pin:
							TCCR0 = (1u << COM01);
							break;
						case WG_SET_Pin:
							TCCR0 = (1u << COM00 | 1u << COM01);
							break;
						default:
							timers[loop_index].is_configured = UNINITIALISED;
						}
					}
					break;
				default:
					timers[loop_index].is_configured = UNINITIALISED;
					retval = NOK;
				}
				TIMER_start(Timer0);
				break;
				case Timer1:
					TCNT1 = timers[Timer1].Timer_reg;
					switch (timers[Timer1].mode)
					{
					case OVERFLOW:
					{
						TCCR1A = (1u << FOC1A) | (1u << FOC1B);
						if(timers[Timer1].interrupt_flag == ON)
						{
							SREG  |= (1u << 7);
							TIMSK |= (1u << TOIE1);
						}
						else if(timers[Timer1].interrupt_flag == NA)
						{
							TIMSK &= ~(1u << TOIE1);
						}
						else
						{
							timers[Timer1].is_configured = UNINITIALISED;
							retval = NOK;
						}
					}
					break;
					case OUTCOMP:
						TCCR1A = (1u << FOC1A) | (1u << FOC1B);
						if(timers[loop_index].CTC_flag == Normal_Compare_match)
						{
							if(timers[loop_index].Timer1_channel == CHANNEL_A)
							{
								TCCR1B = (1 << WGM12);
								OCR1A = timers[loop_index].Compare_reg;
								if(timers[loop_index].interrupt_flag == ON)
								{
									SREG  |= (1u << 7);
									TIMSK |= (1u << OCIE1A);
								}
								else if(timers[loop_index].interrupt_flag == NA)
								{
									TIMSK &= ~(1u << OCIE1A);
								}
							}
							else if(timers[loop_index].Timer1_channel == CHANNEL_B)
							{
								OCR1B = timers[loop_index].Compare_reg;
								if(timers[loop_index].interrupt_flag == ON)
								{
									SREG  |= (1u << 7);
									TIMSK |= (1u << OCIE1B);
								}
								else if(timers[loop_index].interrupt_flag == NA)
								{
									TIMSK &= ~(1u << OCIE1B);
								}
							}
						}
						else
						{
							retval = NOK;
							timers[loop_index].is_configured = UNINITIALISED;
						}
					}
					break;
					default:
					{
						retval =  NOK;
						timers[loop_index].is_configured = UNINITIALISED;
					}

					TIMER_start(Timer1);

					break;
					case Timer2:
						TCNT2 = (uint8)timers[loop_index].Timer_reg;
						switch (timers[loop_index].mode)
						{
						case OVERFLOW:
							if(timers[loop_index].interrupt_flag == ON)
							{
								SREG  |= (1 << 7);
								TIMSK |= (1u << TOIE2);
							}
							else if(timers[loop_index].interrupt_flag == NA)
							{
								TIMSK &= ~(1u << TOIE2);
							}
							break;
						case OUTCOMP:
							TCCR2 = (1u << FOC2 | 1u << WGM21);
							OCR2 = (uint8)timers[loop_index].Compare_reg;
							if(timers[loop_index].CTC_flag == Normal_Compare_match)
							{

								if(timers[loop_index].interrupt_flag == ON)
								{
									SREG  |= (1 << 7);
									TIMSK |= (1u << OCIE2);
								}
								else if(timers[loop_index].interrupt_flag == NA)
								{
									TIMSK &= ~(1u << OCIE2);
								}
								else
								{
									timers[loop_index].is_configured = UNINITIALISED;
									retval = NOK;
								}
							}
							else if(timers[loop_index].CTC_flag == Wave_generation)
							{
								TIMSK &= ~(1u << OCIE2);
								switch (timers[loop_index].WG_PIN)
								{
								case WG_TOGGLE_Pin:
									TCCR2 = (1u << COM20);
									break;
								case WG_CLEAR_Pin:
									TCCR2 = (1u << COM21);
									break;
								case WG_SET_Pin:
									TCCR2 = (1u << COM20 | 1u << COM21);
									break;
								default:
									timers[loop_index].is_configured = UNINITIALISED;
								}
							}
							break;
						default:
							timers[loop_index].is_configured = UNINITIALISED;
							retval = NOK;
						}
						TIMER_start(Timer2);
						break;
			}
		}
	}
	else
	{
		for(loop_index = 0; loop_index < num_of_timers; loop_index++)
		{
			timers[loop_index].is_configured = UNINITIALISED;
		}
		retval = NOK;
	}
	return retval;
}


void TIMER_delay(void(*ServiceFuncPtr)(void), uint8 delay)
{
	g_Timer_callBackPtr = ServiceFuncPtr;
	g_delay = ((delay * 1000) / OVERFLOW_OF_TIMER0);
	DDRB = 0xff;
	PORTB = g_delay;
}

ISR(TIMER0_OVF_vect)
{
	g_delay++;
}



