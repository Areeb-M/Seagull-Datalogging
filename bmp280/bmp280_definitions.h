
/*
 * bmp280_definitions.h
 *
 * Created: 9/9/2019 5:19:27 PM
 *  Author: Areeb Mohammed
 */ 

/*		Imports			*/
#include "lib/bmp280.h"
#define __DELAY_BACKWARD_COMPATIBLE__	// Necessary flag for _delay_ms and _delay_us from delay.h to accept variables as arguments
#include <util/delay.h>

/*		Definitions		*/
#define TWI_PORT TWIF
#define TWI_SPEED 100000	// MCU supports two speeds: 100khz or 400khz

#define BMP280_DEV_ID BMP280_I2C_ADDR_SEC	// BMP280's I2C/TWI address. Since SDO isn't connected to anything, BMP280 defaults to the second address. Connecting SDO to Ground will change this to BMP280_I2C_ADDR_PRIM.
#define BMP280_INTERFACE BMP280_I2C_INTF

/*		Functions		*/
int initialize_bmp280(void);
int bmp280_poll_sensor(void);
int32_t bmp280_read_temperature(void);
double bmp280_read_temperature_double(void);
int32_t bmp280_read_pressure_32bit(void);
int64_t bmp280_read_pressure_64bit(void);
double bmp280_read_pressure_double(void);

// Filtering Coefficient
// Adjusts the IIR Filter Coefficient
// Pattern: BMP280_FILTER_X
// Options are X = OFF, COEFF_2, COEFF_4, COEFF_8, COEFF_16
#define BMP280_FILTER_COEFFICIENT BMP280_FILTER_COEFF_2

// Oversampling Configuration
// Pattern: BMP280_OS_Y
// Options are Y = NONE, 1X, 2X, 4X, 8X, 16X
// Selecting NONE disables the respective sensor
// Documented on page 12(for pressure) and page 13(for temperature) of the BMP280 Manual
#define BMP280_TEMPERATURE_OVERSAMPLING BMP280_OS_4X 
#define BMP280_PRESSURE_OVERSAMPLING BMP280_OS_4X

// Output Data Rate
// Selects how long to spend between sensor readings
// Pattern: BMP280_ODR_X_MS
// Options are X = 0_5, 62_5, 125, 250, 500, 1000, 2000, 4000
// TODO: Figure out what happens when reading sensor faster than it expects
// Refer to page 19 of the manual for the effects of choosing different data rates
#define BMP280_ODR BMP280_ODR_1000_MS

// Sensor Power Mode
// Pattern: BMP280_X
// Options are X = NORMAL_MODE, FORCED_MODE, SLEEP_MODE
// Documented on page 16 of the BMP280 manual
#define BMP280_POWER_MODE BMP280_NORMAL_MODE