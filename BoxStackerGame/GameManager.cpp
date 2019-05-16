#include "pch.h"
#include "GameManager.h"
#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>
#include <list>
#include <time.h>
#include <stdlib.h>

std::list<Shape> GameManager::points;
const double GRAV = 0.048;

GameManager::GameManager()
{
	//std::list<Shape> points = {};
}

GameManager::~GameManager()
{

}

void GameManager::init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);
}

void GameManager::Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//drawing code goes below here	

	for (std::list<Shape>::iterator it = points.begin(); it != points.end(); it++) {
		DrawSquare((*it).x, (*it).y, (*it).r);
	}

	//drawing code goes above here
	glLoadIdentity();
	glFlush();
}

void GameManager::Timer(int) {

	for (std::list<Shape>::iterator it = points.begin(); it != points.end(); ++it) {
			
		if (!(*it).grounded) {
			(*it).velocity += GRAV;
			(*it).y -= (*it).velocity * GRAV;
			//(*it).Update();
			if ((*it).y < -0.9)
			{
				(*it).grounded = true;
				(*it).y = -0.9;
				//(*it).velocity = (*it).velocity*-1;
				//(*it).velocity += GRAV;
			}

			if (!(*it).grounded) {
				for (std::list<Shape>::iterator it1 = points.begin(); it1 != points.end(); ++it1) {
					if (DetectCollision(*it1, *it) == true && (*it).Equals(*it1) == false) {
						(*it).y = (*it1).y + (*it1).r * 2;
						(*it).grounded = true;
					}
				}
			}

			
		}
	}


	glutPostRedisplay();
	glutTimerFunc(1000 / 60, Timer, 0);
}

void GameManager::Reshape(int w, int h) {
	glutReshapeWindow(600, 800);
}

void GameManager::Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 32:
		points = {};
	}

}

void GameManager::Mouse(int button, int state, int x, int y) {
	float xt = ((float)x - 400) / 400;
	float yt = (((float)y - 400) / 400) * -1;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Shape test = Shape(xt, yt, 0.1, 1);
		
		if (!test.doesCollide()) {
			puts("Square Added!");
			points.push_back(test);
		}
		else
		{
			puts("Error - Collision Detected!");
		}
		
		
	}
}

bool GameManager::DetectCollision(Shape s1, Shape s2) {	
	if (s1.x + s1.r > s2.x - s2.r && // hit left
		s1.x - s1.r < s2.x + s2.r && // hit right
		s1.y + s1.r > s2.y - s2.r && // hit bottom
		s1.y - s1.r < s2.y + s2.r	  // hit top
		) {		
		return true;
	}	
	return false;
}

void GameManager::DrawSquare(float x, float y, float width) {
	float w = width;
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);

	glVertex2f(x - w, y - w);
	glVertex2f(x - w, y + w);
	glVertex2f(x + w, y + w);
	glVertex2f(x + w, y - w);

	glEnd();
}