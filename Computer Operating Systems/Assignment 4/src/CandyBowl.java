/***********************************************
 * Name: CandyBowl.java
 * Author: Christopher McDaniel
 * Date: 8 April 2020
 * Class: COSC 4327
 * Version: 1.1
 * Copyright: 2020
 * Description: This is a class to be used in
 * conjunction with "Candy.java".
 ***********************************************/

/******************************************************
 * Class: CandyBowl
 * Description: This class initializes the max number of
 * candies and the current amount of candies. It also has
 * two methods that handle the retrieval and filling of
 * candy bowls.
 ******************************************************/
class CandyBowl
{	
	//Integer variables
	int CMax, knt, num;
	
	//CandyBowl constructor that sets the size of bowl that will be used.
	CandyBowl (int CMax, int num)
	{		
		this.CMax = CMax;	//Bowl size.
		this.num = num;	//Identifies bowl.
		knt = CMax;	//Fills bowl.
	}
	
	//A synchronized method.
	//A faculty member retrieves some candy from the bowl.
	synchronized public boolean Retrieve()
	{
		if (knt > 0)	//Bowl is not empty.
		{
			knt--;	//Knt is deprecated.
			System.out.println("Bowl " + num + " has " + knt + " pieces of candy left!\n");
			notifyAll();	//Notify all the threads.
			return true;
		}
		else	//Bowl is empty
		{
			notifyAll();	//Notify all the threads.
			return false;
		}
	}
	
	//A synchronized method.
	//Fill the candy bowl.
	synchronized public void Fill()
	{
		knt = CMax;	//Fills the candy bowl
		System.out.println("A candy bowl has been filled!");
		notifyAll();	///Notify all the threads.
	}
}