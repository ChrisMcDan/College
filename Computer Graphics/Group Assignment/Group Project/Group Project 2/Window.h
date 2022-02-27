/*******************************************************
Name: Window.h
Author: Christopher McDaniel, Daniel Feuling,
and Dean Morgan-Brown
Date: 5 April 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
functions used in the lighting of the scene.

     DISCLAIMER:
THIS PORTION "Window.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Shape.h", "Lighting.h", and "Main.cpp".
*******************************************************/

#include <GL/freeglut.h>
#include "Shape.h"
#include "Lighting.h"

/*Function identifiers*/
void init();
void display();
void reshape(int, int);
void idle();

/*
Function: init
Parameters: (N/A)
Return: init
Description: Initialize the window size,
position, and name.
*/
void init()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);	//Window size.

    //Initializes screen directly in center.
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1000) / 2,
        (glutGet(GLUT_SCREEN_HEIGHT) - 1000) / 2);
    glutCreateWindow("Lighting");	//Names window.
    glClearColor(0.1, 0.1, 0.1, 0.0);   //Window color.
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Call functions
    shape();
    inSceneLighting();

    glutSwapBuffers();  //Swap buffers
}

/*
Function: reshape
Parameters: (int, int)
Return: reshape
Description: Sets the size of the
viewing matrix.
*/
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);	//Set viewport.
    glMatrixMode(GL_PROJECTION);	//Specifies which matrix is current matrix.
    glLoadIdentity();	//Replace current matrix with identity matrix.
    glOrtho(0.0, 0, 0.0, 0, -1.0, 1.0);	//Multiply current matrix with orthographic matrix.
    glMatrixMode(GL_MODELVIEW);	//Specifies which matrix is current matrix.
}

/*
Function: idle
Parameters: (void)
Return: idle
Description: Function that performs the
glutPostRedisplay()
*/
void idle(void)
{
    glutPostRedisplay();    //Marks the current window as needing to be redisplayed.
}