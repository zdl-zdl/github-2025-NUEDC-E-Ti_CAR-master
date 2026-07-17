#ifndef __UTILS_H
#define __UTILS_H

#include "stdint.h"

typedef enum
{
	First = 1,
	Second
}SelectTask_e;

void System_Init(void);
void TaskSelect(void);
void Wait_For_A_While(void);

extern uint8_t lap_num;
extern uint8_t task_num;
extern uint8_t total_start_flag;
extern uint8_t wait_flag;
extern uint8_t debug_no_turn;
extern uint8_t debug_motor_stop;

void DebugPrint(void);

#endif