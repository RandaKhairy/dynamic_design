/*
 * TMU_Pbcfg.c
 *
 *  Created on: Oct 12, 2019
 *      Author: Randa
 */

#include "TMU_Pbcfg.h"

TMU_FunctionStart functionsDet[NUM_OF_FUNCTIONS] = {
		{toggelLED1, 3u, PERIODDIC,NA},
		{toggelLED2, 5u, PERIODDIC,NA},
		{toggelLED3, 10u, ONE_SHOT,NA}
};
