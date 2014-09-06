#ifndef STRUCTS_H
#define STRUCTS_H

typedef unsigned int uint;

enum Colors {
	BLACK  = 0, // 0b000
	BLUE   = 1, // 0b001
	GREEN  = 2, // 0b010
	ORANGE = 6, // 0b110
	PURPLE = 5, // 0b101
	RED    = 4, // 0b100
	TEAL   = 3, // 0b011
	WHITE  = 7  // 0b111
};

struct Color {
public : 
	Color() : B(0), G(0), R(0) { }
	Color(uint rgb) : B(rgb), G(rgb), R(rgb) { }
	Color(uint r, uint g, uint b) : B(b), G(g), R(r) { }

	Color(Colors color) {
		B = color & 1; // OR color & 0b001;
		G = color & 2; // OR color & 0b010;
		R = color & 4; // OR color & 0b100;
	}

	uint B;
	uint G;
	uint R;
};

struct Pinout {
public : 
	Pinout() : D(-1) { }

	uint A;
	uint B;
	uint C;
	uint D;

	uint Blue0;
	uint Blue1;
	uint Green0;
	uint Green1;
	uint Red0;
	uint Red1;

	uint CLK;
	uint OE;
	uint STB;
};

struct Location {
public : 
	Location(uint xy) : x(xy), y(xy) { };
	Location(uint x, uint y) : x(x), y(y) { };

	uint x;
	uint y;
};

typedef Location Size;

struct Pixel {
public : 
	Pixel(Location *location, Color *color) : color(color), location(location) { }
	Pixel(Location *location, Colors color) : color(new Color(color)), location(location) { }
	~Pixel() {
		delete color;
		delete location;
	}

	Color *color;
	Location *location;
};

#endif