
/*
 * gps.c
 *
 * Created: 9/13/2019 7:19:33 PM
 *  Author: Areeb
 */ 
#include "gps.h"


char GPS_PACKET_PREAMBLE = '$';
char GPS_PACKET_SET_NMEA_OUTPUT[] = "PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
int GPS_PACKET_SET_NMEA_OUTPUT_LEN = sizeof(GPS_PACKET_SET_NMEA_OUTPUT);
char GPS_PACKET_SET_OUTPUT_RATE[] = "PMTK220,1000"; // 1000ms delay

usart_rs232_options_t USART_SERIAL_OPTIONS;

int initialize_gps()
{	
	usart_rs232_options_t temp  = {
		.baudrate = USART_SERIAL_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT
	};
	USART_SERIAL_OPTIONS = temp;
	sysclk_enable_module(SYSCLK_PORT_F, PR_USART0_bm);
	bool success = usart_init_rs232(USART_SERIAL, &USART_SERIAL_OPTIONS);
	if (success)
		return 0;
	else
		return -1;
}

int send_packet(char packet[], int length)
{
	usart_put(USART_SERIAL, GPS_PACKET_PREAMBLE);
	for(int i=0; i < length; i++)
	{
		usart_put(USART_SERIAL, packet[i]);
	}
	
	usart_put(USART_SERIAL, '*');
	
	char checksum = 0;
	for(int i=0; i < length; i++)
	{
		checksum ^= packet[i];
	}
	char result [2];
	sprintf(result, "%02X", checksum);

		usart_put(USART_SERIAL, result[0]);
		usart_put(USART_SERIAL, result[1]);		

	
	usart_put(USART_SERIAL, '\r');
	usart_put(USART_SERIAL, '\n');
}

int set_nmea_output()
{
	send_packet("PMTK413", 7);
	send_packet(GPS_PACKET_SET_NMEA_OUTPUT, sizeof(GPS_PACKET_SET_NMEA_OUTPUT));
	return 0;	
}

typedef struct gps_output
{
		
};
