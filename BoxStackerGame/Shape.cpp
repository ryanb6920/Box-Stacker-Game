#include "pch.h"
#include "Shape.h"
#include "GameManager.h"

Shape::Shape(float tx, float ty, float tr, int ttype)
{
	x = tx; y = ty; type = ttype; r = tr; //assign values
}

//chech if this shape has identical properties to Shape s
bool Shape::Equals(Shape s) {
	return (
		x == s.x &&
		y == s.y &&
		velocity == s.velocity &&
		grounded == s.grounded &&
		type == s.type
		);
}

//Check whether current shape collides with any other shape
bool Shape::DoesCollide() {
	for (std::list<Shape>::iterator it =  GameManager::points.begin(); it != GameManager::points.end(); ++it) {
		if (!Equals(*it)) {
			if (GameManager::DetectCollision(*this, (*it)))
				return true;
		}
	}
	return false;
}

