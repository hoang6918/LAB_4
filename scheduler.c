/*
 * scheduler.c
 *
 *  Created on: Nov 8, 2022
 *      Author: shiba
 */

#include"scheduler.h"

unsigned char g = 0;


void SCH_Init() {
    unsigned char i;
    for (i = 0; i < SCH_MAX_TASKS; i++) {
    	SCH_Delete_Task(i);
    }
}

void SCH_Add_Task ( void (* pFunction ) () , unsigned int DELAY ,unsigned int PERIOD )
{
	 int space_1 = 0;
	 int space_2 = 0;

	 for ( space_1 = 0; space_1 < SCH_MAX_TASKS ; space_1 ++) { // TIM VI TRI TRONG VOI TASK GAN NHAT
	 if( SCH_TASKS_QUEUE [ space_1 ]. pTask == 0) {
	 break ;
	 }
	}
	 if( space_1 == SCH_MAX_TASKS ) // NEU KHONG CON VI TRI TRONG THI THOAT HAM ADD_TASK
		 {
		 return ;
		 }

	 if( SCH_TASKS_QUEUE [0]. pTask == 0 ) // TRUONG HOP QUEUE BAN DAU CHUA CO TASK
	 {
	 SCH_TASKS_QUEUE [0]. Delay = DELAY ;
	 SCH_TASKS_QUEUE [0]. pTask = pFunction ;
	 SCH_TASKS_QUEUE [0]. RunMe = 0;
	 SCH_TASKS_QUEUE [0]. Period = PERIOD ;
	 }
	 else // TRUONG HOP QUEUE DA CO IT NHAT 1 TASK
	 {
	  int New_delay = DELAY ;

	 for (int i = 0; i <= space_1 ; i ++) {
		if( SCH_TASKS_QUEUE [ i ]. Delay <= New_delay && SCH_TASKS_QUEUE [i]. pTask ) // DELAY MOI LON HON HOAC BANG CAC DELAY CU
		{
		 New_delay = New_delay - SCH_TASKS_QUEUE [i ]. Delay ;
		 }
		 else // DELAY MOI NHO HON HOAC BANG CAC DELAY CU
		 {
		 space_2 = i ;
		 if ( SCH_TASKS_QUEUE [ i ]. pTask )
		 SCH_TASKS_QUEUE [i ]. Delay = SCH_TASKS_QUEUE [i ]. Delay - New_delay ;
		 break ;
		 }
		 }
		 for (int j = space_1 ; j > space_2 ; j --) {
		 SCH_TASKS_QUEUE [j ]. RunMe = SCH_TASKS_QUEUE [j -1]. RunMe ;
		 SCH_TASKS_QUEUE [j ]. pTask = SCH_TASKS_QUEUE [j -1]. pTask ;
		 SCH_TASKS_QUEUE [j ]. Period = SCH_TASKS_QUEUE [j -1]. Period ;
		 SCH_TASKS_QUEUE [j ]. Delay = SCH_TASKS_QUEUE [j -1]. Delay ;
		 }
		 SCH_TASKS_QUEUE [ space_2 ]. Period = PERIOD ;
		 SCH_TASKS_QUEUE [ space_2 ]. pTask = pFunction ;
		 SCH_TASKS_QUEUE [ space_2 ]. RunMe = 0;
		 SCH_TASKS_QUEUE [ space_2 ]. Delay = New_delay ;
		 }
}



void SCH_Update (){

	unsigned char Index = 0;;
	 if( SCH_TASKS_QUEUE [ Index ]. pTask ) {
	 if( SCH_TASKS_QUEUE [ Index ]. Delay <= 0) {
	 SCH_TASKS_QUEUE [ Index ]. RunMe = SCH_TASKS_QUEUE [ Index ]. RunMe + 1;
	 } else {
	 SCH_TASKS_QUEUE [ Index ]. Delay = SCH_TASKS_QUEUE [ Index ]. Delay - 1;
	 }
	 }
}

void SCH_Dispatch_Tasks ()
{
	 sTask current_task ;
	unsigned char Index = 0;

	 for ( Index = 0; Index < SCH_MAX_TASKS ; Index ++)
	 {
	 if ( SCH_TASKS_QUEUE [ Index ]. RunMe > 0)
	 {
	 SCH_TASKS_QUEUE [ Index ]. RunMe = SCH_TASKS_QUEUE [ Index ]. RunMe - 1;
	 (* SCH_TASKS_QUEUE [ Index ]. pTask )(); // CHAY TASK

	 current_task.pTask = SCH_TASKS_QUEUE [ Index ]. pTask ;
	 current_task.Period = SCH_TASKS_QUEUE [ Index ].Period ;

	 SCH_Delete_Task ( Index );
	 // XOA TASK VUA CHAY XONG ROI SAU DO ADD NGUOC LAI VAO HANG DOI

	 if( current_task.Period > 0)
	 {
	 SCH_Add_Task ( current_task.pTask , current_task.Period ,current_task.Period ) ;
	 // ADD NGUOC TASK VUA XOA VAO LAI HANG DOI
	 }

	 }

}
}
 void SCH_Delete_Task ( unsigned char current_task_index )  {

  for ( int i = current_task_index + 1; i < SCH_MAX_TASKS ; i++)
  {
  // DAY TASK KE TIEP SAU TASK VUA DUOC XOA LEN 1 DON VI
  SCH_TASKS_QUEUE [i -1]. RunMe = SCH_TASKS_QUEUE [ i ]. RunMe ;
  SCH_TASKS_QUEUE [i -1]. Delay = SCH_TASKS_QUEUE [ i ]. Delay ;
  SCH_TASKS_QUEUE [i -1]. pTask = SCH_TASKS_QUEUE [ i ]. pTask ;
  SCH_TASKS_QUEUE [i -1]. Period = SCH_TASKS_QUEUE [ i ]. Period ;
  }

 }

