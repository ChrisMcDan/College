//******************************************************
//Name: Assignment_1.Polygons.java
//Author: Chrisotpher McDaniel
//Date: 31 January 2020
//Class: COSC 4332
//Version: 1.1
//Copyright: 2020
//Description: This is a program that will display a
//1023 x 767 gray NEWT window with a special title name.
//The window will not be able to change sizes unless the
//size is changed within the code itself.
//
//     DISCLAIMER:
//THIS PORTION "Polygons.java" IS REQUIRED
//TO BE USED IN CONJUNCTION WITH "EventListener.java".
//******************************************************

package opengl101;

import com.jogamp.newt.opengl.GLWindow;
import com.jogamp.opengl.GLCapabilities;
import com.jogamp.opengl.GLProfile;
import com.jogamp.opengl.util.FPSAnimator;

public class Polygons
{

	private static GLWindow window = null;

	/*
	* Function: init
	* Parameters: (N/A)
	* Return: init
	* Description: Initially sets up the NEWT window
	* that will display the polygons.
	*/
	public static void init()
	{
		//Getting the capabilities object of GL2 profile.
		GLProfile.initSingleton();
		final GLProfile profile = GLProfile.get(GLProfile.GL2);
		GLCapabilities capabilities = new GLCapabilities(profile);

		window = GLWindow.create(capabilities);	//Assigns this to variable window
		window.setTitle("Christopher McDaniel's Fantastic Polygons");	//Window Title
		window.setSize(1023, 767);	//Window Dimensions
		window.setResizable(false);	//Window can't resize
		window.addGLEventListener(new EventListener());
		
		FPSAnimator animator = new FPSAnimator(window, 60);	//Keeps window open
		animator.start();	//Starts above line

		window.setVisible(true);	//Display the window
	}

	/*
	* Function: main
	* Parameters: String[] args
	* Return: main
	* Description: Calls the "init" function that
	* displays the NEWT window.
	*/
	public static void main(String[] args)
	{
		init();

	}

}