/*
 * TMU_Pbcfg.h
 *
 *  Created on: Oct 12, 2019
 *      Author: Randa
 */

#ifndef TMU_PBCFG_H_
#define TMU_PBCFG_H_

#include "std_types.h"

#define PERIODDIC 0
#define ONE_SHOT 1
#define NUM_OF_FUNCTIONS 3

#define NA 0xff

typedef struct
{
	void(*functionPtr)(void);
	uint8 delay;
	uint8 state;
	uint8 start_flag;
}TMU_FunctionStart;


#endif /* TMU_PBCFG_H_ */
