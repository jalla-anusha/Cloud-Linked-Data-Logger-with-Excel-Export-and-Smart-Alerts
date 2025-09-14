#include<lpc21xx.h>
#include<stdlib.h>
#include "types.h"
#include "delay.h"
#include "defines.h"
#include "lcd.h"
#include "keypad_defines.h"

u8 kpmlut[4][4]=
{
'1','2','3','A',
'4','5','6','B',
'7','8','9','C',
'*','0','#','D'
};
u8 codes[4]={0xe,0xd,0xb,0x7};
u32 num;

void initkpm(void)
{
	WRITENIBBLE(IODIR1,ROW0,15);
}

u8 colscan(void)
{
	u32 t;
	t=READNIBBLE(IOPIN1,COL0);
	t=(t<15)?0:1;
	return t;
}

u8 Rowcheck(void)
{
	u8 rno,i;
	for(i=0;i<4;i++)
	{
		WRITENIBBLE(IOPIN1,ROW0,codes[i]);
		if(!colscan())
		{
			rno=i;
			break;
		}
	}
	WRITENIBBLE(IOPIN1,ROW0,0);
	return rno;
}

u8 colcheck(void)
{
	u8 cno,i;
	for(i=0;i<4;i++)
	{
		if(READNIBBLE(IOPIN1,COL0)==codes[i])
		{
		cno=i;
		break;
		}
	}
	return cno;
}

u8 keyscan(void)
{
	u8 rno,cno;
	while(colscan());
	rno=Rowcheck();
	cno=colcheck();	 
	while(!colscan());
	return kpmlut[rno][cno];
}

u32 Readnum(void)
{
	u32 i=0;
	u8 arr[20],keyval;
	Write_CMD_LCD(0xc0);
	while(1)
	{
		keyval=keyscan();
		delay_ms(100);
		if((keyval>='0')&&(keyval<='9'))
		{
			arr[i]=keyval;
			Write_DAT_LCD(arr[i]);
			i++;
		}
		else if(keyval=='D')
		{
			arr[i]='\0';
			break;
		}
		else if(keyval=='B')
		{
			i--;
			Write_CMD_LCD(0xc0+i);
			Write_DAT_LCD(' ');
			Write_CMD_LCD(0xc0+i);
		}
	}
	num=atoi((const char *)arr);
	return (num);
}
