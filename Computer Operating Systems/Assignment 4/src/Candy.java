/***********************************************
 * Name: Candy.java
 * Author: Christopher McDaniel
 * Date: 8 April 2020
 * Class: COSC 4327
 * Version: 1.1
 * Copyright: 2020
 * Description: This is a program that utilizes a
 * Java synchronized class to simulate a candy bowl
 * with faculty members being able to take from it
 * one at a time and a TA that fills the bowl when
 * it is empty of 'Candy'. 
 ***********************************************/

import java.util.Scanner;	//Allows for use of the Scanner class to obtain inputs involving primitive input types.

/******************************************************
 * Class: Candy
 * Description: This class handles the menu options
 * and executes them as well. It is the main class
 * for this program.
 ******************************************************/
public class Candy
{
	static Scanner input = new Scanner(System.in);	//Obtain primitive type inputs.
	public static void main (String[]args)
	{
		//Integer variable
		int choice = 1;
		
		/*GUI*/
		System.out.println("Interface");
		System.out.println("1. Default, has a predetermined amount of 'faculty members', one TA, and one candy bowl.");
		System.out.println("2. Pick your own.");
		System.out.print("Choice: ");
		choice = input.nextInt();
		System.out.print("\n");
		
		//Switch of the user choice the call appropriate function.
		switch (choice)
		{
		default:	//Default to this if user given choice is not valid.
			System.out.println("User gave a choice that is not one of the given, using default one due to this.");
			Default();
			break;
		case 1:	//Calls default function.
			Default();
			break;
		case 2:	//Calls User function.
			User();
			break;
		}
	}
	
	//Execution of the default menu option.
	private static void Default()
	{
		//Integer variables
		int Sleep, k;
		
		//Default faculty names.
		String[] names = {"Dr. Smith", "Dr. Cooper", "Dr.Burris", "Dr. Zhou", "Dr. Islam", "Dr. Lester"};
		
		CandyBowl[] Bowls = new CandyBowl[1];	//How many bowls.
		TA[] TAs = new TA[1];	//How many TAs.
		Faculty[] Members = new Faculty[6];	//How many faculty members.
		
		Bowls[0] = new CandyBowl(20, 0);	//Bowl size and number for Default.
		TAs[0] = new TA(Bowls, "The TA");	//Assign TA to Bowl.
		
		Sleep = 500;	//This is the default sleep time. It can be changed.
		
		for (k = 0; k < 6; k++)
		{
			Members[k] = new Faculty(Bowls, TAs, Sleep, names[k]);
			Members[k].start();
		}
	}
	
	//Execution of the user defined menu option.
	private static void User()
	{
		//String variable
		String name;
		
		//Integer variables
		int k, FKnt, TAKnt, BKnt, PKnt, Sleep, choice, Time;
		
		//Ask for user input for operation.
		System.out.print("How many faculty members are there?: ");
		FKnt = input.nextInt();		//User input.
		
		System.out.print("How many TAs will be filling the bowl(s)?: ");
		TAKnt = input.nextInt();	//User input.
		
		System.out.print("How many bowls of candy?: ");
		BKnt = input.nextInt();		//User input.
		
		System.out.print("How much candy is in the bowl(s)?: ");
		PKnt = input.nextInt();		//User input.
		
		System.out.print("Sleep time (ms): ");
		Sleep = input.nextInt();	//User input.
		System.out.print("\n");
		
		CandyBowl[] Bowls = new CandyBowl[BKnt];
		TA[] TAs = new TA[TAKnt];
		Faculty[] Members = new Faculty[FKnt];
		
		for (k = 0; k < BKnt; k++)	//Candy Bowl
		{
			Bowls[k] = new CandyBowl(PKnt, k);
		}
		
		for (k = 0; k < TAKnt; k++)	//TA
		{
			name = "TA " + k;
			TAs[k] = new TA(Bowls, name);
		}
		
		for (k = 0; k < FKnt; k++)	//Faculty
		{
			name = "Faculty Member " + k;
			Members[k] = new Faculty(Bowls, TAs, Sleep, name);
		}
		
		//Ask user to select a runtime.
		System.out.println("How long do you want it to run?");
		System.out.println("1. Endless");
		System.out.println("2. Not endless");
		System.out.print("Choice: ");
		choice = input.nextInt();	//User input.
		System.out.print("\n");
		
		//Switch to operate the user given choice of run time.
		switch (choice)
		{
		default:	//Endless
			System.out.println("User gave a choice that is not one of the given, the application will now run endlessly.");
			System.out.println("\n");
		case 1:	//Endless
			for (k = 0; k < FKnt; k++)
			{
				Members[k].start();
			}
			break;
		case 2:	//User given time.
			System.out.print("How long do you want it to run (ms): ");
			Time = input.nextInt();	//User input
			System.out.print("\n");
			System.out.print("********************************************");
			
			for (k = 0; k < FKnt; k++)
			{
				Members[k].start();
			}
			try
			{				
				Thread.sleep(Time);	//Pause execution for specified time.
				System.out.println("End of the line!\n");
				
				for (k = 0; k < FKnt; k++)
				{
					Members[k].interrupt();	//Interrupts the thread
				}
			}
			catch (InterruptedException e){}	//Catches the interrupted thread.
			break;
		}
	}
}