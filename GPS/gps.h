
/*
 * gps.h
 *
 * Created: 9/13/2019 7:19:25 PM
 *  Author: Areeb
 */
#include "usart.h"
#include <sysclk.h>
#include <stdio.h>

#define USART_SERIAL                     &USARTF0
#define USART_SERIAL_BAUDRATE            9600
#define USART_SERIAL_CHAR_LENGTH         USART_CHSIZE_8BIT_gc
#define USART_SERIAL_PARITY              USART_PMODE_DISABLED_gc
#define USART_SERIAL_STOP_BIT            false


/*		Functions		*/
int initialize_gps(void);
int set_nmea_output(void);
int send_packet(char packet[], int length);

/*		Definitions		*/
char GPS_PACKET_PREAMBLE;
char GPS_PACKET_SET_NMEA_OUTPUT[];
char GPS_PACKET_SET_OUTPUT_RATE[];