/*******************************************************
Name: Snake.cpp
Author: Chrisotpher McDaniel
Date: 23 February 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a program that will display a
500 x 500 window and allow an individual to play the
game 'Snake'.

     DISCLAIMER:
THIS PORTION "Snake.cpp" IS REQUIRED
TO BE USED IN CONJUNCTION WITH "Window.h" and "Snake.h".
*******************************************************/

#include <GL/freeglut.h>
#include "Window.h"
#include "Snake.h"

/*Function definitions*/
void initGrid(int, int);
void drawGrid();
void barrier(int, int);

//int global variable.
int X_grid, Y_grid;

/*
Function: initGrid
Parameters: int x, int y
Return: initGrid
Description: Initialize the grid axes.
*/
void initGrid(int x, int y)
{
	X_grid = x;
	Y_grid = y;
}

/*
Function: drawGrid
Parameters: (N/A)
Return: drawGrid
Description: Draw the grid.
*/
void drawGrid()
{
	for (int x = 0; x < X_grid; x++)
	{
		for (int y = 0; y < Y_grid; y++)
		{
			barrier(x, y);
		}
	}
}

/*
Function: barrier
Parameters: int x, int y
Return: Barrier
Description: Creates an 'out of bound' barrier
that ends the game..
*/
void barrier(int x, int y)
{
	//Kill zone
	if (x == 0 || y == 0 || x == X_grid - 1 || y == Y_grid - 1)
	{
		glLineWidth(3.0);
		glColor3f(0.0, 0.0, 0.0);
	}
	else //Live zone
	{
		glLineWidth(1.0);
		glColor3f(0.80, 0.80, 0.80);
	}

	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);

	glEnd();
}

/*
Function: main
Parameters: int argc, char** argv
Return: main
Description: Calls initial window function
and all the needed callback functions.
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);	//Initialize GLUT library.
	init();	//Call init() function.
	glutTimerFunc(0, increaseSpeed, 0);
	glutDisplayFunc(display);	//Display callback.
	glutReshapeFunc(reshape);	//Reshape callback.
	glutSpecialFunc(keyboard);	//Special keyboard callback
	glutMainLoop();	//Trigger callback functions.

	return 0;
}