/*******************************************************
Name: Camera.h
Author: Christopher McDaniel
Date: 30 March 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This header file will create the operations
for the camera function.

     DISCLAIMER:
THIS PORTION "Camera.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Scene.cpp".
*******************************************************/

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <iostream>
#include <GL/freeglut.h>

/*Function identifier*/
void camera();

/*Global variables*/
float cameraX = 0;
float cameraY = -50;
float cameraHeight = 10;
float cameraAngleX = 0;
float cameraAngleY = 0;

/*
Function: camera
Parameters: (N/A)
Return: camera
Description: Function that creates the camera
operations.
*/
void camera()
{
    GLdouble eyeX = cameraX;
    GLdouble eyeY = cameraHeight;
    GLdouble eyeZ = cameraY;
    GLdouble centerX = cameraX + cos(cameraAngleX);
    GLdouble centerY = cameraHeight;
    GLdouble centerZ = cameraY + sin(cameraAngleY);
    GLdouble upX = 0;
    GLdouble upY = 1;
    GLdouble upZ = 0;

    gluPerspective(60, 1, 5, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);

    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

#endif