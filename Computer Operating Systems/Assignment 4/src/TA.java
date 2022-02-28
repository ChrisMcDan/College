/***********************************************
 * Name: TA.java
 * Author: Christopher McDaniel
 * Date: 8 April 2020
 * Class: COSC 4327
 * Version: 1.1
 * Copyright: 2020
 * Description: This is a class to be used in
 * conjunction with "Candy.java".
 ***********************************************/

/******************************************************
 * Class: TA
 * Description: This class handles the filling of a
 * designated candy bowl that is empty.
 ******************************************************/
class TA
{
	//Array variable.
	CandyBowl[] BowlList;
	
	//String variable.
	String name;
	
	//TA constructor.
	TA (CandyBowl[] BowlList, String name)
	{
		this.BowlList = BowlList;
		this.name = name;
	}
	
	//TA fills the candy.
	public void FillCandy (int target)
	{
		BowlList[target].Fill();
		System.out.println("***************************************");
		System.out.println(name + " has filled bowl " + target);
		System.out.println("***************************************");
	}
}