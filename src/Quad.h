#pragma once

#include<body.h>

class Quad
{
private:
	double xmid, ymid, zmid, length;
public:
	// create a cube quadrant with a given length and midpoints (xmid, ymid, zmid)
	Quad(double xmid, double ymid, double zmid, double length);

	// How long is this quadrant?
	double getLength();

	// Check if the current quadrant contains a point
	bool contains(Vector position);

	//Create subdivisions of the current quadrant
	// Subdivision: X0Y0Z0 quadrant
	Quad X0Y0Z0();

	// Subdivision: X0Y0Z1 quadrant
	Quad X0Y0Z1();

	// Subdivision: X0Y1Z0 quadrant
	Quad X0Y1Z0();

	// Subdivision: X0Y1Z1 quadrant
	Quad X0Y1Z1();

	// Subdivision: X1Y0Z0 quadrant
	Quad X1Y0Z0();

	// Subdivision: X1Y0Z1 quadrant
	Quad X1Y0Z1();

	// Subdivision: X1Y1Z0 quadrant
	Quad X1Y1Z0();

	// Subdivision: X1Y1Z1 quadrant
	Quad X1Y1Z1();
};

