/*
* LedCandle.cpp
*
* Created: 28.03.2018 23:53:19
* Author : Eugene
*/

#define F_CPU 510000
//#define USE_RANDOM_SEED

#include <avr/io.h>
#include <util/delay.h>
#include "random.h"

void SetBrightness (unsigned char brightness,unsigned char delay)
{
	while(OCR0B!=brightness)
	{
		if(OCR0B>brightness)
		OCR0B--;
		else
		OCR0B++;

		for(unsigned char i=0;i<delay;i++)
		_delay_ms(1);
	}
}

int main(void)
{
	/* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0x00;

	// Таймер для ШИМ:
	TCCR0A = 0x21; // режим ШИМ, неинверсный сигнал на выходе OC0A, инверсный - на выходе OC0B
	TCCR0B = 0x01; // предделитель тактовой частоты CLK/8
	TCNT0=0; // начальное значение счётчика
	//OCR0A=0; // регистр совпадения A
	OCR0B=0; // регистр совпадения B

	uint16_t z = 333;
	random_init(z); // initialize 16 bit seed
	unsigned char last_brightness = 0;
	while (1)
	{
		unsigned char brightness = 0;
		
		while(brightness<50)
		{
			z=random();
			brightness = (z&0xFF)^(z>>8);
		}
		if(brightness<last_brightness)
			SetBrightness(brightness,40);
		else
			SetBrightness(brightness,20);

		last_brightness = brightness;


		if(brightness>180)
			_delay_ms(2000); // Пауза
		if(brightness>80)
			_delay_ms(1000); // Пауза		
		else
			_delay_ms(300); // Пауза		
	}
}

