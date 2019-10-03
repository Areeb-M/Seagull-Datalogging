
/*
 * bmp280_driver.c
 *
 * Created: 9/9/2019 9:59:39 PM
 *  Author: Areeb Mohammed
 */ 

#include "bmp280_definitions.h"

struct bmp280_dev bmp;
struct bmp280_config conf;
struct bmp280_uncomp_data ucomp_data;

uint32_t pres32, pres64;    
int32_t temp32;
double temp, pres;

/*!
 * @brief Function to delay a certain number of ms
 * @param[in] period_ms : The number of ms to delay.
 *
 */
void delay_ms(uint32_t period_ms)
{
	_delay_ms(period_ms);
}

/*!
 * @brief Function for initializing a TWI/I2C connection with the BMP280
 * 
 *  @return Status of execution
 *  @retval 0||>0 -> Success
 *  @retval <0 -> Failure Info
 */
int initialize_bmp280(void)
{
	//twi_init(BMP280_I2C_ADDR_SEC, TWI_PORT, TWI_SPEED);
	twi_master_options_t opt = {
		.speed = TWI_SPEED,
		.chip = BMP280_I2C_ADDR_SEC
	};
	twi_master_setup(&TWI_PORT, &opt);
	
	bmp.delay_ms = delay_ms;
	bmp.dev_id = BMP280_I2C_ADDR_SEC;
	bmp.intf = BMP280_I2C_INTF;
	bmp.read = i2c_reg_read;
	bmp.write = i2c_reg_write;
	
	int result = bmp280_init(&bmp);
	if(result < 0) // Signify an error has occurred
	{return result;}
	
	// Retrieve default configuration data
	result = bmp280_get_config(&conf, &bmp);
	if(result < 0) // Signify an error has occurred
	{return result-1000;} // -1000 means that it failed at getting the config
	
	// Adjust sensor configuration
	conf.filter = BMP280_FILTER_COEFFICIENT;
	conf.os_temp = BMP280_TEMPERATURE_OVERSAMPLING;
	conf.os_pres = BMP280_PRESSURE_OVERSAMPLING;
	conf.odr = BMP280_ODR;
	
	// Upload new configuration to sensor
	result = bmp280_set_config(&conf, &bmp);
	if(result < 0)
	{return result-2000;} // -2000 means that it failed at uploading the config
		
	// Update power mode after setting configuration
	result = bmp280_set_power_mode(BMP280_POWER_MODE, &bmp);
	if(result < 0)
	{return result-3000;} // -3000 means that it failed at setting the power mode
	
	return 0; // Initialization Complete!
}

/*!
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[in] reg_data : Pointer to the data buffer whose value is to be written.
 *  @param[in] length   : No of bytes to write.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
twi_package_t packet_write = {
	.addr         = reg_addr,      // TWI slave memory address data
	.addr_length  = sizeof (reg_addr),    // TWI slave memory address data size
	.chip         = i2c_addr,      // TWI slave bus address
	.buffer       = (void *)reg_data, // transfer data source buffer
	.length       = length  // transfer data size (bytes)
};
while (twi_master_write(&TWI_PORT, &packet_write) != TWI_SUCCESS);
    /* Implement the I2C write routine according to the target machine. */
    return 0;
}

/*!
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : Sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length   : No of bytes to read.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
twi_package_t packet_read = {
	.addr         = reg_addr,      // TWI slave memory address data
	.addr_length  = sizeof (reg_addr),    // TWI slave memory address data size
	.chip         = i2c_addr,      // TWI slave bus address
	.buffer       = reg_data,        // transfer data destination buffer
	.length       = length                    // transfer data size (bytes)
};
// Perform a multi-byte read access then check the result.
if(twi_master_read(&TWI_PORT, &packet_read) == TWI_SUCCESS){
	//Check read content
}
    /* Implement the I2C read routine according to the target machine. */
    return 0;
}

/*!
 * @brief Function to get new data from the sensor. Call this before trying to read new data.
 * 
 *  @return Status of execution
 *  @retval 0||>0 -> Success
 *  @retval <0 -> Failure Info
 */
int bmp280_poll_sensor(void)
{
	return bmp280_get_uncomp_data(&ucomp_data, &bmp);
}

/*!
 * @brief Function that returns the previously polled temperature
 *	
 *  @return Temperature in degrees Celsius in integer form
 */
int32_t bmp280_read_temperature(void)
{
	bmp280_get_comp_temp_32bit(&temp32, ucomp_data.uncomp_temp, &bmp);
	return temp32;
}

/*!
 * @brief Function that returns the previously polled temperature
 *	
 *  @return Temperature in degrees Celsius with decimals
 */
double bmp280_read_temperature_double(void)
{
	bmp280_get_comp_temp_double(&temp, ucomp_data.uncomp_temp, &bmp);
	return temp;
}

/*!
 * @brief Function that returns the previously polled pressure
 *	
 *  @return Pressure with 32 bit precision
 */
int32_t bmp280_read_pressure_32bit(void)
{
	bmp280_get_comp_pres_32bit(&pres32, ucomp_data.uncomp_press, &bmp);
	return pres32;
}

/*!
 * @brief Function that returns the previously polled pressure
 *	
 *  @return Pressure with 64 bit precision
 */
int64_t bmp280_read_pressure_64bit(void)
{
	bmp280_get_comp_pres_64bit(&pres64, ucomp_data.uncomp_press, &bmp);
	return pres64;
}

/*!
 * @brief Function that returns the previously polled pressure
 *	
 *  @return Pressure as a floating point value
 */
double bmp280_read_pressure_double(void)
{
	bmp280_get_comp_pres_double(&pres, ucomp_data.uncomp_press, &bmp);
	return pres;
}