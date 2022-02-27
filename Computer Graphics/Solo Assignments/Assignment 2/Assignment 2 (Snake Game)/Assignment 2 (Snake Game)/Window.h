/*******************************************************
Name: Window.h
Author: Chrisotpher McDaniel
Date: 23 February 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This header file will display a window size
of 500 x 500.

	 DISCLAIMER:
THIS PORTION "Window.h" IS REQUIRED
TO BE USED IN CONJUNCTION WITH "Snake.cpp" and "Snake.h".
*******************************************************/

#include <GL/freeglut.h>
#include "Snake.h"

#define COLUMNS 40
#define ROWS 40

/*Function definitions*/
void init();
void display();
void reshape(int, int);

/*
Function: init
Parameters: (N/A)
Return: init
Description: Initialize the window size,
position, and name.
*/
void init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);	//Window size.

	//Initializes screen directly in center.
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 500) / 2,
							(glutGet(GLUT_SCREEN_HEIGHT) - 500) / 2);
	glutCreateWindow("Snake");	//Names window.
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initGrid(COLUMNS, ROWS);
}

/*
Function: display
Parameters: (N/A)
Return: display
Description: Calls all the functions to
display.
*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Call functions
	drawGrid();
	snake();
	spawnFood();	
	gameover();

	glutSwapBuffers();	//Swap buffers
}

/*
Function: reshape
Parameters: int w, int h
Return: reshape
Description: Sets the size of the
viewing matrix.
*/
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);	//Set viewport.
	glMatrixMode(GL_PROJECTION);	//Specifies which matrix is current matrix.
	glLoadIdentity();	//Replace current matrix with identity matrix.
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);	//Multiply current matrix with orthographic matrix.
	glMatrixMode(GL_MODELVIEW);	//Specifies which matrix is current matrix.
}
