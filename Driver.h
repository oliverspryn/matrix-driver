#ifndef DRIVER_H
#define DRIVER_H

#include "Structs.h"

class Driver {
public : 
	Driver(Size *size, Pinout *pinout);
	~Driver();

	void draw();

protected : 
	bool hasPinD;
	Pixel** matrix;
	Pinout *pinout;
	Size *size;

private : 
	void clock();
	void latch();
	void setEvenColor(Color color);
	void setEvenColor(Colors color);
	void setOddColor(Color color);
	void setOddColor(Colors color);
	void selectRow(int row);
};

#endif