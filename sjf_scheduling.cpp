// Input is number of processes n
// Then input n number of time arrival_time and burst_time
// This is part of preemitive shortest job first scheduling
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
class cpu_schedular
{
public:
	int n;
	vector<vector<int> > process;
	vector<vector<int> > completed;

	cpu_schedular(vector<vector<int> > arr, int m):process(arr), n(m)
	{
	}

	int min_arr_time(int time){
		return 0;
	}

	void heapify(int i, int time){

		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int smallest = i;
		if(l<n && process[smallest][0]<=time && process[l][0]<=time){
		if(l<n && process[l][2] < process[smallest][2])
			smallest = l;}
		else if(l<n && process[smallest][0]>=time && process[l][0]<=time)
				smallest = l;
		if(r<n && process[smallest][0]<=time && process[r][0]<=time){
		if(r<n && process[r][2] < process[smallest][2])
			smallest = r;}
		else if(r<n && process[smallest][0]>=time && process[r][0]<=time)
				smallest = r;
		if(i!=smallest)
		{
			process[i].swap(process[smallest]);
			heapify(smallest, time);
		}
	}

	void priority_queue(int time)
	{
		for(int i=sqrt(n);i>=0;i--)
		{
			heapify(i, time);
		}
	}
	void print(vector<vector<int> > v)
	{
		for(int i=0;i<v.size();i++){
			cout<<v[i][0]<<" "<<v[i][1]<<" "<<v[i][2]<<" "<<v[i][3]<<" "<<v[i][4]<<" "<<v[i][5]<<endl;
		}
	}

	void completed_process(int id, int time){
		process[id][6] = 1;
		vector<int> temp;
		for(int i=0;i<process[id].size();i++)
		temp.push_back(process[id][i]); 
		completed.push_back(temp);
		cout<<"Completed : \n";
		print(completed);
		cout<<"Deleting the completed process : Done.";
		process.erase(process.begin()+id);
		n--;
		heapify(id, time);
	}

	int waiting_time(int id){
		return process[id][3] - process[id][0] - process[id][1];
	}

	int turn_around_time(int id)
	{
		return process[id][3] - process[id][0];
	}

	void sjf_scheduling(){
		int sum = 0;
		for(int i=0;i<n;i++)
		{
			sum += process[i][1];
		}
		int time = 0;
		priority_queue(time);
		cout<<"Process : \n";
		print(process);
		int check = process.size(); 
		while(check){
			int id = -1;
			id = min_arr_time(time);
			process[id][2]-=1;
			time++;
			priority_queue(time);
			cout<<"Level : " << id << " \n";
			print(process);
			cout<<time<<endl;
			if(process[id][2] == 0)
			{
				process[id][3] = time;
				process[id][4] = waiting_time(id);
				process[id][5] = turn_around_time(id);
				completed_process(id, time); 
				check -= 1;
			}
		}
		cout<<"Process Completed : \n";
		print(completed);
	}
};

int main()
{
	int n;
	cin>>n;
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
	cpu_schedular scheduling_1 = cpu_schedular(process,n);
	scheduling_1.sjf_scheduling();
}