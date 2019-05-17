// BoxStackerGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "GameManager.h"

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Box Stacker !!");
	GameManager::Init();	
	glutTimerFunc(1000 / 60, GameManager::Timer, 0);
	glutDisplayFunc(GameManager::Display);
	glutMouseFunc(GameManager::Mouse);
	glutReshapeFunc(GameManager::Reshape);
	glutKeyboardFunc(GameManager::Keyboard);
	glutMainLoop();
	return 0;
}
