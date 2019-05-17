#pragma once
class Shape
{
public:
	//variables
	float x;
	float y;
	float r;
	float velocity = 0;
	int type = 1;
	bool grounded = false;
	float colour[3] = { 0,0,0 };
	//methods
	Shape(float tx, float ty, float tr, int type);
	bool Equals(Shape s);
	bool DoesCollide();
};

