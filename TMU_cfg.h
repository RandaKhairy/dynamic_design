/*
 * TMU_cfg.h
 *
 *  Created on: Oct 12, 2019
 *      Author: Randa
 */

#ifndef TMU_CFG_H_
#define TMU_CFG_H_

#include "std_types.h"

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2

#define BUFFER_LENGTH 5

typedef struct
{
	uint8 Timer;
	uint8 resolution;
}TMU_ConfigType;


extern TMU_ConfigType TMU_cfg;

#endif /* TMU_CFG_H_ */
