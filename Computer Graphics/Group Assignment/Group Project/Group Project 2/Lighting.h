/*******************************************************
Name: Lighting.h
Author: Christopher McDaniel, Daniel Feuling,
and Dean Morgan-Brown
Date: 5 April 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
functions used in the lighting of the scene.

     DISCLAIMER:
THIS PORTION "Lighting.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Main.cpp".
*******************************************************/

#ifndef LIGHTING_H_INCLUDED
#define LIGHTING_H_INCLUDED

#include <GL/freeglut.h>

/*Function identifiers*/
void lighting(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void inSceneLighting();

/*Global GLboolean*/
GLboolean ambient = true;
GLboolean diffuse = true;
GLboolean specular = true;

/*Array for the lighting*/
GLfloat noLight[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat lightAmbient[] = { .50, .50, .50, .50 };
GLfloat lightDiffuse[] = { .50, .50, .50, .50 };
GLfloat lightSpecular[] = { .50, .50, .50, .50 };
GLfloat lightPosition[] = { 2.0, 5.0, 5.0, 0.0 };

GLfloat no_mat[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shiness[] = { 100.0 };

/*
Function: lighting
Parameters: (GLfloat, GLfloat, GLfloat, GLfloat, GLfloat)
Return: lighting
Description: Sets the intial light of the object.
*/
void lighting(GLfloat no_mat[], GLfloat mat_ambient[], GLfloat mat_diffuse[], GLfloat mat_specular[], GLfloat shiness[])
{
    if (ambient)    //Ambient lighting.
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    }

    if (diffuse)    //Diffuse lighting.
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
    }

    if (specular)   //Specular lighting.
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    }
    glMaterialfv(GL_FRONT, GL_SHININESS, shiness);  //Combination of all three.
}

/*
Function: inSceneLighting
Parameters: (N/A)
Return: inSceneLighting
Description: Sets the parameters for
the light source.
*/
void inSceneLighting()
{
    //lighting in scene
    glEnable(GL_LIGHT0);
    if (ambient)    //Ambient lighting.
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, noLight);
    }

    if (diffuse)    //Diffuse lighting.
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, noLight);
    }

    if (specular)   //Specular lighting.
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, noLight);
    }
}

#endif