/****************************************************************************
 *
 * 		Copyright (C) 2005-2009 ESEC UESTC All Rights Reserved.
 ***************************************************************************/


/**
 * @file 	init.c
 * @brief
 * @date
 */



#include "include.h"
#include <stdio.h>
#include <string.h>


void showLogo();

int main(int argc ,char *argv[])
{

  //volatile int x=sizeof(OSDWORD);


 	BSP_UartInit(); 	
	BSP_TimerInit();
	EnableInterrupts;
	//showLogo();
	StartOS(OSDEFAULTAPPMODE);
	
	
	return 0;

}

//show LOGO
void showLogo()
{
	printf("************************************************************\n");
	printf("****************ESEC OSEK EVENT AND MESSAGE*****************\n");
	printf("************************************************************\n\n");
}

//output task ID and states
void showTaskInfo(TaskType taskId)
{
	TaskStateType taskState;
	GetTaskState(taskId, &taskState);
	printf("task id: %u, ", (int)taskId);
	switch(taskState)
	{
		case RUNNING:
			printf("taskState: running\n");
		break;
		case WAITING:
			printf("taskState: waiting\n");
		break;
		case READY:
			printf("taskState: ready\n");
		break;
		case SUSPENDED:
			printf("taskState: suspended\n");
	    break;
	    default:
	    break;
	}
}
/*************************************************
**************** Task1 ***************************
**************************************************
*/
TASK(Task1)
{	
	TaskType taskId;
	StatusType status;
	OSBYTE buf1[] = "1 to 2";
	EventMaskType mask;
	
	GetTaskID(&taskId);

	showLogo();

	
	printf("**********************task 1 running**********************\n");
	
	//show task information
	showTaskInfo(taskId); 
	//start COM module
	StartCOM();
	
  //task1 send message to task2;
  printf("task1 send Msg1: %s\n", buf1);
	SendMessage(Msg1, buf1);	
	
 	printf("**********************task 1 end**************************\n"); 
	TerminateTask();
}



/*************************************************
**************** Task2 ***************************
**************************************************
*/

TASK(Task2)
{
	TaskType taskId;
	StatusType status;
	OSBYTE buf1[20] ;
	OSBYTE buf2[] = "2 to 3";
	EventMaskType mask;
	
	GetTaskID(&taskId);
	
    printf("**********************task 2 running**********************\n");
	showTaskInfo(taskId); 
	
  //receive message from task1
	status = ReceiveMessage(Msg1, buf1);
	if(status == E_OK)
	{
	 	printf("task2 receive message Msg1: %s\n", buf1);
	} else
	{
		printf("task2 receive message error: %d\n", status);
	}
	

	//send message Msg2 to task3
	printf("task2 send Msg2: %s\n", buf2);
	SendMessage(Msg2, buf2);


	printf("**********************task 2 end**************************\n");
	TerminateTask();
}

/*************************************************
**************** Task3 ***************************
**************************************************
*/

TASK(Task3)
{
	TaskType taskId;
	StatusType status;
	OSBYTE buf1[20] ;
	OSBYTE buf2[] = "3 to 4";
	EventMaskType mask;
	
	GetTaskID(&taskId);
	
    printf("**********************task 2 running**********************\n");
	showTaskInfo(taskId); 
	
  //receive message from task2
	status = ReceiveMessage(Msg2, buf1);
	if(status == E_OK)
	{
	 	printf("task3 receive message Msg2: %s\n", buf1);
	} else
	{
		printf("task3 receive message error: %d\n", status);
	}
	

	//send message Msg1 to task4
	printf("task2 send Msg1: %s\n", buf2);
	SendMessage(Msg1, buf2);


	printf("**********************task 3 end**************************\n");
	TerminateTask();
}

/*************************************************
**************** Task4 ***************************
**************************************************
*/

TASK(Task4)
{
	TaskType taskId;
	StatusType status;
	OSBYTE buf1[20] ;
	OSBYTE buf2[] = "4 to 5";
	EventMaskType mask;
	
	GetTaskID(&taskId);
	
    printf("**********************task 4 running**********************\n");
	showTaskInfo(taskId); 
	
  //receive message from task13
	status = ReceiveMessage(Msg1, buf1);
	if(status == E_OK)
	{
	 	printf("task4 receive message Msg1: %s\n", buf1);
	} else
	{
		printf("task4 receive message error: %d\n", status);
	}
	

	//send message Msg2 to task5
	printf("task4 send Msg2: %s\n", buf2);
	SendMessage(Msg2, buf2);


	printf("**********************task 4 end**************************\n");
	TerminateTask();
}

