/*******************************************************
Name: Scene.h
Author: Christopher McDaniel
Date: 30 March 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a header file that create the
functions for drawing the wall, the floor, and the
ceiling of the scene.

     DISCLAIMER:
THIS PORTION "Scene.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "drawLight.h" and "Scene.cpp".
*******************************************************/

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <GL/freeglut.h>
#include "drawLight.h"

/*Function identifiers*/
void drawWall();
void drawFloor();
void drawCeiling();

/*
Function: drawWall
Parameters: (N/A)
Return: drawWall
Description: Draw the walls of the room
by calling the glutSolidCube function
then translate and scale it as needed.
The lighting for each wall is also called
upon here.
*/
void drawWall()
{
    //Lighting arrays for the walls.
    GLfloat wallNoMat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat wallAmbient[] = { 0.4, 0.6, 0.6, 1.0 };
    GLfloat wallDiffuse[] = { 0.3, 0.6, 0.6, 0.9 };
    GLfloat wallSpecular[] = { 0.3,0.6, 0.6, 1.0 };
    GLfloat wallShiness[] = { 13 };

    //Call the lighting function.
    lighting(wallNoMat, wallAmbient, wallDiffuse, wallSpecular, wallShiness);

    //Draws, translates and scales the left wall.
    glPushMatrix();
    {
        glTranslatef(25, 7.5, 7);   //Translates cube.
        glScalef(0.2, 15, 40);      //Scales cube.
        glutSolidCube(1);           //Draws cube.
    }
    glPopMatrix();

    //Draws, translates and scales the right wall.
    glPushMatrix();
    {
        glTranslatef(-25, 7.5, 7);  //Translates cube.
        glScalef(0.2, 15, 40);      //Scales cube.
        glutSolidCube(1);           //Draws cube.
    }
    glPopMatrix();

    //Draws, translates and scales the back wall.
    glPushMatrix();
    {
        glTranslatef(0, 7.5, 27);   //Translates cube.
        glScalef(50, 15, 0.2);      //Scales cube.
        glutSolidCube(1);           //Draws cube.
    }
    glPopMatrix();
}

/*
Function: drawFloor
Parameters: (N/A)
Return: drawFloor
Description: Draw the floor of the room
by calling the glutSolidCube function
then translate and scale it as needed.
The lighting for the floor is also called
upon here.
*/
void drawFloor()
{
    //Lighting arrays for the floor.
    GLfloat floorNoMat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat floorAmbient[] = { 0.2, 0.3, 0.3, 0.8 };
    GLfloat floorDiffuse[] = { 0.2, 0.3, 0.3, 1.0 };
    GLfloat floorSpecular[] = { 0.2, 0.4, 0.4, 1.0 };
    GLfloat floorShiness[] = { 15 };

    //Call the lighting function.
    lighting(floorNoMat, floorAmbient, floorDiffuse, floorSpecular, floorShiness);
    glPushMatrix();
    {
        //Draws, translates and scales the floor.
        glTranslatef(0, 0, 7);  //Translates cube.
        glScalef(50, 0.2, 40);  //Scales cube.
        glutSolidCube(1);       //Draws cube.
    }
    glPopMatrix();
}

/*
Function: drawCeiling
Parameters: (N/A)
Return: drawCeiling
Description: Draw the ceiling of the room
by calling the glutSolidCube function
then translate and scale it as needed.
The lighting for the ceiling is also called
upon here.
*/
void drawCeiling()
{
    //Lighting arrays for the ceiling.
    GLfloat ceilingNoMat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat ceilingAmbient[] = { 0.4, 0.6, 0.6, 1.0 };
    GLfloat ceilingDiffuse[] = { 0.4, 0.6, 0.7, 0.9 };
    GLfloat ceilingSpecular[] = { 0.4, 0.7, 0.6, 1.0 };
    GLfloat ceilingShiness[] = { 15 };

    //Call the lighting function.
    lighting(ceilingNoMat, ceilingAmbient, ceilingDiffuse, ceilingSpecular, ceilingShiness);
    glPushMatrix();
    {
        //Draws, translates, and scales the ceiling.
        glTranslatef(0, 15, 7); //Translates cube.
        glScalef(50, 0.2, 40);  //Scales cube.
        glutSolidCube(1);       //Draws cube.
    }
    glPopMatrix();

}

#endif