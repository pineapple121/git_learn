
#ifndef OCC_CFG_H
#define OCC_CFG_H

/* application mode */ 
#define		OSDEFAULTAPPMODE		0


//ISR function
extern		void		Ir_RealTimInt(void);



/* tasks */
//Task IDs

#define		Task1		0
#define		Task2		1
#define		Task3		2
#define		Task4		3
#define		Task5		4
#define		Task6		5
#define		Task7		6
#define		Task8		7
#define		Task9		8
#define		Task10	9
#define		Task11	10
#define		Task12	11

//task functions
//extern	void	FuncTaskError(void);
extern	void	FuncTask1(void);
extern	void	FuncTask2(void);
extern	void	FuncTask3(void);
extern	void	FuncTask4(void);
extern	void	FuncTask5(void);
extern	void	FuncTask6(void);
extern	void	FuncTask7(void);
extern	void	FuncTask8(void);
extern	void	FuncTask9(void);
extern	void	FuncTask10(void);
extern	void	FuncTask11(void);
extern	void	FuncTask12(void);




/* counters */
//COUNTER IDs
#define		SysCounter		0


/* alarms */
//ALARM configuration lists
#define		AlarmError		&osekAlarm_AlarmTable[0]




/* messages */
#if defined (OCC_LOCALMESSAGESONLY)



#endif  /* OCC_LOCALMESSAGESONLY */




#endif/*	ifndef OCC_CFG_H	*/



