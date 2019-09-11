
/*
 * twi.c
 *
 * Created: 9/9/2019 5:05:23 PM
 *  Author: Areeb Mohammed
 */ 

#include "twi.h"

/*!
 * @brief Function for initializing a Two Wire Interface connection with a slave device.
 * @param[in] slave_address : Slave TWI/I2C Address
 * @param[in] twi_port : The port to create the connection on.
 * @param[in] low_frequency : If true, defaults to 100kHz, else, chooses 400kHz bus speed.
 *
 

void twi_init(uint8_t slave_address, TWI_t twi_port, bool low_frequency)
{
	int speed = speed_100_kHz;
	if(!low_frequency)
		speed = speed_400_kHz;
		
	twi_master_options_t options = {
		.speed = speed,
		.chip = slave_address
	};
	twi_master_setup(&twi_port, &options);
}
*/

/*!
 * @brief Function for initializing a Two Wire Interface connection with a slave device.
 * @param[in] slave_address : Slave TWI/I2C Address
 * @param[in] twi_port : The port to create the connection on.
 * @param[in] frequency : Frequency that the bus should operate on.
 *
 */

void twi_init(uint8_t slave_address, TWI_t twi_port, int frequency)
{		
	twi_master_options_t options = {
		.speed = frequency,
		.chip = slave_address
	};
	twi_master_setup(&twi_port, &options);
}

/*!
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] twi_port  : The port the slave is on.
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

int8_t i2c_reg_write(TWI_t twi_port, uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
	twi_package_t packet_write = {
		.addr         = reg_addr,      // TWI slave memory address data
		.addr_length  = sizeof (reg_addr),    // TWI slave memory address data size
		.chip         = i2c_addr,      // TWI slave bus address
		.buffer       = reg_data, // transfer data source buffer
		.length       = length // transfer data size (bytes)
	};
	while (twi_master_write(&twi_port, &packet_write) != TWI_SUCCESS);
	if (twi_master_write(&twi_port, &packet_write) == TWI_SUCCESS)
	{
		return 0;
		} else {
		return 1;
	}
}

/*!
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] twi_port  : The port the slave is on.
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
int8_t i2c_reg_read(TWI_t twi_port, uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
	//uint8_t data_received[length];
	twi_package_t packet_read = {
		.addr         = reg_addr,      // TWI slave memory address data
		.addr_length  = sizeof (reg_addr),    // TWI slave memory address data size
		.chip         = i2c_addr,      // TWI slave bus address
		.buffer       = reg_data,        // transfer data destination buffer
		.length       = length                    // transfer data size (bytes)
	};
	// Perform a multi-byte read access
	if(twi_master_read(&twi_port, &packet_read) == TWI_SUCCESS){
		return 0;
	} else {
		return 1;
	}
}