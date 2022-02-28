/*******************************************************
Name: drawChair.h
Author: Christopher McDaniel
Date: 30 March 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a header file that will create the
function that will draw a chair.

     DISCLAIMER:
THIS PORTION "drawChair.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Scene.cpp".
*******************************************************/

#ifndef DRAWCHAIR_H_INCLUDED
#define DRAWCHAIR_H_INCLUDED

#include <GL/freeglut.h>

/*Function identifier*/
void drawChair(float, float, float);

/*
Function: drawChair
Parameters: (float, float, float)
Return: drawChair
Description: Draw the chairs within the room
by calling the glutSolidCube function
then translate and scale it as needed.
The lighting for each chair is also called
upon here.
*/
void drawChair(float x, float z, float r)
{
    //Lighting arrays for the chair legs.
    GLfloat chairLegNoMat[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat chairLegAmbient[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat chairLegDiffuse[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat chairLegSpecular[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat chairLegShiness[] = { 15 };

    //Lighting arrays for the chair seat.
    GLfloat chairSeatNoMat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat chairSeatAmbient[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat chairSeatDiffuse[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat chairSeatSpecular[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat chairSeatShiness[] = { 17 };

    //Lighting arrays for the chair back.
    GLfloat chairBackNoMat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat chairBackAmbient[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat chairBackDiffuse[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat chairBackSpecular[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat chairBackShiness[] = { 17 };

    //Chair legs
    //Call the lighting function.
    lighting(chairLegNoMat, chairLegAmbient, chairLegDiffuse, chairLegSpecular, chairLegShiness);
    glEnable(GL_COLOR_MATERIAL);    //Enable the objects to be colored.
    glColor3f(0.34, 0.19, 0.06);    //Set color of chairs.
    glPushMatrix();
    {
        glTranslatef(-4 + x, 2.5, 9.5 + z);  //Translate cube.
        glScalef(0.35, 4, 0.35);    //Scale cube.
        glutSolidCube(1);           //Draw cube.
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-4 + x, 2.5, 6.5 + z);  //Translate cube.
        glScalef(0.35, 4, 0.35);    //Scale cube.
        glutSolidCube(1);           //Draw cube.
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-7 + x, 2.5, 9.5 + z);  //Translate cube.
        glScalef(0.35, 4, 0.35);    //Scale cube.
        glutSolidCube(1);           //Draw cube.
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-7 + x, 2.5, 6.5 + z);  //Translate cube.
        glScalef(0.35, 4, 0.35);    //Scale cube.
        glutSolidCube(1);           //Draw cube.
    }
    glPopMatrix();

    //Chair seat
    //Call the lighting function.
    lighting(chairSeatNoMat, chairSeatAmbient, chairSeatDiffuse, chairLegSpecular, chairSeatShiness);
    glPushMatrix();
    {
        glTranslatef(-5.5 + x, 4.5, 8 + z);  //Translate cube.
        glScalef(4, 0.5, 4);        //Scale cube.
        glutSolidCube(1);           //Draw cube.
    }
    glPopMatrix();

    //Chair back
    //Call the lighting function.
    lighting(chairBackNoMat, chairBackAmbient, chairBackDiffuse, chairSeatSpecular, chairBackShiness);
    if (r == 1)
    {
        //Right chair        
        glPushMatrix();
        {
            glTranslatef(-7.3 + x, 6.5, 8 + z);  //Translate cube.
            glRotatef(90, 0, 0, 1);     //Rotate cube.
            glScalef(4, 0.3, 3.8);      //Scale cube.
            glutSolidCube(1);           //Draw cube.
        }
        glPopMatrix();
    }
    else if (r == 2)
    {
        //Left chair
        glPushMatrix();
        {
            glTranslatef(-7.7 + x + 4, 6.5, 8 + z);  //Translate cube.
            glRotatef(90, 0, 0, 1);     //Rotate cube.
            glScalef(4, 0.3, 3.8);      //Scale cube.
            glutSolidCube(1);           //Draw cube.
        }
        glPopMatrix();
    }
    else if (r == 3)
    {
        //Front chair
        glPushMatrix();
        {
            glTranslatef(-8.0 + x + 2.5, 6.5, 8 + z - 1.8);  //Translate cube.
            glRotatef(90, 1, 0, 0);     //Rotate cube.
            glScalef(4, 0.3, 3.8);      //Scale cube.
            glutSolidCube(1);           //Draw cube.
        }
        glPopMatrix();
    }
    else if (r == 4)
    {
        //Back chair
        glPushMatrix();
        {
            glTranslatef(-8.0 + x + 2.5, 6.5, 8 + z + 1.8);  //Translate cube.
            glRotatef(90, 1, 0, 0);     //Rotate cube.
            glScalef(4, 0.3, 3.8);      //Scale cube.
            glutSolidCube(1);           //Draw cube.
        }
        glPopMatrix();

    }
    glDisable(GL_COLOR_MATERIAL);
}

#endif