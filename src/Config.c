/*************	Magic	Numbers	***************/
/***********State Machine Definitions*************/
/*************	Global Variables	***************/
/*************Function	Prototypes***************/

/*************	Header Files	***************/
#include <stddef.h>
#include "Config.h"
#include "Pins.h"
#include "scheduler.h"
#include "HiddenObject.h"

/************* Semantic Versioning***************/
//This project requires the Pins library to fulfill it's roll
#ifdef FEATURE_PINS
	#ifndef PINS_LIBRARY
		#error "Pins library was not found"
	#endif
#endif

#ifdef FEATURE_SCHEDULER
	#ifndef SCHEDULER_LIBRARY
		#error "Scheduler library was not found"
	#endif
#endif

#ifdef FEATURE_HIDDENOBJECT
	#ifndef HIDDENOBJECT_LIBRARY
		#error "HiddenObjects library was not found"
	#endif
#endif

/************		Config bits		*************/
#ifdef MCU_PIC24F16KA101
	#pragma config BWRP = OFF			//Boot segment may be written
	#pragma config BSS = OFF			//No boot program Flash segment
	#pragma config GWRP = OFF			//General segment may be written
	#pragma config GCP = OFF			//No protection
	#pragma config FNOSC = FRC			//Fast RC oscillator (FRC)
	#pragma config IESO = OFF			//Internal External Switchover mode disabled (Two-Speed Start-up disabled)
	#pragma config POSCMOD = NONE		//Primary oscillator disabled
	#pragma config OSCIOFNC = ON		//CLKO output disabled; pin functions as port I/O
	#pragma config POSCFREQ = HS		//Primary oscillator/external clock input frequency greater than 8 MHz
	#pragma config SOSCSEL = SOSCLP	 	//Secondary oscillator configured for low-power operation
	#pragma config FCKSM = CSDCMD		//Both Clock Switching and Fail-safe Clock Monitor are disabled
	#pragma config WDTPS = PS32768		//1 : 32,768
	#pragma config FWPSA = PR128		//WDT prescaler ratio of 1 : 128
	#pragma config WINDIS = OFF			//Standard WDT selected; windowed WDT disabled
	#pragma config FWDTEN = ON			//WDT enabled
	#pragma config BOREN = BOR3			//Brown-out Reset enabled in hardware; SBOREN bit disabled
	#pragma config PWRTEN = ON			//PWRT enabled
	#pragma config I2C1SEL = PRI		//Default location for SCL1/SDA1 pins
	#pragma config BORV = V30			//Brown-out Reset set to Highest Voltage (2.7V)
	#pragma config MCLRE = ON			//MCLR pin enabled; RA5 input pin disabled
	#pragma config ICS = PGx1			//PGC1/PGD1 are used for programming and debugging the device
	#pragma config BKBUG = OFF			//Background debugger disabled
	#pragma config DSWDTPS = DSWDTPS5	//1 : 2048 (2.1 Seconds)
	#pragma config DSWDTOSC = LPRC		//DSWDT uses LPRC as reference clock
	#pragma config RTCOSC = LPRC		//RTCC uses LPRC as reference clock
	#pragma config DSBOREN = ON		 	//Deep Sleep BOR enabled in Deep Sleep
	#pragma config DSWDTEN = OFF		//DSWDT disabled
#endif

/************Arbitrary Functionality*************/
/*************	Magic	Numbers	***************/
/***********State Machine Definitions*************/
struct MCU_t
{
#ifdef FEATURE_HIDDENOBJECT
	HiddenObject_t *HiddenObject[NUMBER_OF_HIDDENOBJECTS];
#endif//FEATURE_HIDDENOBJECT
} MCU = {NULL};

/*************	Global Variables	***************/
/*************Interrupt Prototypes***************/
#ifdef MCU_PIC24F16KA101
void __attribute__((interrupt, auto_psv)) _OscillatorFail(void);
void __attribute__((interrupt, auto_psv)) _AddressError(void);
void __attribute__((interrupt, auto_psv)) _StackError(void);
void __attribute__((interrupt, auto_psv)) _MathError(void);
#endif

/*************Function	Prototypes***************/
/************* Main Body Of Code	***************/

