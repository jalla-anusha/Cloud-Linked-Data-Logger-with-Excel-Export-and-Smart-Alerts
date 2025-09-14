#include <lpc21xx.h>
#include "pin_function_defines.h"
#include "defines.h"
#include "types.h"

u8 i_flag=0;

void eint0_isr(void) __irq
{
	i_flag=1;
	SCLRBIT(EXTINT,0);//clear flag
	VICVectAddr=0;//dummy write;
}	

void Enable_EINT0(void)
{
	CFGPIN(PINSEL1,0,FUNC2);
	SETBIT(VICIntEnable,14);
	VICVectCntl1=0x20|14;
	VICVectAddr1=(unsigned)eint0_isr;
	
	//Enable EINT0 
	//SSETBIT(EXTINT,0) //default
	
	//EINT0 as EDGE_TRIG
  SETBIT(EXTMODE,0);
	//EINT0 as REDGE
  //SETBIT(EXTPOLAR,0);	
}	
