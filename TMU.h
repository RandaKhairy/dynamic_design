/*
 * TMU.h
 *
 *  Created on: Oct 12, 2019
 *      Author: Randa
 */

#ifndef TMU_H_
#define TMU_H_
#include "TMU_cfg.h"
#include "Timer.h"
#include "TMU_Pbcfg.h"

void TMU_init(const TMU_ConfigType* ConfigPtr);
void TMU_start(uint8 index);
void TMU_stop(uint8 index);

#endif /* TMU_H_ */
