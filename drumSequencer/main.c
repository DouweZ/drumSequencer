/*
 * drumSequencer.c
 *
 * Created: 20-12-2016 17:52:32
 * Author : Douwe
 */ 

#define F_CPU 16000112


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "light_ws2812.h"
#include "sequencerData.h"

uint8_t direction = 1;
uint16_t ms;
uint16_t bpm = 120;

uint8_t endStep = 7;
uint8_t step;
uint8_t subDiv = 4;

uint16_t sequenceOne;




// OC1C (Pin13) is LED
ISR(TIMER1_COMPA_vect){	
				if(!(ms % ((120000/bpm)/subDiv))) //
				{
					// Increase step until endStep and start over
					step = ((step < endStep) ? (step + 1) : 0);
					PORTC |= ((1 & (sequenceOne >> step)) << PC0);
					_delay_ms(5);
					PORTC = 0;
					
				}
		if(ms == (120000/bpm)){ // 1000 ticks at 120bpm
			PORTB |= (1 << PB1);
			ms = 0;
		}

		else if(ms == 100){
			PORTB &= ~(1 << PB1);
				
			ms++;
		}
		else{
			ms++;
		}

	
	


}

int main(void)
{
	DDRB |= 0b110111;
	// Set up BPM counter
	//			7		6		5		4		3		2		1		0
	// ----------------------------------------------------------------------
	// TCCR1A :	COM1A1	COM1A0	COM1B1	COM1B0	COM1C1	COM1C0	WGM11	WGM10 // OC1C to toggle
	TCCR1A |=	0b00010000;
	// TCCR1C : ICNC1	ICES1	-		WGM13	WGM12	CS12	CS11	CS10 // WGM to CTC & PRESCALAR to 8
	TCCR1B |=	0b00001010;
	TIMSK1 |=	(1 << OCIE1A);
	
	DDRC |= 0b0111111;
	
	OCR1A = 999;	// 1kHz

	/*
	sequence[0] = 0b0001;
	sequence[1] = 0b0000;
	sequence[2] = 0b0100;
	sequence[3] = 0b0001;*/
	sequenceOne = 0b00010011;
	
	struct cRGB ledarray[8];
	
	// GRB
	const struct cRGB ledOff = {0,0,0};
	const struct cRGB ledOrange = {0,255,0};
	const struct cRGB ledRed = {0,0,0};
	const struct cRGB ledGreen = {255,0,0};
	const struct cRGB ledBlue = {0,0,255};
	const struct cRGB ledWhite = {32,32,32};
	const struct cRGB ledBright = {255,255,255};
	

	ledarray[1] = ledRed;
	ledarray[2] = ledOrange;
	ledarray[3] = ledRed;
	ledarray[4] = ledOrange;
	ledarray[5] = ledOrange;
	ledarray[6] = ledOrange;
	ledarray[7] = ledOrange;
	ledarray[8] = ledOrange;

	
	ws2812_setleds(ledarray, 8); 
    while(1)
    {
		
		
		
		
	
    }
}

