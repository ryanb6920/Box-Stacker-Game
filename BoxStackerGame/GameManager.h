#pragma once

#include <list>
#include "Shape.h"



class GameManager
{
public:
	GameManager();
	~GameManager();	
	static std::list<Shape> points;

	static void init(void);
	static void Display();
	static void Timer(int);
	static void Reshape(int w, int h);
	static void Keyboard(unsigned char key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static bool DetectCollision(Shape s1, Shape s2);
	
private:
	static void DrawSquare(float x, float y, float width);

};



