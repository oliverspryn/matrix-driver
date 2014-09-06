#include "Arduino.h"
#include "Driver.h"

Driver::Driver(Size *size, Pinout *pinout) : pinout(pinout), size(size) {
//Configure the device pinouts
	pinMode(pinout->A,      OUTPUT);
	pinMode(pinout->B,      OUTPUT);
	pinMode(pinout->C,      OUTPUT);
	pinMode(pinout->D,      OUTPUT);

	pinMode(pinout->Blue0,  OUTPUT);
	pinMode(pinout->Blue1,  OUTPUT);
	pinMode(pinout->Green0, OUTPUT);
	pinMode(pinout->Green1, OUTPUT);
	pinMode(pinout->Red0,   OUTPUT);
	pinMode(pinout->Red1,   OUTPUT);

	pinMode(pinout->CLK,    OUTPUT);
	pinMode(pinout->OE,     OUTPUT);
	pinMode(pinout->STB,    OUTPUT);

//Allocate the pixel matrix memory
	int x = size->x, y = size->y;

	matrix = new Pixel*[y];

	for(int i = 0; i < y; ++i) {
		for(int j = 0; j < x; ++j) {
			matrix[i] = new Pixel(new Location(j, i), BLACK);
		}
	}

//Has the pinout struct specified the presence of pin "D"?
	hasPinD = (pinout->D >= 0);

	Serial.begin(9600);
}

Driver::~Driver() {
	delete pinout;
	delete size;
}

void Driver::clock() {
	digitalWrite(pinout->CLK, HIGH);
	digitalWrite(pinout->CLK, LOW);
}

void Driver::draw() {
	int half = size->y / 2, x = size->x;

	for(int i = 0; i < 4; ++i) {
		digitalWrite(pinout->OE, HIGH);
		setEvenColor(BLACK);
		selectRow(i);

		for(int j = 0; j < x; ++j) {
			//setEvenColor(RED);
			//setOddColor(RED);
			//clock();
		}

		//Serial.print(i);
		//	Serial.print('\n');

		latch();
		digitalWrite(pinout->OE, LOW);
	}
}

void Driver::latch() {
	digitalWrite(pinout->STB, HIGH);
	digitalWrite(pinout->STB, LOW);
}

void Driver::setEvenColor(Color color) {
	digitalWrite(pinout->Red0,   1);
	digitalWrite(pinout->Green0, 1);
	digitalWrite(pinout->Blue0,  1);
}

void Driver::setEvenColor(Colors color) {
	Color c(color);

	digitalWrite(pinout->Red0,   1);
	digitalWrite(pinout->Green0, 1);
	digitalWrite(pinout->Blue0,  1);
}

void Driver::setOddColor(Color color) {
	digitalWrite(pinout->Red1,   1);
	digitalWrite(pinout->Green1, 1);
	digitalWrite(pinout->Blue1,  1);
}

void Driver::setOddColor(Colors color) {
	Color c(color);

	digitalWrite(pinout->Red1,   1);
	digitalWrite(pinout->Green1, 1);
	digitalWrite(pinout->Blue1,  1);
}

void Driver::selectRow(int row) {
	int half = size->y / 2;

//Ensure the specified row is within range
	if (row < 0 || row >= half)
		return;

//Determine the bit pattern to target the specified row
	int a = row & 1; // OR row & 0b0001
	int b = row & 2; // OR row & 0b0010
	int c = row & 4; // OR row & 0b0100
	int d = 0;
	
	if (hasPinD)
		d = row & 8; // OR row & 0b1000

//Signal the specified row
	digitalWrite(pinout->A, a);
	digitalWrite(pinout->B, b);
	digitalWrite(pinout->C, c);

	if (hasPinD)
		digitalWrite(pinout->D, d);
}