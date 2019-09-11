
/*
 * main.h
 *
 * Created: 9/9/2019 4:47:14 PM
 *  Author: Areeb Mohammed
 */ 

/*		Imports			*/
#include <asf.h>
#include <avr/eeprom.h>
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__	// Necessary definition for _delay_ms and _delay_us from delay.h to accept variables as arguments
#include <util/delay.h>
#include <bmp280/bmp280_definitions.h>

/*		Functions		*/
int main(void);
void error_check(int status);