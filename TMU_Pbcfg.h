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

typedef struct
{
	void (*functionPtr)(void) = NULL;
	uint8 delay;
	uint8 state;
};

#endif /* TMU_PBCFG_H_ */
