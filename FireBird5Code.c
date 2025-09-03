#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Configuring the 8-pin ports
void motion_pin_config (void){
	DDRA = DDRA | 0X0F;
	PORTA = PORTA & 0xF0;
	DDRL = DDRL | 0x18;
	PORTL = PORTL | 0x18;
}

//Initializing the ports
void init_ports(){
	motion_pin_config();
}

//Initializing the output pins
void timer5_init(){
	TCCR5A = 0xA9;
	TCCR5B = 0x00;
	TCNT5H = 0xFF;
	TCNT5L = 0x01;
	OCR5AH = 0x00;
	OCR5AL = 0xFF;
	OCR5BH = 0x00;
	OCR5BL = 0xFF;
	OCR5CH = 0x00;
	OCR5CL = 0xFF;
}

//Initialing the motor pins
void velocity (unsigned char left_motor, unsigned char right_motor){
	OCR5AL = (unsigned char)left_motor;
	OCR5BL = (unsigned char)right_motor;
}

//Setting up the motors
void motion_set(unsigned char Direction){
	unsigned char PortARestore = 0;
	
	Direction &= 0x0F;
	PortARestore = PORTA;
	PortARestore &= 0xF0;
	PortARestore |= Direction;
	PORTA = PortARestore;
}

void forward(void){
	motion_set(0x06);
}

void backward(void){
	motion_set(0x09);
}

void left(void){
	motion_set(0x05);
}

void right(void){
	motion_set(0x0A);
}

void stop(void){
	motion_set(0x00);
}

void init_devices(void){
	cli();
	init_ports();
	timer5_init();
	sei();
}

//The driver function
int main(void){
	
	init_devices();
	
	while(1){
		//Move Foward
		velocity(100,100);
		forward();
		_delay_ms(1000);
		
		
		stop();
		_delay_ms(500);
		
		//Move Backward
		velocity(255,255);
		backward();
		_delay_ms(1000);
		
		stop();
		_delay_ms(500);
		
		//Rotate Right
		velocity(150,20);
		forward();
		_delay_ms(1000);
		
		stop();
		_delay_ms(500);
		
		//Rotate Left
		velocity(20,150);
		forward();
		_delay_ms(1000);
		
		stop();
		_delay_ms(500);
		
	}
}