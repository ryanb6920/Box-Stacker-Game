#pragma once
class Shape
{
public:
	double x;
	double y;
	double r;
	double velocity = 0;
	int type;
	bool grounded = false;
	double colour[3] = { 0,0,0 };
	Shape(double tx, double ty, double tr, int type);
	~Shape();
	bool Equals(Shape s);
	bool doesCollide();
};

