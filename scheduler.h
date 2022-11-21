/*
 * scheduler.h
 *
 *  Created on: Nov 8, 2022
 *      Author: shiba
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include"stdint.h"
#include"main.h"

typedef struct {
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;

	uint32_t TaskID;
} sTask;

#define SCH_MAX_TASKS 40

#define RETURN_NORMAL 1
#define RETURN_ERROR 2

#define ERROR_SCH_CANNOT_DELETE_TASK 3
#define ERROR_SCH_TOO_MANY_TASK 4

sTask SCH_TASKS_QUEUE[SCH_MAX_TASKS];

unsigned char  Error_code_G ;
unsigned char Return_code ;
unsigned char g;
#define TICK 10

void SCH_Init();
void SCH_Add_Task ( void (* pFunction ) () , unsigned int DELAY ,unsigned int PERIOD );
void SCH_Update ();
void SCH_Dispatch_Tasks ();
void SCH_Delete_Task ( unsigned char current_task_index );
#endif /* INC_SCHEDULER_H_ */