void Configure_MCU(void)
{
	/*************		Pins		***************/
#ifdef FEATURE_PINS
	LATA = 0;
	LATB = 0;
	TRISA = ~0;
	TRISB = ~0;
	AD1PCFG = ~0;
	
	Pin_Definition(PIN_RA0_PGC2,	Rx0,	&TRISA, &ODCA, &LATA, &PORTA);
	Pin_Definition(PIN_RA1_PGD2,	Rx1,	&TRISA, &ODCA, &LATA, &PORTA);
	Pin_Definition(PIN_RA2,			Rx2,	&TRISA, &ODCA, &LATA, &PORTA);
	Pin_Definition(PIN_RA3,			Rx3,	&TRISA, &ODCA, &LATA, &PORTA);
	Pin_Definition(PIN_RA4_PGC3,	Rx4,	&TRISA, &ODCA, &LATA, &PORTA);
	Pin_Definition(PIN_RB2,			Rx2,	&TRISB, &ODCB, &LATB, &PORTB);
	Pin_Definition(PIN_RB4_PGD3,	Rx4,	&TRISB, &ODCB, &LATB, &PORTB);
	Pin_Definition(PIN_RB7,			Rx7,	&TRISB, &ODCB, &LATB, &PORTB);
	Pin_Definition(PIN_RB8,			Rx8,	&TRISB, &ODCB, &LATB, &PORTB);
	Pin_Definition(PIN_RB9,			Rx9,	&TRISB, &ODCB, &LATB, &PORTB);
	Pin_Definition(PIN_RB12,		Rx12,	&TRISB, &ODCB, &LATB, &PORTB);
	Pin_Definition(PIN_RB13,		Rx13,	&TRISB, &ODCB, &LATB, &PORTB);
	Pin_Definition(PIN_RB14,		Rx14,	&TRISB, &ODCB, &LATB, &PORTB);
	Pin_Definition(PIN_RB15,		Rx15,	&TRISB, &ODCB, &LATB, &PORTB);
							 
	Pin_Initialize(PIN_RA0_PGC2,	LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RA1_PGD2,	LOW, PUSH_PULL, INPUT);
	Pin_Initialize(PIN_RA2,			LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RA3,			LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RA4_PGC3,	LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RB2,			LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RB4_PGD3,	LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RB7,			LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RB8,			LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RB9,			LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RB12,		LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RB13,		LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RB14,		LOW, PUSH_PULL, OUTPUT);
	Pin_Initialize(PIN_RB15,		LOW, PUSH_PULL, OUTPUT);
#endif

	/*************	 HiddenObjects  ***************/
#ifdef FEATURE_HIDDENOBJECT
	HO_Aquire_HiddenObject_Object(&MCU.HiddenObject[HIDDENOBJECT_], HIDDENOBJECT_);
	HO_Reset_HiddenObject(MCU.HiddenObject[HIDDENOBJECT_]);
#endif

	/*************		Scheduler	 ***************/
#ifdef FEATURE_SCHEDULER
	Initialize_Scheduler(1, MILLISECOND);
#endif

	/*************	Start-Up Complete ***************/
#ifdef FEATURE_SCHEDULER
	while(1)
	{
		while(Waiting_To_Run_Tasks())
		{
			asm("ClrWdt");
			Task_Master();
		}
	}
#endif

	return;
}

/* ****************************************************************
* Standard Exception Vector handlers if ALTIVT (INTCON2<15>) = 0	*
*																 *
* These are suggested by microchip								*
******************************************************************/
#ifdef MCU_PIC24F16KA101
void __attribute__((interrupt, auto_psv)) _OscillatorFail(void)
{
	asm("ClrWdt");
	INTCON1bits.OSCFAIL = 0;
}

void __attribute__((interrupt, auto_psv)) _AddressError(void)
{
	asm("ClrWdt");
	INTCON1bits.ADDRERR = 0;
	asm("reset");
}

void __attribute__((interrupt, auto_psv)) _StackError(void)
{
	asm("ClrWdt");
	INTCON1bits.STKERR = 0;
	asm("reset");
}

void __attribute__((interrupt, auto_psv)) _MathError(void)
{
	asm("ClrWdt");
	INTCON1bits.MATHERR = 0;
	asm("reset");
}

void __attribute__((interrupt, auto_psv)) _DefaultInterrupt(void)
{
	/*
	 * Intentionally stall the processor during an unexpected interrupt to make
	 * it apparent, this is done so a proper interrupt handler can be written
	*/
	while(1);
	return;
}
#endif
