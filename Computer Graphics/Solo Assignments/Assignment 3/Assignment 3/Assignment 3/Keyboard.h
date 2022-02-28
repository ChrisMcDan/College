/*******************************************************
Name: Keyboard.h
Author: Christopher McDaniel
Date: 30 March 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
functions to move the camera via the keyboard.

     DISCLAIMER:
THIS PORTION "Keyboard.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Camera.h" and "Scene.cpp".
*******************************************************/

#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include <GL/freeglut.h>
#include "Camera.h"

/*Function identifiers*/
void WASDKeyboard(unsigned char, int, int);
void ArrowKeyboard(int, int, int);

/*
Function: WASDKeyboard
Parameters: (unsigned char, int, int)
Return: WASDKeyboard
Description: Utilizes a switch statement
to move the camera left, right, forwards,
and backwards along the X-axis and Z-axis.
It also changes the lighting depending on
the numbers 1, 2, and 3 that are pressed.
*/
void WASDKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
    case 'A':   //Move camera left.
        cameraX = cameraX + 0.5;
        break;
    case 'd':
    case 'D':   //Move camera right.
        cameraX = cameraX - 0.5;
        break;
    case 'w':
    case 'W':   //Move camera forwards.
        cameraY = cameraY + 0.5;
        break;
    case 's':
    case 'S':   //Move camera backwards.
        cameraY = cameraY - 0.5;
        break;
    case '1':   //Ambient lighting.
        ambient = !ambient;
        break;
    case '2':   //Diffuse lighting.
        diffuse = !diffuse;
        break;
    case '3':   //Specular lighting.
        specular = !specular;
        break;
    }
}

/*
Function: ArrowKeyboard
Parameters: (int, int, int)
Return: ArrowKeyboard
Description: Utilizes a switch statement
to move the turn the camera left and right.
*/
void ArrowKeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:    //Right arrow key.
        cameraAngleX += .20;
        cameraAngleY += .20;
        break;
    case GLUT_KEY_LEFT:     //Left arrow key.
        cameraAngleX -= .20;
        cameraAngleY -= .20;
        break;
    }
}

#endif