/***********************************************
 * Name: Faculty.java
 * Author: Christopher McDaniel
 * Date: 8 April 2020
 * Class: COSC 4327
 * Version: 1.1
 * Copyright: 2020
 * Description: This is a class to be used in
 * conjunction with "Candy.java".
 ***********************************************/

import java.util.Random;

/******************************************************
 * Class: Faculty
 * Description: This class handles when the faculty
 * member is getting a piece of candy and when they are
 * sleeping.
 ******************************************************/
class Faculty extends Thread
{
	//Array variables
	CandyBowl[] BowlList;
	TA[] TAList;
	
	//String variable
	String name;
	
	//Random variable
	Random rng = new Random();
	
	//Integer variables
	int BKnt, CKnt, TAKnt, SMax, Sleep, target;
	
	//Boolean variable
	boolean Status;
	
	//Faculty constructor to set the local variables.
	Faculty (CandyBowl[] BowlList, TA[] TAList, int SMax, String name)
	{
		CKnt = 0;	//Candy count is 0.
		
		this.BowlList = BowlList;	//List of bowls in the array.
		this.TAList = TAList;	///List of TAs in the array.
		this.SMax = SMax;	//Maximum amount of sleep.
		this.name = name;	//Name
		
		BKnt = BowlList.length;	//Bowl count.
		TAKnt = TAList.length;	//TA count.
	}
	
	//Runs the thread.
	public void run()
	{
		try	//Sleep and Eat loop.
		{
			while (true)
			{
				target = rng.nextInt(BKnt);	//Target bowl.
				Status = BowlList[target].Retrieve();	//Does said bowl have candy?
				
				if (Status == true)	//If bowl is empty fill it.
				{
					CKnt++;	//Increase faculty member amount of had candy.
					
					Sleep = rng.nextInt(SMax);	//Faculty member goes to sleep.
					
					System.out.println(name + " had a piece of candy and waits for " + Sleep + " milliseconds...");
					
					Thread.sleep(Sleep);	//Thread goes to sleep
				}
				else	//Bowl has candy.
				{
					TAList[rng.nextInt(TAKnt)].FillCandy(target);
				}
			}
		}
		
		catch (InterruptedException e){}	//Catches the interrupted thread.
		
		finally	//The faculty members ate this much candy.
		{
			System.out.println(name + " has eaten " + CKnt + " pieces of candy!");
		}
	}
}