#include "pch.h"
#include "GameManager.h"
#include "pch.h"
#include <iostream>
#include <string.h>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>
#include <list>
#include <time.h>
#include <stdlib.h>
#include <sstream>


std::list<Shape> GameManager::points;
const double GRAV = 0.048;
double GameManager::ranr = 0.1;
Shape GameManager::uiShape = Shape(-0.875, -0.875,0.1, 1);

int secs = 10;
int ticks = 0;
int score = 0;

char defaultMessage[] = "Box Stacking !!";
char defaultMessage2[] = "Stack as many boxes as you can.";
char defaultMessage3[] = "1 point per box, if you cannot place";
char defaultMessage4[] = "a box within 10 seconds GAME OVER!";
char timeMessage[] = "Time:";
char scoreMessage[] = "Score:";
char timeVar[64] = "";
char scoreVar[256] = "";


char *message = defaultMessage;
char *message2 = defaultMessage2;
char *message3 = defaultMessage3;
char *message4 = defaultMessage4;

char *timeT = timeMessage;
char *scoreT = scoreMessage;


char *timeV = timeVar;
char *scoreV = scoreVar;



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

	OutputText(-0.75, -0.8, message);
	OutputText(-0.75, -0.86, message2);
	OutputText(-0.75, -0.92, message3);
	OutputText(-0.75, -0.98, message4);

	OutputText(0.25, -0.8, timeT);
	OutputText(0.25, -0.86, timeV);
	OutputText(0.25, -0.92, scoreT);
	OutputText(0.25, -0.98, scoreV);

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-1, -0.75);
	glVertex2f(1, -0.75);
	glVertex2f(-0.75, -0.75);
	glVertex2f(-0.75, -1);
	glVertex2f(0.25, -0.75);
	glVertex2f(0.25, -1);
	glEnd();

	DrawSquare(uiShape.x, uiShape.y, uiShape.r);

	DrawObjects();

	//drawing code goes above here
	
	glLoadIdentity();
	glFlush();

	
}

void GameManager::Timer(int) {
	ticks++; 
	if (ticks % 60 == 0)
	{
		secs--;
		if (secs == 0)
			secs = 10;
		printf("\nTime Elapsed: %d\n",secs);
		ticks = 0;
	}

	//Text
	
	sprintf_s(timeV,4, "%d", secs);
	sprintf_s(scoreV, 10, "%d", score);

	//for all objects
	for (std::list<Shape>::iterator it = points.begin(); it != points.end(); ++it) {
			
		if (!(*it).grounded) { // if not grounded
			(*it).velocity += GRAV;	//move on y axis
			(*it).y -= (*it).velocity * GRAV;
			//(*it).Update();
			if ((*it).y < -0.75 + (*it).r) 
			{
				(*it).grounded = true;
				(*it).y = -0.75 + (*it).r;
				//(*it).velocity = (*it).velocity*-0.75;
				//(*it).velocity += GRAV;
			}


			for (std::list<Shape>::iterator it1 = points.begin(); it1 != points.end(); ++it1) {
				if (DetectCollision(*it1, *it) == true && (*it).Equals(*it1) == false) {
					(*it).y = (*it1).y + (*it1).r + (*it).r;
					(*it).velocity =0;
					(*it).grounded = true;
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
		Shape test = Shape(xt, yt, ranr, 1);
		if (!test.doesCollide()) {
			//puts("Square Added!");
			points.push_back(test);
			ranr = (rand() % 5) / 100.0 + 0.06;
			uiShape.r = ranr; 
			score++;
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


void GameManager::DrawObjects() {
		
	for (std::list<Shape>::iterator it = points.begin(); it != points.end(); it++) {
		switch ((*it).type) {
		case 1:
			DrawSquare((*it).x, (*it).y, (*it).r);
		}
	}
}


void GameManager::OutputText(double x, double y, char *string)
{
	int len, i;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void GameManager::OutputText(double x, double y, const char *string)
{
	int len, i;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}