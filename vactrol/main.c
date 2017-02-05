/*
 * basicDrivingPWM.c
 *
 * Created: 14-10-2016 11:08:03
 * Author : Douwe
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "adc.h"


int direction = 1;

/*
ISR(TIMER2_OVF_vect){
	
	if(direction){
		OCR2A++;
		if(OCR2A == 255){
			direction = 0;
		}
	}
	if(!(direction)){
		OCR2A--;
		if(OCR2A == 0){
			direction = 1;
		}
	}
}
*/

int main(void)
{
	DDRB |= (1 << DDB3);
	DDRD |= (1 << DDB3);
	DDRB |= (1 << DDB5);
	
	i2c_init();
	
	TCCR2A	|=(1 << WGM20)	/* PHASE CORRECT PWM */
	| (1 << COM2B1)			/* Clear on up count, set on down count (NON INVERTING?) */
	| (1 << COM2A1);		/**/
	TCCR2B	|= (1 << CS22);	/* No prescalar */
	
	//TIMSK2 |= (1 << TOIE2); // Interrupt overflow interrupt
	adc_init();
	
	uint16_t pitch;

	
	    //init lcd
	    lcd_init(LCD_DISP_ON_BLINK);

	    //lcd go home
	    lcd_home();
    while (1) 
    {
		pitch = (read_adc(1) / 4);
		
		
		OCR2B = pitch;
		

		
		
	
    }
}


