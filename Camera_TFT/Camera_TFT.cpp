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

void SetPixel(int x, int y, ushort colour ) 
{

	
}

int main(void)
{
	LCD::Init();
	Graphics::Rectangle(0,0,240,320, _paletteW[0]);
	Graphics::BeginPixels();

	ushort colour = 0x1F;
	int x,y;//,height,width;
	x = 0;
	y = 0;
		
	LCD::SetPixel(x, y, colour);


	
    while(1)
    {

    }
}