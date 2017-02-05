/*
 * adc.h
 * Simple functions for initializing and reading the ADC pins
 
 * Created: 10-12-2016 13:28:15
 *  Author: Douwe
 */ 

#include <avr/io.h>

void adc_init(void){
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));  //16Mhz/128 = 125Khz the ADC reference clock
	ADMUX |= (1<<REFS0);							//Voltage reference from Avcc (5v)
	ADCSRA |= (1<<ADEN);							//Turn on ADC
	ADCSRA |= (1<<ADSC);							//Do an initial conversion because this one is the slowest and to ensure that everything is up and running
}

volatile uint16_t read_adc(uint8_t channel){
	ADCW = 0;
	ADMUX &= 0xF0;                    //Clear the older channel that was read
	ADMUX |= channel;                //Defines the new ADC channel to be read
	ADCSRA |= (1<<ADSC);                //Starts a new conversion
	while(ADCSRA & (1<<ADSC));            //Wait until the conversion is done
	return ADCW;                    //Returns the ADC value of the chosen channel
}