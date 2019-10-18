/*
 * TMU.h
 *
 *  Created on: Oct 12, 2019
 *      Author: Randa
 */

#ifndef TMU_H_
#define TMU_H_

#include "std_types.h"
#include "TMU_cfg.h"
#include "TIMER.h"
#include <avr/io.h>

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2

void TMU_init(const uint8 Timer_ID);
void TMU_start(const TMU_Servicing_Functions FUNC);
void TMU_stop(uint8 index);
void TMU_Dispacher(void);
void TMU_Deinit(const uint8 Timer_ID);

#endif /* TMU_H_ */
