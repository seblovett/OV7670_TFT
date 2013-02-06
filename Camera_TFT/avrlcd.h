/*
 *  avrlcd.h
 *  
 *
 *  Created by Steve Gunn on 27/08/2012.
 *  Copyright 2012 University of Southampton. All rights reserved.
 *
 */

#include <avr/io.h>
#include <util/delay.h>

#define CTRL_PORT	PORTD
#define CTRL_DDR	DDRD
#define CTRL_PIN	PIND
#define DATA_PORT	PORTB
#define DATA_DDR	DDRB
#define DATA_PIN	PINB
#define CS			0
#define BLC			1
#define RESET		2
#define WR			3
#define RS			4
#define RD			5
#define VSYNC		6
#define FMARK		7

#define CONTROLPORT	PORTA
#define DATAOUT     DATA_DDR = 0xFF; // Output
#define DATAIN      DATA_DDR = 0x00; // Input


#define CS_lo()		CTRL_PORT &= ~_BV(CS)
#define CS_hi()		CTRL_PORT |= _BV(CS)
#define BLC_lo()	CTRL_PORT &= ~_BV(BLC)
#define BLC_hi()	CTRL_PORT |= _BV(BLC)
#define RESET_lo()	CTRL_PORT &= ~_BV(RESET)
#define RESET_hi()	CTRL_PORT |= _BV(RESET)
#define WR_lo()		CTRL_PORT &= ~_BV(WR)
#define WR_hi()		CTRL_PORT |= _BV(WR)
#define RS_lo()		CTRL_PORT &= ~_BV(RS)
#define RS_hi()		CTRL_PORT |= _BV(RS)
#define RD_lo()		CTRL_PORT &= ~_BV(RD)
#define RD_hi()		CTRL_PORT |= _BV(RD)
#define VSYNC_lo()	CTRL_PORT &= ~_BV(VSYNC)
#define VSYNC_hi()	CTRL_PORT |= _BV(VSYNC)
#define WRITE(x)	DATA_PORT = (x)

#define CS0		CTRL_PORT &= ~_BV(CS)
#define CS1		CTRL_PORT |= _BV(CS)
#define BLC0	CTRL_PORT &= ~_BV(BLC)
#define BLC1	CTRL_PORT |= _BV(BLC)
#define RESET0	CTRL_PORT &= ~_BV(RESET)
#define RESET1	CTRL_PORT |= _BV(RESET)
#define WR0		CTRL_PORT &= ~_BV(WR)
#define WR1		CTRL_PORT |= _BV(WR)
#define RS0		CTRL_PORT &= ~_BV(RS)
#define RS1		CTRL_PORT |= _BV(RS)
#define RD0		CTRL_PORT &= ~_BV(RD)
#define RD1		CTRL_PORT |= _BV(RD)
#define VSYNC_lo()	CTRL_PORT &= ~_BV(VSYNC)
#define VSYNC_hi()	CTRL_PORT |= _BV(VSYNC)
#define WRITE(x)	DATA_PORT = (x)

void init_ports()
{
	/* Disable JTAG in software, so that it does not interfere with Port C  */
	/* It will be re-enabled after a power cycle if the JTAGEN fuse is set. */
	MCUCR |=(1<<JTD);
	MCUCR |=(1<<JTD);
	
	CTRL_DDR = 0x7F;
	DATA_DDR = 0xFF;
}

void delay_ms(uint16_t m)
{
	uint16_t i;
	for(i=0; i<m; i++)
		_delay_ms(1);
}
