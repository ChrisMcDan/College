/*******************************************************
Name: drawTable.h
Author: Christopher McDaniel
Date: 30 March 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a header file that will create the
function that draws the table within the scene.

     DISCLAIMER:
THIS PORTION "drawTable.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Scene.cpp".
*******************************************************/

#ifndef DRAWTABLE_H_INCLUDED
#define DRAWTABLE_H_INCLUDED

#include <GL/freeglut.h>

/*Function identifier*/
void drawTable();

/*
Function: drawTable
Parameters: (N/A)
Return: drawTable
Description: Draw the table by calling
the glutSolidCube function then translate
and scale it as needed. The lighting for
the table is also called upon here.
*/
void drawTable()
{
    //Lighting arrays for the table legs.
    GLfloat tableLegNoMat[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat tableLegAmbient[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat tableLegDiffuse[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat tableLegSpecular[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat tableLegShiness[] = { 15 };

    //Lighting arrays for the table top.
    GLfloat tableTopNoMat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat tableTopAmbient[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat tableTopDiffuse[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat tableTopSpecular[] = { 1.0, 0.4, 0.3, 1.0 };
    GLfloat tableTopShiness[] = { 17 };

    //Table legs
    //Call the lighting function.
    lighting(tableLegNoMat, tableLegAmbient, tableLegDiffuse, tableLegSpecular, tableLegShiness);
    glEnable(GL_COLOR_MATERIAL);    //Enable the objects to be colored.
    glColor3f(0.34, 0.19, 0.06);    //Set color of table.

    glPushMatrix();
    {
        glScalef(.5, 5, .5);        //Scale cube.
        glTranslatef(-5, 0.7, 10);  //Translate cube.
        glutSolidCube(1);           //Draw cube.
    }
    glPopMatrix();

    glPushMatrix();
    {
        glScalef(0.5, 5, 0.5);      //Scale cube.
        glTranslatef(-5, 0.7, 22);  //Translate cube.
        glutSolidCube(1);           //Draw cube.
    }
    glPopMatrix();

    glPushMatrix();
    {
        glScalef(0.5, 5, 0.5);      //Scale cube.
        glTranslatef(5, 0.7, 10);   //Translate cube.
        glutSolidCube(1);           //Draw cube.
    }
    glPopMatrix();

    glPushMatrix();
    {
        glScalef(0.5, 5, 0.5);      //Scale cube.
        glTranslatef(5, 0.7, 22);   //Translate cube.
        glutSolidCube(1);           //Draw cube.
    }
    glPopMatrix();

    //Table top
    //Call the lighting function.
    lighting(tableTopNoMat, tableTopAmbient, tableTopDiffuse, tableTopSpecular, tableTopShiness);
    glPushMatrix();
    {
        glTranslatef(0, 6, 8);  //Translate cube.
        glScalef(6, 0.5, 9);    //Scale cube.
        glutSolidCube(1);       //Draw cube.
    }
    glPopMatrix();

    //Teapot
    glPushMatrix();
    {
        glColor3f(0.653, 0.653, 0.653); //Set color of teapot.
        glTranslatef(0, 7, 8);          //Translate teapot.
        glutSolidTeapot(1);             //Draw teapot.
    }
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
}

#endif