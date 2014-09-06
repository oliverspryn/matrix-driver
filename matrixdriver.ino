#include "Driver.h"

#define PA   A0
#define PB   A1
#define PC   A2
#define PD   A3

#define PB0  2
#define PB1  3
#define PG0  4
#define PG1  5
#define PR0  6
#define PR1  7

#define PCLK 8
#define POE  9
#define PSTB 10

#define X    32
#define Y    32

Driver *driver = NULL;

void setup() {
	Pinout *pinout = new Pinout();
	pinout->A      = PA;
	pinout->B      = PB;
	pinout->C      = PC;
	pinout->D      = PD;
	
	pinout->Blue0  = PB0;
	pinout->Blue1  = PB1;
	pinout->Green0 = PG0;
	pinout->Green1 = PG1;
	pinout->Red0   = PR0;
	pinout->Red1   = PR1;

	pinout->CLK    = PCLK;
	pinout->OE     = POE;
	pinout->STB    = PSTB;

	Size *size = new Size(X, Y);
	driver = new Driver(size, pinout);
}

void loop() {
	driver->draw();
}