/*******************************************************
Name: Snake.h
Author: Christopher McDaniel
Date: 23 February 2020
Class: COSC 4332
Version: 1.1
Copyright: 2020
Description: This is a program that will draw the snake,
draw food, randomly place food, take user input, increase
speed, and initialize gameover when the snake touches its body
or the barrier.

	 DISCLAIMER:
THIS PORTION "Snake.h" IS REQUIRED
TO BE USED IN CONJUNCTION WITH "Window.h" and "Snake.cpp".
*******************************************************/

#include <ctime>
#include <GL/freeglut.h>
#include <stdlib.h>

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

//Define initial starting speed.
#define SPEED 10

//Define arrow keys.
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2

//Define all the functions.
void initGrid(int, int);
void drawGrid();
void snake();
void spawnFood();
void placeFood(int&, int&);
void increaseSpeed(int);
void keyboard(int, int, int);
bool gameover();

//Short global variable.
short arrow = 0;

//Float global variable.
float vel = (SPEED * 0.05);	// increases speed by 5%.

//Bool global variables.
bool endGame = false;	//Not the movie.
bool yummies = true;	//Not to be confused with the Mongolian Grill.

//Int variable is in a different file ("Snake.cpp").
extern int X_grid, Y_grid;

//int global variables.
int length = 1;
int score = 0;
int X_pos[100] = { 20 }, Y_pos[100] = { 20 };
int X_yummies, Y_yummies;

/*
Function: snake
Parameters: (N/A)
Return: snake
Description: Moves snake, sets color of snake,
end game, increase body, size, and velocity.
*/
void snake()
{
	for (int i = length - 1; i > 0; i--)
	{
		X_pos[i] = X_pos[i - 1];
		Y_pos[i] = Y_pos[i - 1];
	}

	//Decrement or increment postion in array to corresponding arrow key. 
	if (arrow == LEFT)
	{
		X_pos[0]--;
	}
	else if (arrow == UP)
	{
		Y_pos[0]++;
	}
	else if (arrow == DOWN)
	{
		Y_pos[0]--;
	}
	else if (arrow == RIGHT)
	{
		X_pos[0]++;
	}

	//Sets color and shape of snake head and body.
	for (int i = 0; i < length; i++)
	{
		if (i == 0)
		{
			glColor3f(0.0, 0.5, 0.0);
		}
		else
		{
			glColor3f(0.0, 0.3, 0.0);
		}
		glRectd(X_pos[i], Y_pos[i], X_pos[i] + 1, Y_pos[i] + 1);
	}

	//End game if the snake goes out of bounds.
	if (X_pos[0] == 0 || X_pos[0] == X_grid - 1 || Y_pos[0] == 0 || Y_pos[0] == Y_grid - 1)
	{
		endGame = true;
	}

	//Increases score, length, and velocity when snake gets a yummy.
	if (X_pos[0] == X_yummies && Y_pos[0] == Y_yummies)
	{
		score++;
		length++;
		vel++;
		yummies = true;
	}

	//If snake impacts it's body end game.
	for (int j = 1; j < length; j++)
	{
		if (X_pos[j] == X_pos[0] && Y_pos[j] == Y_pos[0])
		{
			endGame = true;
		}
	}
}

/*
Function: spawnFood
Parameters: (N/A)
Return: spawnFood
Description: Creates the food shape and color.
*/
void spawnFood()
{
	if (yummies)
	{
		placeFood(X_yummies, Y_yummies);
	}

	glColor3f(1.0, 0.0, 0.0);
	yummies = false;
	glRectf(X_yummies, Y_yummies, X_yummies + 1, Y_yummies + 1);
}

/*
Function: placeFood
Parameters: int &x, int &y
Return: placeFood
Description: randomly places food on the grid.
*/
void placeFood(int &x, int &y)
{
	//initialize variables.
	int X_max = X_grid - 2;
	int Y_max = Y_grid - 2;
	int min = 1;

	//Randomly places food.
	srand(time (NULL));
	x = rand() % (X_max - min) + min;
	y = rand() % (Y_max - min) + min;
}

/*
Function: increaseSpeed
Parameters: int
Return: increaseSpeed
Description: Redisplays the increased speed of
the snake.
*/
void increaseSpeed(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / (SPEED + vel), increaseSpeed, 0);
}

/*
Function: keyboard
Parameters: int key, int, int
Return: keyboard
Description: Takes user input from keyboard arrows
and moves the snake accordingly.
*/
void keyboard(int key, int, int)
{
	switch (key)
	{

	case GLUT_KEY_LEFT:
		if (arrow != RIGHT)
		{
			arrow = LEFT;
		}
		break;

	case GLUT_KEY_UP:
		if (arrow != DOWN)
		{
			arrow = UP;
		}
		break;

	case GLUT_KEY_DOWN:
		if (arrow != UP)
		{
			arrow = DOWN;
		}
		break;

	case GLUT_KEY_RIGHT:
		if (arrow != LEFT)
		{
			arrow = RIGHT;
		}
		break;

	}
}

/*
Function: gameover
Parameters: (N/A)
Return: gameover or retry
Description: Displays "Game Over" message box
and tells you your score.
*/
bool gameover()
{
	if (endGame)
	{
		char highScore[10];
		_itoa_s(score, highScore, 10);	//Convert integer to string.
		char your[50] = "Your snakes length: ";
		strcat_s(your, highScore);	//Append string.
		int msgBoxID = MessageBox(NULL, your, "Game Over", MB_RETRYCANCEL | MB_ICONQUESTION);	//Creates message box
		switch (msgBoxID)
		{
		case IDRETRY:
			WinExec("Assignment 2 (Snake Game).exe", SW_SHOW);

		case IDCANCEL:
			exit(0);
		}
	}
}
#endif