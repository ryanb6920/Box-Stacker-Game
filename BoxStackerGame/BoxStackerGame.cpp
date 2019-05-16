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

	glutCreateWindow("Test");

	GameManager::init();
	glutMouseFunc(GameManager::Mouse);
	glutTimerFunc(1000 / 60, GameManager::Timer, 0);
	glutDisplayFunc(GameManager::Display);
	glutReshapeFunc(GameManager::Reshape);
	glutKeyboardFunc(GameManager::Keyboard);
	glutMainLoop();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
