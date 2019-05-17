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
const float GRAV = 0.048;
float GameManager::ranr = 0.1;
Shape GameManager::uiShape = Shape(-0.875, -0.875,0.1, 1);

int secs = 10;
int ticks = 0;
int score = 0;
bool gameOver = false;

const char *message = "Box Stacking !!";
const char *message2 = "Stack as many boxes as you can.";
const char *message3 = "1 point per box, if you cannot place";
const char *message4 = "a box within 10 seconds GAME OVER!";
const char *timeT = "Time:";
const char *scoreT = "Score:";

char timeVar[64] = "";
char scoreVar[256] = "";
char gOverScore[256] = "";

char *timeV = timeVar;
char *scoreV = scoreVar;

//Initializer Method for the GameManager
void GameManager::Init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);	
	glShadeModel(GL_FLAT);
}

//Display Function to pass to GLUT, all drawing code goes here
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

	DrawSquare(uiShape.x, uiShape.y, uiShape.r,0,0,0);
	DrawObjects();

	if (gameOver) {
		DrawSquare(-0.25, 0.32, 0.15,0.06, 0.75, 0.75, 0.75);
		DrawSquare(-0.25, 0.22, 0.28, 0.035, 0.75, 0.75, 0.75);
		OutputText(-0.395, 0.325, "Game Over");
		OutputText(-0.35, 0.30-0.025, gOverScore);
		OutputText(-0.50, 0.20, "Press Space to Reset");
	}
	//drawing code goes above here
	
	glLoadIdentity();
	glFlush();	
}

//Timer Function to pass to GLUT, game logic goes here.
void GameManager::Timer(int) {	
	if (!gameOver) {
		ticks++;
		if (ticks % 60 == 0)
		{
			secs--;
			if (secs == 0)
				gameOver = true;
			ticks = 0;
		}
	}
		
	sprintf_s(timeV,4, "%d", secs);
	sprintf_s(scoreV, 10, "%d", score);
	sprintf_s(gOverScore, 30, "Score: %d", score);

	//for all objects
	for (std::list<Shape>::iterator it = points.begin(); it != points.end(); ++it) {
			
		if (!(*it).grounded) { // if not grounded
			(*it).velocity += GRAV;	//move on y axis
			(*it).y -= (*it).velocity * GRAV;
			if ((*it).y < -0.75 + (*it).r) 
			{
				(*it).grounded = true;
				(*it).y = -0.75 + (*it).r;
			}

			for (std::list<Shape>::iterator it1 = points.begin(); it1 != points.end(); ++it1) {
				if (DetectCollision(*it1, *it) == true && (*it).Equals(*it1) == false) {
					if ((*it1).y < (*it).y) {
						(*it).y = (*it1).y + (*it1).r + (*it).r;
						(*it).velocity = (*it1).velocity;
					}
				}
			}
		}	
	}
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, Timer, 0);
}

//prevents user from resizing window
void GameManager::Reshape(int w, int h) {
	glutReshapeWindow(600, 800);
}

//Keyboard control class, passed to GLUT function
void GameManager::Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 32:
		if (gameOver) {
			points = {};
			score = 0;
			secs = 10;
			gameOver = false;
		}
	}
}

//Mouse control class, passed to GLUT function
void GameManager::Mouse(int button, int state, int x, int y) {
	float xt = ((float)x - 400) / 400;
	float yt = (((float)y - 400) / 400) * -1;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Shape test = Shape(xt, yt, ranr, 1);
		if (!test.DoesCollide() && !OutOfBounds(test)) {
			points.push_back(test);
			ranr = (rand() % 5) / 100.0 + 0.06;
			uiShape.r = ranr; 
			score++;
			secs = 10;
			ticks = 0;
		}		
	}
}

//Detects whether Shape s1 & Shape s2 Collide
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

//Renders a square using openGL commands, overload to have uniform square or custom width & height
void GameManager::DrawSquare(float x, float y, float width, float r,float g, float b) {
	float w = width;
	glBegin(GL_QUADS);
	glColor3f(r, g, b);

	glVertex2f(x - w, y - w);
	glVertex2f(x - w, y + w);
	glVertex2f(x + w, y + w);
	glVertex2f(x + w, y - w);

	glEnd();
}
void GameManager::DrawSquare(float x, float y, float width, float height, float r, float g, float b) {
	float w = width;
	float h = height;
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex2f(x - w, y - h);
	glVertex2f(x - w, y + h);
	glVertex2f(x + w, y + h);
	glVertex2f(x + w, y - h);
	glEnd();
}

//Loops through all Objects in 'points' and calls DrawSquare to render each one
void GameManager::DrawObjects() {		
	for (std::list<Shape>::iterator it = points.begin(); it != points.end(); it++) {
		switch ((*it).type) {
		case 1:
			DrawSquare((*it).x, (*it).y, (*it).r,0,0,0);
		}
	}
}

//Medthod to render text onto screen using a string
void GameManager::OutputText(float x, float y, const char *string)
{
	int len, i;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

//Method to determine whether Object is out of bounds of screen
bool GameManager::OutOfBounds(Shape s) {
	if (s.x - s.r <= -1		||
		s.x + s.r >= 0.5	||
		s.y - s.r <= -0.75	||
		s.y + s.r >= 1
		)
		return true;
	else
		return false;
}