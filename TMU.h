/*
 * TMU.h
 *
 *  Created on: Oct 12, 2019
 *      Author: Randa
 */

#ifndef TMU_H_
#define TMU_H_
#include "TMU_cfg.h"

void TMU_init(const TMU_ConfigType * ConfigPtr);
void TMU_start(TMU_FunctionStart);
void TMU_stop();

#endif /* TMU_H_ */
