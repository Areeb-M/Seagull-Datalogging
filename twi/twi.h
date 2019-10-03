// 
// /*
//  * twi_definitions.h
//  *
//  * Created: 9/9/2019 5:14:56 PM
//  *  Author: Areeb Mohammed
//  */ 
// 
// /*		Imports			*/
// #include <asf.h>
// 
// /*		Definitions		*/
// #define speed_100_kHz 100000
// #define speed_400_kHz 400000
// 
// /*		Function Definitions		*/
// //void twi_init(uint8_t slave_address, TWI_t twi_port, bool low_frequency);
// void twi_init(uint8_t slave_address, TWI_t twi_port, uint32_t frequency);
// int8_t i2c_reg_write(TWI_t twi_port, uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
// int8_t i2c_reg_read(TWI_t twi_port, uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);