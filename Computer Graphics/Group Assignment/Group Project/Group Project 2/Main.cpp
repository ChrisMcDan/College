/*******************************************************
Name: Main.cpp
Author: Christopher McDaniel, Daniel Feuling,
and Dean Morgan-Brown
Date: 5 April 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
functions used in the lighting of the scene.

	 DISCLAIMER:
THIS PORTION "Main.cpp" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Window.h".
*******************************************************/

#include <GL/freeglut.h>
#include <iostream>
#include "Window.h"

/*
Function: main
Parameters: int argc, char** argv
Return: main
Description: Calls initial window function,
enables server side GL capabilities, and
all the needed callback functions.
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);	//Initialize GLUT library.
	init();	//Call init() function.
	glEnable(GL_DEPTH_TEST);	//Enable DEPTH TEST.
	glEnable(GL_NORMALIZE);		//Enable NORMALIZE.
	glEnable(GL_LIGHTING);		//Enable LIGHTING.

	xRotated = yRotated = zRotated = 30;
	xRotated = 43;
	yRotated = 50;

	glEnable(GL_LIGHT0);	//Enable LIGHT0.
	{
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);		//Set light source parameters.
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);		//Set light source parameters.
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);	//Set light source parameters.
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);	//Set light source parameters.
	}
	glDisable(GL_LIGHT0);	//Disable LIGHT0.

	glutDisplayFunc(display);	//Display callback.
	glutReshapeFunc(reshape);	//Reshape callback.
	glutKeyboardFunc(Keyboard);	//WASD keyboard callback.
	glutIdleFunc(idle);			//Redisplays window.

	glutMainLoop();	//Trigger callback functions.

	return 0;
}