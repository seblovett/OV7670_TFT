/*
 * Camera_TFT.cpp
 *
 * Created: 05/02/2013 21:08:58
 *  Author: hslovett
 */ 

#define F_CPU 12000000UL
#include <avr/io.h>
#include "Graphics.h"
#include "LCD.h"
extern "C"{
	#include "ov7670.h"
	#include "TWI_Master.h"
	};
#define C16(_rr,_gg,_bb) ((ushort)(((_bb & 0xF8) << 8) | ((_gg & 0xFC) << 3) | ((_rr & 0xF8) >> 3)))

//  8 bit palette - in RAM because of graphics driver
short _paletteW[] =
{
	C16(0,0,0),
	C16(255,0,0),        // 1 red
	C16(222,151,81),     // 2 brown
	C16(255,184,255),    // 3 pink

	C16(0,0,0),
	C16(0,255,255),      // 5 cyan
	C16(71,84,255),      // 6 mid blue
	C16(255,184,81),     // 7 lt brown

	C16(0,0,0),
	C16(255,255,0),      // 9 yellow
	C16(0,0,0),
	C16(33,33,255),      // 11 blue
	
	C16(0,255,0),        // 12 green
	C16(71,84,174),      // 13 aqua
	C16(255,184,174),    // 14 lt pink
	C16(222,222,255),    // 15 whiteish
};

ISR(PCINT2_vect)
{
		//xprintf(PSTR("ISR Entered"));
		if (VSYNC_Count==1)//start a frame read
		{
			/*xprintf(PSTR("WEN Set\n"));*/
			FIFO_WEN_SET;
			VSYNC_Count++;
		}
		else if(VSYNC_Count == 2)//rising edge of pin change
		{
			VSYNC_Count++;
		}
		else if (VSYNC_Count==3)//end a frame read
		{
			FIFO_WEN_CLR;
			/*xprintf(PSTR("WEN Clear\n"));*/
		}
		else
		{
			VSYNC_Count = 0;//wait for a read to be started
		}
}

void PCINTINIT()
{
	PCICR = (1<<PCIE2); //enable PCINTs[23..16]
	PCMSK2 = (1<<PCINT18);
}
int main(void)
{
	TWI_Master_Initialise();
	LCD::Init();
	PCINTINIT();
	sei();
	Graphics::Rectangle(0,0,240,320, _paletteW[0]);
	Graphics::BeginPixels();

	ushort colour = 0x1F;
	int x,y,i,j;//,height,width;
	x = 0;
	y = 0;
		
	//LCD::SetPixel(x, y, colour);
	FIFO_init();
	if(OV7670_init() == 1)
		colour = _paletteW[12];//green
	else
		colour = _paletteW[1];
	Graphics::Rectangle(0,0, LCD::GetWidth(), LCD::GetHeight(), colour);
    while(1)
    {
		LoadImageToBuffer();
		while(VSYNC_Count != 3)
			;//wait for an image
		//reset read pointer
		FIFO_nRRST_CLR; 
		FIFO_RCLK_SET;
		FIFO_RCLK_CLR;
		FIFO_nRRST_SET;
		_delay_ms(1);
		for (j=240; j > 0; j--) //Read all data
		{

			for (i=0; i < 320; i++)
			{
				
				colour=FIFO_TO_AVR();
				colour = (char)(colour >> 8) |(((char)colour)<<8);
				LCD::SetPixel(j,i, colour);

			}
		}
		VSYNC_Count = 0;
    }
}