/*
 * adc.h
 * Simple functions for initializing and reading the ADC pins
 
 * Created: 10-12-2016 13:28:15
 *  Author: Douwe
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init(void);
int16_t read_adc(uint8_t channel);



#endif /* ADC_H_ */