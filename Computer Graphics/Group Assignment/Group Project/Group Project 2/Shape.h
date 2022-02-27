/*******************************************************
Name: Shape.h
Author: Christopher McDaniel, Daniel Feuling,
and Dean Morgan-Brown
Date: 5 April 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
functions used in the lighting of the scene.

     DISCLAIMER:
THIS PORTION "Shape.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Lighting.h" and "Main.cpp".
*******************************************************/

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <stdlib.h>
#include <iostream>
#include "Lighting.h"

/*Fuinction identifiers*/
void genColor();
void shape();

/*Global integers*/
int shapeRand = 1;

/*Global floats*/
GLfloat colorRandr, colorRandg, colorRandb; //Red, Green, Blue.
GLfloat xRotated, yRotated, zRotated;   //X, Y, Z rotation.

/*
Function: shape
Parameters: (N/A)
Return: shape
Description: Draws the shape and rotates it
within the window.
*/
void shape()
{
    std::cout << shapeRand << std::endl;

    xRotated += 0.1;
    yRotated += 0.1;
    zRotated += 0.1;

    lighting(noLight, lightAmbient, lightDiffuse, lightSpecular, lightPosition);
    glEnable(GL_COLOR_MATERIAL);
    glLoadIdentity();

    glPushMatrix();
    {
        glTranslatef(0, 0, 0);  //Translate shape.
        glScalef(0.5f, 0.5f, 0.5f);    //Scale shape.
        glColor3f(colorRandr, colorRandg, colorRandb);
        switch (shapeRand)
        {
        case(1):    //Donut
            glRotatef(xRotated, 1, 0, 0);   //Rotate about X-axis.
            glRotatef(yRotated, 0, 1, 0);   //Rotate about Y-axis.
            glRotatef(zRotated, 0, 0, 1);   //Rotate about Z-axis.
            glutSolidTorus(0.4, 0.8, 10, 50);
            break;
        case(2):    //Sphere
            glRotatef(xRotated, 1, 0, 0);   //Rotate about X-axis.
            glRotatef(yRotated, 0, 1, 0);   //Rotate about Y-axis.
            glRotatef(zRotated, 0, 0, 1);   //Rotate about Z-axis.
            glutSolidSphere(1, 25, 25);
            break;
        case(3):    //Teapot
            glRotatef(xRotated, 1, 0, 0);   //Rotate about X-axis.
            glRotatef(yRotated, 0, 1, 0);   //Rotate about Y-axis.
            glRotatef(zRotated, 0, 0, 1);   //Rotate about Z-axis.
            glutSolidTeapot(1);
            break;
        }
    }
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
    glFlush();
}

/*
Function: Keyboard
Parameters: (unsigned char, int, int)
Return: Keyboard
Description: Utilizes a switch statement
to change the lighting depending on
the keys A, D, and S that are pressed.
Also, when 1 or 2 is pressed it changes
the shape.
*/
void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case'a':
    case'A':
        ambient = !ambient;
        break;
    case'd':
    case'D':
        diffuse = !diffuse;
        break;
    case's':
    case'S':
        specular = !specular;
        break;
    case'1':
        shapeRand--;
        genColor();
        break;
    case'2':
        shapeRand++;
        genColor();
        break;
    }
}

/*
Function: genColor
Parameters: (N/A)
Return: genColor
Description: Generates a random number to be
used in the generation of colors.
*/
void genColor()
{
    colorRandr = (rand() % 10) / 1;
    colorRandg = (rand() % 10) / 1;
    colorRandb = (rand() % 10) / 1;
}

#endif

