/*******************************************************
Name: Scene.cpp
Author: Christopher McDaniel
Date: 30 March 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a program that will display a
500 x 500 window and draw a 3D scene that can be
moved within via the "W, A, S, and D" keys.

     DISCLAIMER:
THIS PORTION "Scene.cpp" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Window.h", "Keyboard.h", and
"Scene.h".
*******************************************************/

#include <GL/freeglut.h>
#include "Window.h"
#include "Scene.h"
#include "Keyboard.h"

using namespace std;

/*Function identifiers*/
int main(int, char**);

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
	glutKeyboardFunc(WASDKeyboard);	//WASD keyboard callback.
	glutSpecialFunc(ArrowKeyboard);	//Arrow keyboard callback.
	glutIdleFunc(idle);	//Redisplays window.

	glutMainLoop();	//Trigger callback functions.

	return 0;
}