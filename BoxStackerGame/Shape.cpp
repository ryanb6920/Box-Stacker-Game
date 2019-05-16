#include "pch.h"
#include "Shape.h"
#include "GameManager.h"

Shape::Shape(double tx, double ty, double tr, int ttype)
{
	x = tx; y = ty; type = ttype; r = tr; //assign values
}

bool Shape::Equals(Shape s) {
	return (
		x == s.x &&
		y == s.y &&
		velocity == s.velocity &&
		grounded == s.grounded &&
		type == s.type
		);
}

bool Shape::doesCollide() {
	for (std::list<Shape>::iterator it =  GameManager::points.begin(); it != GameManager::points.end(); ++it) {
		if (!Equals(*it)) {
			if (GameManager::DetectCollision(*this, (*it)))
				return true;
		}
	}
	return false;
}



Shape::~Shape()
{
}
