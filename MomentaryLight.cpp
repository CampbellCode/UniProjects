/*
 * MomentaryLight.cpp
 *
 * Created: 27/03/2017 8:40:20 AM
 * Author : Campbell Blake
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>

#define ButtonPushed (!(PINA & (1<<0)))

#define LightOn (PORTB |= (1<<6))
#define LightOff (PORTB &= ~(1<<6))



void setup(void);

int main(void)
{
    
	setup();
	
	
    while (1) 
    {
		char counter = 0;
		while (!ButtonPushed);
		PORTC = 0x00;
		_delay_ms(250);
		LightOn;
		_delay_ms(2000);
		
		while(counter < ADCH && !ButtonPushed)
		{	
			PORTC = counter;
			_delay_ms(227);
			counter++;
			
		}
		LightOff;

    }
}

void setup(void)
{
	ADCSRA = 0xE7; //0b11100111 Turn on. Start conversion. Free running. Slowest conversion
	ADMUX = 0x62; //0b01100010 Voltage reference. Left Adjust. Channel 2
	
	DDRB = 0x40; //Light is set to output
	PORTB = 0x00; //Light is off
	
	DDRA = 0x00; //Sets the dial to the input
	
	DDRE = 0x03;
	PORTE = 0x01; //Set multiplexer to push buttons
	
	DDRC = 0xFF; //Sets PORTC to outputs
}
