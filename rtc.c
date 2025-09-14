#include<lpc21xx.h>
#include "uart0.h"
#include "types.h"
#include "rtc_defines.h"

// RTC Initialization: Configures and enables the RTC
void RTC_Init(void) 
{
  // Reset the RTC
	CCR = RTC_CTC_RESET;	
  // Set prescaler integer part
	PREINT = PREINT_VAL;
  // Set prescaler fractional part
	PREFRAC = PREFRAC_VAL;
	/*
  // Enable the RTC for LPC2129
	CCR = RTC_CCR_EN;
	*/
	// Enable the RTC for LPC2148 with external clock source
	CCR = RTC_CCR_EN | RTC_CLKSRC;
}

void RTCSetTime(u32 hr,u32 mi,u32 se)
{
	HOUR = hr;
	MIN = mi;
	SEC = se;
}
