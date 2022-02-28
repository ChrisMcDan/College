#ifndef Structures_H
#define Structures_H

/*
class for scheduler object
*/
class scheduler
{
public:
	int PID;		//Process ID
	int arrival;    //Arrival time
	int priority;   //Priority
	int cpu_time;    //Burst time
	int cpu_left;    //Time still needed
	int cpu_done;    //Completed time
	int exit;		//Process is completed
	int RR;			//RR Q=2
	
	scheduler() {}

	//Constructor
	scheduler(int id, int arriv, int pri, int cpuT)
	{
		PID = id;
		arrival = arriv;
		priority = pri;
		cpu_time = cpuT;
		cpu_left = cpuT;
		cpu_done = 0;
		cpu_left = 0;
		exit = 0;
		RR = 0;
	}

	~scheduler() {}
};

struct Compare_Priorities
{
	bool operator()(const scheduler& p1, const scheduler& p2)
	{
		return p1.priority > p2.priority;
	}
};

#endif /* Structures_H */