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
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# Basic usage of on-board LED and button
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
#include main.h>


int main (void)
{
	board_init();
	ioport_set_pin_level(LED_0_PIN, !LED_0_ACTIVE); // disable LED
	
	int status = initialize_bmp280();
	error_check(status);
	
	int temperature, pressure;
	while (1)
	{
		status = bmp280_poll_sensor();	
		error_check(status);
		
		temperature = bmp280_read_temperature();
		pressure = bmp280_read_pressure_32bit();
		
		while(!eeprom_is_ready()){}
		eeprom_write_word(12, temperature);	// Store status in EEPROM		
		while(!eeprom_is_ready()){}
		eeprom_write_word(24, pressure);	// Store status in EEPROM		
		_delay_ms(1000); // Sensor polls every 1000ms
	}

}

/*!
 * @brief Checks the status code and freezes the program if anything goes wrong
 * 
 *  @param[in] status: the status code from bmp280 functions
 */
void error_check(int status)
{		
	if(status < 0)
	{
		ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE); // Turn on the LED as an error status indicator
		while(!eeprom_is_ready()){}
		eeprom_write_word(0, status);	// Store status in EEPROM
		for(;;){} // Don't continue
	}	
}

/*
if (ioport_get_pin_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
	// Yes, so turn LED on. 
	ioport_set_pin_level(LED_0_PIN, LED_0_ACTIVE);
	} else {
	// No, so turn LED off. 
	ioport_set_pin_level(LED_0_PIN, !LED_0_ACTIVE);
}*/