/*************************************************
**************** Task5 ***************************
**************************************************
*/

TASK(Task5)
{
	TaskType taskId;
	StatusType status;
	OSBYTE buf1[20] ;
	EventMaskType mask;
	
	GetTaskID(&taskId);
	
    printf("**********************task 5 running**********************\n");
	showTaskInfo(taskId); 
	
  //receive message from task4
	status = ReceiveMessage(Msg2, buf1);
	if(status == E_OK)
	{
	 	printf("task5 receive message Msg2: %s\n", buf1);
	} else
	{
		printf("task5 receive message error: %d\n", status);
	}
	



	printf("**********************task 5 end**************************\n");
	TerminateTask();
}







/*************************************************
**************** Task6 ***************************
**************************************************
*/
TASK(Task6)
{ 
	TaskType taskId;
	StatusType status;
	OSBYTE buf[20];
	
	GetTaskID(&taskId);
    
    printf("**********************task 6 running**********************\n");
    showTaskInfo(taskId); 
    
  //waits for event 0x06 in order to set event for task7
	printf("task6 wait event 0x06 \n");
	WaitEvent(0x06);
	printf("task6 get event 0x06!!\n"); 
	
	//set event 0x07 for task7
	printf("task6 set event 0x07 for task7\n");
	SetEvent(Task7, 0x07);
	

	
	
    printf("**********************task 6 end**************************\n");
    TerminateTask();
}


/*************************************************
**************** Task7 ***************************
**************************************************
*/
TASK(Task7)
{ 
	TaskType taskId;
	StatusType status;
	OSBYTE buf[20];
	
	GetTaskID(&taskId);
    
    printf("**********************task 7 running**********************\n");
    showTaskInfo(taskId); 
    
  //waits for event 0x07 
	printf("task6 wait event 0x07 \n");
	WaitEvent(0x07);
	printf("task7 get event 0x07!n"); 
	
	//set event 0x08 for task8
	printf("task7 set event 0x08 for task8\n");
	SetEvent(Task8, 0x08);
	

	
	
    printf("**********************task 7 end**************************\n");
    TerminateTask();
}


/*************************************************
**************** Task8 ***************************
**************************************************
*/
TASK(Task8)
{ 
	TaskType taskId;
	StatusType status;

	
	GetTaskID(&taskId);
    
    printf("**********************task 8 running**********************\n");
    showTaskInfo(taskId); 
    
  //waits for event 0x08 in order to set event for task9
	printf("task8 wait event 0x08 \n");
	WaitEvent(0x08);
	printf("task8 get event 0x08!!\n"); 
	
	//set event 0x09 for task9
	printf("task8 set event 0x09 for task9\n");
	SetEvent(Task9, 0x09);
	

	
	
    printf("**********************task 8 end**************************\n");
    TerminateTask();
}


/*************************************************
**************** Task9 ***************************
**************************************************
*/
TASK(Task9)
{ 
	TaskType taskId;
	StatusType status;

	
	GetTaskID(&taskId);
    
    printf("**********************task 9 running**********************\n");
    showTaskInfo(taskId); 
    
  //waits for event 0x09 in order to set event for task710
	printf("task9 wait event 0x09 \n");
	WaitEvent(0x09);
	printf("task9 get event 0x09!!\n"); 
	
	//set event 0x0a for task10
	printf("task9 set event 0x0a for task10\n");
	SetEvent(Task10, 0x0a);
	

	
	
    printf("**********************task 9 end**************************\n");
    TerminateTask();
}


/*************************************************
**************** Task10 ***************************
**************************************************
*/
TASK(Task10)
{ 
	TaskType taskId;
	StatusType status;

	
	GetTaskID(&taskId);
    
    printf("**********************task 10 running**********************\n");
    showTaskInfo(taskId);
    
    
  printf("task10 set event 0x06 for task6\n");
  SetEvent(Task6,0x06); 
    
  //waits for event 0x0a
	printf("task10 wait event 0x0a \n");
	WaitEvent(0x0a);
	printf("task10 get event 0x0a!!\n"); 
	

	
	
    printf("**********************task 10 end**************************\n");
    TerminateTask();
}

