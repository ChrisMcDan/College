//******************************************************
//Name: Assignment_1.Polygons.java
//Author: Chrisotpher McDaniel
//Date: 31 January 2020
//Class: COSC 4332
//Version: 1.1
//Copyright: 2020
//Description: This is a program that will display
//the outlines and fillings of regular polygons from
//a triangle all the way up to an octagon, including
//a circle. Each polygon will be a different color.
//
//     DISCLAIMER:
//THIS PORTION "EventListener.java" IS REQUIRED
//TO BE USED IN CONJUNCTION WITH "Polygons.java".
//******************************************************

package opengl101;

import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.glu.GLU;


public class EventListener implements GLEventListener
{
	//Global variables.
	float x, y;
	int i;

	/*
	* Function: Triangle
	* Parameters: GLAutoDrawable drawable
	* Return: Triangle
	* Description: Draws the outline and filling of a Triangle.
	*/
	public static void Triangle(GLAutoDrawable drawable)
	{
		GL2 gl = drawable.getGL().getGL2();


		//////////// TRIANGLE ////////////

		gl.glColor3d(0, 0, 1);	//Blue
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(-6.0, 0, 0);	//Move to coordinates
		gl.glRotatef(90, 0, 0, 1);	//Rotate 90 degrees

		gl.glBegin(GL2.GL_LINE_LOOP);	//Draws connected lines
		for(int i = 0; i <= 3; i++)
		{
			double angle =  (2 * Math.PI) * i / 3;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.

		gl.glPopMatrix();	//Pops from stack


		//////////// FILLED TRIANGLE ////////////
			
		gl.glColor3d(0, 0, 0.5);	//Dark blue
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(-6.0, -1.1, 0);	//Move to coordinates
		gl.glRotatef(-90, 0, 0, 1);	//Rotate -90 degrees

		gl.glBegin(GL2.GL_TRIANGLES);	//Draws polygon
		for(int i = 0; i <= 3; i++)
		{
			double angle =  (2 * Math.PI) * i / 3;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.
		
		gl.glPopMatrix();	//Pops from stack

	}
	
	
	/*
	* Function: Square
	* Parameters: GLAutoDrawable drawable
	* Return: Square
	* Description: Draws the outline and filling of a Square.
	*/
	public static void Square(GLAutoDrawable drawable)
	{
		GL2 gl = drawable.getGL().getGL2();


		//////////// SQUARE ////////////

		gl.glColor3f(1, 0, 1);	//Purple
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(-4.0, 0.20, 0);	//Move to coordinates
		gl.glRotatef(45, 0, 0, 1);	//Rotate 45 degrees

		gl.glBegin(GL2.GL_LINE_LOOP);	//Draws connected lines
		for(int i = 0; i <= 4; i++)
		{
			double angle =  (2 * Math.PI) * i / 4;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.

		gl.glPopMatrix();	//Pops from stack
		

		//////////// FILLED SQUARE ////////////

		gl.glColor3d(0.7, 0, 0.7);	//Dark purple
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(-4.0, -1.30, 0);	//Move to coordinates
		gl.glRotatef(-45, 0, 0, 1);	//Rotate -45 degrees

		gl.glBegin(GL2.GL_QUADS);  //Draws polygon
		for(int i = 0; i <= 4; i++)
		{
			double angle =  (2 * Math.PI) * i / 4;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.

		gl.glPopMatrix();	//Pops from stack
		
	}

	/*
	* Function: Pentagon
	* Parameters: GLAutoDrawable drawable
	* Return: Pentagon
	* Description: Draws the outline and filling of a Pentagon.
	*/
	public static void Pentagon(GLAutoDrawable drawable)
	{
		GL2 gl = drawable.getGL().getGL2();



		////////////REGULAR PENTAGON ////////////

		gl.glColor3f(0, 1, 0);	//Green
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(-2.0, 0.30, 0);	//Move to coordinates
		gl.glRotatef(90, 0, 0, 1);	//Rotate 90 degrees

		gl.glBegin(GL2.GL_LINE_LOOP);	//Draws connected lines
		for(int i = 0; i <= 5; i++)
		{
			double angle =  (2 * Math.PI) * i / 5;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.

		gl.glPopMatrix();	//Pops from stack

		//////////// FILLED REGULAR PENTAGON ////////////

		gl.glColor3d(0, 0.7, 0);	//Dark green
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(-2.0, -1.40, 0);	//Move to coordinates
		gl.glRotatef(-90, 0, 0, 1);	//Rotate -90 degrees

		gl.glBegin(GL2.GL_POLYGON);  //Draws polygon
		for(int i = 0; i <= 5; i++)
		{
			double angle =  (2 * Math.PI) * i / 5;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.
		
		gl.glPopMatrix();	//Pops from stack

	}

	/*
	* Function: Hexagon
	* Parameters: GLAutoDrawable drawable
	* Return: Hexagon
	* Description: Draws the outline and filling of a Hexagon.
	*/
	public static void Hexagon(GLAutoDrawable drawable)
	{
		GL2 gl = drawable.getGL().getGL2();


		////////////REGULAR HEXAGON ////////////

		gl.glColor3f(1, 1, 0);	//Yellow
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(0, 0.35, 0);	//Move to coordinates
		gl.glRotatef(60, 0, 0, 1);	//Rotate 60 degrees

		gl.glBegin(GL2.GL_LINE_LOOP);	//Draws connected lines
		for(int i = 0; i <= 6; i++)
		{
			double angle =  (2 * Math.PI) * i / 6;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.

		gl.glPopMatrix();	//Pops from stack

		
		//////////// FILLED REGULAR HEXAGON ////////////

		gl.glColor3d(0.7, 0.7, 0);	//Dark yellow
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(0, -1.48, 0);	//Move to coordinates
		gl.glRotatef(-60, 0, 0, 1);	//Rotate -60 degrees

		gl.glBegin(GL2.GL_POLYGON);  //Draws polygon
		for(int i = 0; i <= 6; i++)
		{
			double angle =  (2 * Math.PI) * i / 6;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.

		gl.glPopMatrix();	//Pops from stack

	}

	/*
	* Function: Heptagon
	* Parameters: GLAutoDrawable drawable
	* Return: Heptagon
	* Description: Draws the outline and filling of a Heptagon.
	*/
	public static void Heptagon(GLAutoDrawable drawable)
	{
		GL2 gl = drawable.getGL().getGL2();


		////////////REGULAR HEPTAGON ////////////

		gl.glColor3f(0, 1, 1);	//Cyan
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(2.0, 0.37, 0);	//Move to coordinates
		gl.glRotated(38.6, 0, 0, 1);	//Rotate 38.6 degrees

		gl.glBegin(GL2.GL_LINE_LOOP);	//Draws connected lines
		for(int i = 0; i <= 7; i++)
		{
			double angle =  (2 * Math.PI) * i / 7;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.
		
		gl.glPopMatrix();	//Pops from stack


		//////////// FILLED REGULAR HEPTAGON ////////////

		gl.glColor3d(0, 0.7, 0.7);	//Dark cyan
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(2.0, -1.55, 0);	//Move to coordinates
		gl.glRotated(-38.6, 0, 0, 1);	//Rotate -38.6 degrees

		gl.glBegin(GL2.GL_POLYGON);  //Draws polygon
		for(int i = 0; i <= 7; i++)
		{
			double angle =  (2 * Math.PI) * i / 7;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.
		
		gl.glPopMatrix();	//Pops from stack

	}
	
	/*
	* Function: Octagon
	* Parameters: GLAutoDrawable drawable
	* Return: Octagon
	* Description: Draws the outline and filling of a Octagon.
	*/
	public static void Octagon(GLAutoDrawable drawable)
	{
		GL2 gl = drawable.getGL().getGL2();


		////////////REGULAR OCTAGON ////////////

		gl.glColor3f(1, 0, 0);	//Red
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(4.0, 0.37, 0);	//Move to coordinates
		gl.glRotated(22.5, 0, 0, 1);	//Rotate 22.5 degrees

		gl.glBegin(GL2.GL_LINE_LOOP);	//Draws connected lines
		for(int i = 0; i <= 8; i++)
		{
			double angle =  (2 * Math.PI) * i / 8;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.
		
		gl.glPopMatrix();	//Pops from stack


		//////////// FILLED REGULAR OCTAGON ////////////

		gl.glColor3d(0.5, 0, 0);	//Dark red
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(4.0, -1.60, 0);	//Move to coordinates
		gl.glRotated(-22.5, 0, 0, 1);	//Rotate -22.5 degrees

		gl.glBegin(GL2.GL_POLYGON);  //Draws polygon
		for(int i = 0; i <= 8; i++)
		{
			double angle =  (2 * Math.PI) * i / 8;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.
		
		gl.glPopMatrix();	//Pops from stack

	}

	/*
	* Function: Circle
	* Parameters: GLAutoDrawable drawable
	* Return: Circle
	* Description: Draws the outline and filling of a Circle.
	*/
	public static void Circle(GLAutoDrawable drawable)
	{
		GL2 gl = drawable.getGL().getGL2();


		//////////// CIRCLE ////////////

		gl.glColor3f(1, 1, 1);	//White
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(6.0, 0.45, 0);	//Move to coordinates

		gl.glBegin(GL2.GL_LINE_LOOP);	//Draws connected lines
		for(int i = 0; i <= 1000; i++)
		{
			double angle =  (2 * Math.PI) * i / 1000;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.
		
		gl.glPopMatrix();	//Pops from stack


		//////////// FILLED CIRCLE ////////////
		
		gl.glPushMatrix();	//Push onto stack
		gl.glTranslated(6.0, -1.65, 0);	//Move to coordinates

		gl.glColor3f(0, 0, 0);	//Black

		gl.glBegin(GL2.GL_POLYGON);	//Draws polygon
		for(int i = 0; i <= 1000; i++)
		{
			double angle =  2 * Math.PI * i / 1000;
			double x = Math.cos(angle);
			double y = Math.sin(angle);
			gl.glVertex2d(x,y);
		}
		gl.glEnd();
		gl.glFlush();	//Process all OpenGL routines as quickly as possible.
		
		gl.glPopMatrix();	//Pops from stack

	}

	/*
	* Function: Display
	* Parameters: GLAutoDrawable drawable
	* Return: Display
	* Description: Calls the above functions in order
	* to display the polygons.
	*/
	public void display(GLAutoDrawable drawable)
	{
		GL2 gl = drawable.getGL().getGL2();

		gl.glClear(GL2.GL_COLOR_BUFFER_BIT);	//Clear display window.

		//Function calls
		Triangle(drawable);
		Square(drawable);
		Pentagon(drawable);
		Hexagon(drawable);
		Heptagon(drawable);
		Octagon(drawable);
		Circle(drawable);

	}

	/*
	* Function: init
	* Parameters: GLAutoDrawable drawable
	* Return: init
	* Description: Initializes the coordinate grid
	* that is apart of the window.
	*/
	public void init(GLAutoDrawable drawable)
	{
		GL2 gl = drawable.getGL().getGL2();
		GLU glu = new GLU();

		gl.glClearColor(.5f, .5f, .5f, 0f);	//Set display window color.

		gl.glMatrixMode(GL2.GL_PROJECTION);
		gl.glLoadIdentity();
		glu.gluOrtho2D(
				-8.0, 8.0,		//Left, Right
				-6.0, 6.0);		//Top, Bottom
		gl.glMatrixMode(GL2.GL_MODELVIEW);
		x = 0.005f;
	}
	

	@Override
	public void dispose(GLAutoDrawable drawable) {
		// TODO Auto-generated method stub
		
	}
	

	@Override
	public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
		// TODO Auto-generated method stub
		
	}
}