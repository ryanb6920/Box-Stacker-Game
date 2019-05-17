#pragma once
#include <list>
#include "Shape.h"

class GameManager
{
public:
	static std::list<Shape> points;
	static Shape uiShape;
	static float ranr;
	static void Init(void);
	static void Display();
	static void Timer(int);
	static void Reshape(int w, int h);
	static void Keyboard(unsigned char key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static bool DetectCollision(Shape s1, Shape s2);
	static bool OutOfBounds(Shape s);
private:
	static void OutputText(float x, float y, const char* string);
	static void DrawObjects();
	static void DrawSquare(float x, float y, float width, float r, float g, float b);
	static void DrawSquare(float x, float y, float width, float height, float r, float g, float b);
};



