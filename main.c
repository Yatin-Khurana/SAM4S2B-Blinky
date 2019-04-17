/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
void delay(int del);
void pll(void);
int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();
	pll();
	PIOA->PIO_PER |= 0xFF;
	PIOA->PIO_OWER |= 0XFF;
	PIOA->PIO_OER |= 0xFF;
	PIOA->PIO_PPDER |= 0XFF;
	/* Insert application code here, after the board has been initialized. */
	while(1){
		PIOA->PIO_SODR |= 0xFF;
		delay(1000);
		PIOA->PIO_CODR |= 0xFF;
		delay(1000);
	}
}
void delay(int del){
	for(int x=0;x<=1000;x++)
	for(int y=0;y<=1000;y++);
}
void pll(){
	PMC->CKGR_MOR |= (CKGR_MOR_MOSCRCEN);// Enable Internal Clock Source
	PMC->CKGR_MOR |= (CKGR_MOR_MOSCRCF_12_MHz);// Configures Internal 12Mhz
	PMC->CKGR_PLLAR |= CKGR_PLLAR_ONE; // Enter PLLA Programming Mode
	PMC->CKGR_PLLAR |= (CKGR_PLLAR_DIVA(1))|CKGR_PLLAR_MULA(9); // Sets PLLA to 120Mhz Divisor 1 and Multiplier 10 (9+1)
	PMC->CKGR_PLLAR |= ~CKGR_PLLAR_ONE; // Exits/ Disables PllA Programming
	PMC->PMC_MCKR |= PMC_MCKR_CSS_PLLA_CLK;
	while(((PMC->PMC_SR)&0x0003000B)!=(0x0003000B)); // Wait For PLLA to Lock and System to Stabilize at 120Mhz
}