#include <string.h>
#include<stdlib.h> 
#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "esp01.h"


extern char buff[350];
extern unsigned short int i;
extern u8 rsp;

void esp01_connectAP(void)
{
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD("AT");
	delay_ms(1000);
	UART0_Str("AT\r\n");
	i=0;memset(buff,'\0',350);
	while(i<4);
	delay_ms(500);
	buff[i] = '\0';
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD(buff);
	delay_ms(2000);
	if(strstr(buff,"OK"))
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("OK");
		delay_ms(1000);		
	}
	else
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("ERROR");
		delay_ms(1000);		
		return;
	}
	
	
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD("ATE0");
	delay_ms(1000);
	UART0_Str("ATE0\r\n");
	i=0;memset(buff,'\0',350);
	while(i<4);
	delay_ms(500);
	buff[i] = '\0';
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD(buff);
	delay_ms(2000);
	if(strstr(buff,"OK"))
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("OK");
		delay_ms(1000);		
	}
	else
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("ERROR");
		delay_ms(1000);		
		return;
	}
	
	
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD("AT+CIPMUX");
	delay_ms(1000);
	UART0_Str("AT+CIPMUX=0\r\n");
	i=0;memset(buff,'\0',350);
	while(i<4);
	delay_ms(500);
	buff[i] = '\0';
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD(buff);
	delay_ms(2000);
	if(strstr(buff,"OK"))
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("OK");
		delay_ms(1000);		
	}
	else
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("ERROR");
		delay_ms(1000);		
		return;
	}
	
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD("AT+CWQAP");
	delay_ms(1000);
	UART0_Str("AT+CWQAP\r\n");
	i=0;memset(buff,'\0',350);
	while(i<4);
	delay_ms(1500);
	buff[i] = '\0';
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD(buff);
	delay_ms(2000);
	if(strstr(buff,"OK"))
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("OK");
		delay_ms(1000);		
	}
	else
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("ERROR");
		delay_ms(1000);		
		return;
	}
	
	
	
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD("AT+CWJAP");
	delay_ms(1000);
	//need to change the wifi network name and password
	UART0_Str("AT+CWJAP=\"OnePlus11r\",\"12345678\"\r\n");
	i=0;memset(buff,'\0',350);
	while(i<4);
	delay_ms(2500);
	buff[i] = '\0';
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD(buff);
	delay_ms(2000);
	if(strstr(buff,"WIFI CONNECTED"))
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("OK");
		delay_ms(1000);		
	}
	else
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("ERROR");
		delay_ms(1000);		
		return;
	}
	
}

void esp01_sendToThingspeak(char val,char n)
{
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD("AT+CIPSTART");
	delay_ms(1000);
	UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
	i=0;memset(buff,'\0',350);
	while(i<5);
	delay_ms(2500);
	buff[i] = '\0';
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD(buff);
	delay_ms(2000);
	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("OK");
		delay_ms(1000);
		
		Write_CMD_LCD(0x01);
		Write_CMD_LCD(0x80);
		Write_str_LCD("AT+CIPSEND");
		delay_ms(1000);
		UART0_Str("AT+CIPSEND=49\r\n");
		i=0;memset(buff,'\0',350);
		//while(buff[i] != '>');
		delay_ms(500);
		if(n==1)
		{
		//need to change the thingspeak write API key accordind to your channel
		UART0_Str("GET /update?api_key=QKP64LTK7BS8RO9S&field1=");
		}
		else if(n==2)
		{
		//need to change the thingspeak write API key accordind to your channel
		UART0_Str("GET /update?api_key=QKP64LTK7BS8RO9S&field2=");
		}
	/*	else if(n==3)
		{
			UART0_Str("AT+CIPSEND=72\r\n");
			i=0;memset(buff,'\0',350);
			//while(buff[i] != '>');
			delay_ms(500);			
			UART0_Str("GET /channels/2404711/fields/1.json?api_key=MGK21FQYHK9RI75B&results=1\r\n");
			buff[i]='\0';
			//strcpy((char *)arr,buff);
			extract_sp((u8 *)buff);
		} */
		//if((n==1)||(n==2))
		//{
		UART0_Int(val);
		UART0_Str("\r\n\r\n");
		delay_ms(5000);
		delay_ms(5000);
		buff[i] = '\0';
	//	}
		Write_CMD_LCD(0x01);
		Write_CMD_LCD(0x80);
		Write_str_LCD(buff);
		delay_ms(2000);
		if(strstr(buff,"SEND OK"))
		{
			Write_CMD_LCD(0x01);
			Write_str_LCD("DATA UPDATED");
			delay_ms(1000);			
		}
		else
		{
			Write_CMD_LCD(0x01);
			Write_str_LCD("DATA NOT UPDATED");
			delay_ms(1000);	
		}
		
	}
	else
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("ERROR");
		delay_ms(1000);		
		return;
	}

	
}

void espo1_ReadfromThingspeak(void)
{
	u8 arr[350];
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD("AT+CIPSTART");
	delay_ms(1000);
	UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
	i=0;memset(buff,'\0',350);
	while(i<5);
	delay_ms(2500);
	buff[i] = '\0';
	Write_CMD_LCD(0x01);
	Write_CMD_LCD(0x80);
	Write_str_LCD(buff);
	delay_ms(2000);
	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("OK");
		delay_ms(1000);
		
		Write_CMD_LCD(0x01);
		Write_CMD_LCD(0x80);
		Write_str_LCD("AT+CIPSEND");
		delay_ms(1000);
		UART0_Str("AT+CIPSEND=72\r\n");
		i=0;memset(buff,'\0',350);
		//while(buff[i] != '>');
		delay_ms(500);
		//need to change the thingspeak write API key accordind to your channel
		UART0_Str("GET /channels/3033560/fields/1.json?api_key=S6OM0F65S7MO8PO7&results=1");
		//UART0_Int(val);
		UART0_Str("\r\n");
		delay_ms(5000);
		delay_ms(5000);
		buff[i] = '\0';
		Write_CMD_LCD(0x01);
		Write_CMD_LCD(0x80);
		Write_str_LCD(buff);
		delay_ms(2000);
		strcpy((char *)arr,buff);
		if(strstr(buff,"SEND OK"))
		{
			Write_CMD_LCD(0x01);
			Write_str_LCD("DATA UPDATED");
			delay_ms(1000);			
			extract_sp(arr);
			Write_CMD_LCD(0x01);
		}
		else
		{
			Write_CMD_LCD(0x01);
			Write_str_LCD("DATA NOT UPDATED");
			delay_ms(1000);	
			Write_CMD_LCD(0x01);
		}
		
	}
	else
	{
		Write_CMD_LCD(0xC0);
		Write_str_LCD("ERROR");
		delay_ms(1000);		
		Write_CMD_LCD(0x01);
		return;
	}	
}

void extract_sp(u8 *p)
{
	u8 cnt=0,r[5],l=0;
	char *q;
	q=(char *)p;
	q=strstr((const char *)q,"field1");
	while(q)
	{
		cnt++;
		if(cnt==2)
		{
			q=strchr((const char *)q,':');
			if(q)
			{
				q=q+2;
				for(;*q!='"';q++)
				{
					r[l++]=*q;
				}
				r[l]='\0';
			}
			break;
		}	
		q++;
		q=strstr((const char *)q,"field1");
	}
	rsp=atoi((const char *)r);
	Write_CMD_LCD(0x01);
	Write_str_LCD("Remote sp: ");
	Write_int_LCD(rsp);
	delay_ms(3000);
	Write_CMD_LCD(0x01);
}
