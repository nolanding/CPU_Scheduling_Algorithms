// Input is number of processes n
// Then input n number of time arrival_time and burst_time
// This is part of priority based scheduling
//For Process Vector 
	// Index 0 - Arrival time
	// Index 1 - Burst time
	// Index 2 - Priority of a process
	// Index 3 - Completed Time
	// Index 4 - Waiting Time
	// Index 5 - Turn Around Time

#include<iostream>
#include<vector>
#include<string>
#include<math.h>
using namespace std;
class priority_based_scheduling{

int n;
vector<vector<int> > process;
vector<vector<int> > completed;

public:
	priority_based_scheduling(vector<vector<int> > arr, int m): process(arr), n(m){
	}

	void heapify(int i){

		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int smallest = i;
		if(l<n && process[smallest][0] > process[l][0])
			smallest = l;
		else if(l<n && process[smallest][0] == process[l][0] && process[smallest][2] > process[l][2])
			smallest = l;
		else if(l<n && process[smallest][0] == process[l][0] && process[smallest][2] == process[l][2] && process[smallest][1] > process[l][1])
			smallest = l;
		if(r<n && process[smallest][0] > process[r][0])
			smallest = r;
		else if(r<n && process[smallest][0] == process[r][0] && process[smallest][2] > process[r][2])
			smallest = r;
		else if(r<n && process[smallest][0] == process[r][0] && process[smallest][2] == process[r][2] && process[smallest][1] > process[r][1])
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

	void print(vector<vector<int> > v)
	{
		for(int i=0;i<v.size();i++){
			cout<<v[i][0]<<" "<<v[i][1]<<" "<<v[i][2]<<" "<<v[i][3]<<" "<<v[i][4]<<" "<<v[i][5]<<endl;
		}
	}

	int waiting_time(int id){
		return process[id][3] - process[id][0] - process[id][1];
	}

	int turn_around_time(int id)
	{
		return process[id][3] - process[id][0];
	}

	void completed_process(int id){
		completed.push_back(process[id]);
		process.erase(process.begin()+id);
		n--;
		heapify(id);
	}
	int min_id(){
		return 0;
	}
	void scheduling()
	{
		int sum = 0;
		for(int i=0;i<n;i++)
		{
			sum += process[i][1];
		}
		int time = 0;
		priority_queue();
		cout<<"Process : \n";
		print(process);
		int loop_over_process = n;
		for(int i=0;i<loop_over_process;i++)
		{
			int id = min_id();
			time += process[id][1];
			process[id][3] = time; 					//Completed Time
			process[id][4] = waiting_time(id);		//Waiting Time (finish - arrival - burst_time)
			process[id][5] = turn_around_time(id);    //Turn Around Time (finish - arrival)
			completed_process(id);
		}
		cout<<"Process Completed : \n";
		print(completed);
	}
};

int main(int argc, char ** argv)
{
	int n;
	cin>>n;
	vector<vector<int> > process(n);
	for(int i=0;i<n;i++)
	{
		process[i] = vector<int>(7, 0);
	}
	for(int i=0;i<n;i++)
	{
		int arrival_time, burst_time, priority;
		cin>>arrival_time>>burst_time>>priority;
		process[i][0] = arrival_time;
		process[i][1] = burst_time;
		process[i][2] = priority;
	}
	priority_based_scheduling obj = priority_based_scheduling(process, n);
	obj.scheduling();
	return 0;
}