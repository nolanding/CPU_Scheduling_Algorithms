// Input is number of processes n and time quantum for qound robin q
// Then input n number of  arrival_time and burst_time
// This is part of Round Robin scheduling
//For Process Vector 
	// Index 0 - Arrival time
	// Index 1 - Burst time
	// Index 2 - Remaining time, Initial Value equal to burst time.
	// Index 3 - Completed Time
	// Index 4 - Waiting Time
	// Index 5 - Turn Around Time


#include<iostream>
#include<vector>
#include<string.h>
#include<math.h>
using namespace std;
class round_robin_scheduling{

	int n;
	vector<vector<int> > process;
	vector<vector<int> > completed;
	int quantum;

public: 
	round_robin_scheduling(vector<vector<int> > process, int m, int quantum): process(process), n(m), quantum(quantum){}

	void heapify(int i){

		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int smallest = i;
		if(l<n && process[l][0] < process[smallest][0])
			smallest = l;
		if(r<n && process[r][0] < process[smallest][0])
			smallest = r;
		if(i!=smallest)
		{
			process[i].swap(process[smallest]);
			heapify(smallest);
		}
	}

	void priority_queue()
	{
		for(int i=sqrt(n);i>=0;i--)
		{
			heapify(i);
		}
	}

	int waiting_time(int id)
	{
		return process[id][3] - process[id][0] - process[id][1];
	}

	int turn_around_time(int id)
	{
		return process[id][3] - process[id][0];
	}

	void print(vector<vector<int> > v)
	{
		for(int i=0;i<n;i++)
			cout<<v[i][0]<<" "<<v[i][1]<<" "<<v[i][2]<<" "<<v[i][3]<<" "<<v[i][4]<<" "<<v[i][5]<<endl;
	}

	void scheduling()
	{
		int sum_burst_time = 0;
		for(int i=0;i<n;i++)
		{
			sum_burst_time += process[i][1];
		}
		priority_queue();
		int time = 0;
		cout<<"Burst Time : "<<sum_burst_time<<endl;
		while(sum_burst_time){
			for(int i=0;i<n;i++)
			{
				if(process[i][2]>=quantum)
				{
					process[i][2] -= quantum;
					sum_burst_time -= quantum;
					time += quantum;
				}
				else 
				{
					sum_burst_time -= process[i][2];
					time += process[i][2];
					process[i][2] = 0;
				}
				if(process[i][2]==0 && process[i][3]==0)
				{
					process[i][3] = time;
					process[i][4] = waiting_time(i);
					process[i][5] = turn_around_time(i);
				}
			}
		}
		cout<<"Completed Process : "<<endl;
		print(process);
	}

};

int main()
{
	int n;
	cin>>n;
	int quantum;
	cin>>quantum;
	vector<vector<int> > process(n);
	for(int i=0;i<n;i++)
	{
		process[i] = vector<int>(6, 0);
	}
	int sum = 0;
	for(int i=0;i<n;i++)
	{
		int arrival_time, burst_time;
		cin>>arrival_time;cin>>burst_time;
		sum += burst_time;
		process[i][0] = (arrival_time);
		process[i][1] = (burst_time);
		process[i][2] = (burst_time);
	}
	round_robin_scheduling obj = round_robin_scheduling(process, n, quantum);
	obj.scheduling();
}