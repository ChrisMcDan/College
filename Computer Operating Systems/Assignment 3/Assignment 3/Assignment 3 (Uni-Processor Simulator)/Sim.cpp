/*************************************************************
Preemptive-Priority Scheduler with a Priority Queue using a
secondary algorithm of round robin with a quantum factor of 2.
*************************************************************/

#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "Structures.h"

using namespace std;

/********************
Function declarations
********************/
bool que_empty();

int main();
int job_amount(); //collects # of jobs to schedule
int total_time(vector<scheduler>& vec); //calcs time needed to run all jobs

void job_attributes(vector<scheduler>& vec, int n); //puts created jobs into vector
void display_vector(const vector<scheduler> vec); //prints job vector data
void arrival_check(vector<scheduler> vec, int t); //notes arrivals as needed
void cpu_usage(); //manages cpu usage
void display_time(int curr_time); //displays time units
void preemption(int TID); //notes preemptions
void tie_breaker(); //manages round robin secondary
void turnaround(vector<scheduler> vec);//calcs job TaT's and avg TaT
void exit_check(int curr_time, int calc_time, vector<scheduler>& vec);//note/update when jobs exit
void display(int calc_time, vector<scheduler> vec); //driver for scheduling of jobs
//void ludacrisSpeed(); //speed controller

/***************************
global variables/structures
***************************/
priority_queue<scheduler, vector<scheduler>, Compare_Priorities> que;
int selector = 1;

/******************
Function definitons
******************/
bool que_empty()
{
	if (que.empty())
	{
		return true;
	}
}

int job_amount()
{
	int num;
	
	cout << "There are ";
	cin >> num;
	cout << num;
	cout << " jobs to complete";
	cout << endl << endl;

	return num;
}

int total_time(vector<scheduler>& vec)
{
	int calc_time = 0;

	for (int i = 0; i < vec.size(); i++)
	{
		calc_time = calc_time + vec.at(i).cpu_time;
	}
	
	return calc_time;
}

void job_attributes(vector<scheduler>& vec, int n)
{
	int arrive;
	int prio;
	int cpu;

	for (int i = 0; i < n; i++)
	{
		cout << "Job #: " << i;
		cout << endl;

		cout << "Arrive: "; cin >> arrive; cout << arrive << endl;
		cout << "Priority: "; cin >> prio; cout << prio << endl;
		cout << "CPU_Time: "; cin >> cpu; cout << cpu << endl << endl;

		scheduler job(i, arrive, prio, cpu);
		job.cpu_left = job.cpu_time;
		vec.push_back(job);
	}
}

void display_vector(const vector<scheduler> vec)
{
	cout << "JOB CHART" << endl
		<< "#  Ar Pr CT CL CD NN" << endl;

	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i].PID << "  "
			<< vec[i].arrival << "  "
			<< vec[i].priority << "  "
			<< vec[i].cpu_time << "  "
			<< vec[i].cpu_left << "  "
			<< vec[i].cpu_done << "  "
			<< vec[i].exit << endl;
	}
	cout << endl;
}

void arrival_check(vector<scheduler> vec, int curr_time)
{
	scheduler temp;
	int preempt;

	if (!que_empty())
	{
		preempt = que.top().PID;
	}

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec.at(i).arrival == curr_time)
		{
			cout << "Job: " << vec.at(i).PID << " arrival" << endl;
			temp = vec.at(i);

			if (!que_empty())
			{
				if (temp.priority < que.top().priority)
				{
					cout << "CONTEXT SWITCH"
						<< endl
						<< "job " << preempt << " preempts"
						<< endl;
				}
			}

			que.push(temp);
		}
	}
}

void cpu_usage()
{
	int TID = que.top().PID;
	scheduler temp = que.top();

	if (!que_empty())
	{
		cout << "Job: " << TID << " runs" << endl;

		que.pop();

		temp.cpu_done++;
		temp.RR++;
		temp.cpu_left--;
		
		que.push(temp);

		while (que.top().PID != temp.PID)
		{
			scheduler hold = que.top(); //Maybe move to top?
			que.pop();
			que.push(hold);
		}
	}
}

void display_time(int curr_time)
{
	cout << "TIME = " << curr_time;
	cout << endl;
	cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔";
	cout << endl;
}

void preemption(int TID)
{
	cout << "Job: " << TID << " preempts" << endl;
}

void tie_breaker()
{
	scheduler temp = que.top();
	int TID = temp.PID;

	if (que.top().RR > 1)
	{
		que.pop();

		if ((que.top().PID != temp.PID) && (que.top().priority == temp.priority))
		{
			temp.RR = 0;
			que.push(temp);
			preemption(TID);
		}
		else
		{
			que.push(temp);
		}
	}
}

void turnaround(vector<scheduler> vec)
{
	int i;

	float avg_turnaround = 0;

	cout << "Turnaround" << endl;
	cout << "▔▔▔▔▔▔▔▔▔▔▔" << endl;
	cout << "Job [] turnaround time: EXIT - ARRIVAL = []" << endl;
	cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;

	for (i = 0; i < vec.size(); i++)
	{
		float job_turnaround = vec.at(i).exit - vec.at(i).arrival;
		avg_turnaround = avg_turnaround + job_turnaround;
		cout << "Job " << i << "turnaround time: " << vec.at(i).exit
			<< " - " << vec.at(i).arrival << " = " << job_turnaround
			<< endl;
	}

	cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << endl;
	cout << "Average Turnaround time: " << avg_turnaround / vec.size();
	cout << endl;
}

void exit_check(int curr_time, int calc_time, vector<scheduler>& vec)
{
	scheduler temp = que.top();
	int TID = temp.PID;

	if (!que_empty())
	{
		que.pop();

		cout << "Job: " << TID << " exits" << endl;
		if (temp.cpu_left == 0)
		{
			for (int i = 0; i < vec.size(); i++)
			{
				if (vec.at(i).PID == TID)
				{
					vec.at(i).exit = curr_time;
				}
			}

			if (que_empty())
			{
				exit_check(curr_time, calc_time, vec);
			}
			else
			{
				cout << "Context Switch" << endl;
			}
		}
	}
	else
	{
		if (curr_time < calc_time)
		{
			cout << "Empty cycle" << endl;
		}
		else
		{
			cout << "QUEUE IS EMPTY" << endl;
			turnaround(vec);
			exit(0);
		}
	}
}

void display(int calc_time, vector<scheduler> vec)
{
	for (int curr_time = 0; curr_time <= calc_time; curr_time++)
	{
		display_time(curr_time);
		arrival_check(vec, curr_time);
		exit_check(curr_time, calc_time, vec);
		tie_breaker();
		cpu_usage();

		if (!que_empty() && curr_time == calc_time)
		{
			calc_time++;
		}
	}
}

int main()
{
	int n = job_amount();

	vector<scheduler> scheduler_vector;

	job_attributes(scheduler_vector, n);
	display_vector(scheduler_vector);

	int time = total_time(scheduler_vector);

	display(time, scheduler_vector);

	return 0;
}