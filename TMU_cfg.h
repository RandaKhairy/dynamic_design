/*
 * TMU_cfg.h
 *
 *  Created on: Oct 12, 2019
 *      Author: Randa
 */

#ifndef TMU_CFG_H_
#define TMU_CFG_H_
#include "std_types.h"

#define Max_buffer_size 5

#define Periodic 0
#define One_Shot 1

#define Active 0
#define Not_Active 1


#define NA 0xff

//typedef  void (*Func_Ptr)(void);

typedef struct {
	void (*Pointer)(void);
	uint8 delay;
	uint8 Periodicity;
	uint8 Tolerance;
	uint8 Activation;
	uint8 index;
}TMU_Servicing_Functions;

extern TMU_Servicing_Functions Functions_array[Max_buffer_size];

#endif /* TMU_CFG_H_ */
