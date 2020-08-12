//input 
// n = number of processes.
// process 
// 0 = arrival time
// 1 = burst_time
// 7 = queue_level_priority
// 4 = scheduling algoithm to be used 


// basic case for different along the queue different scheduling algorithms will be used.
#include<iostream>
#include<vector>
#include<string.h>
#include<math.h>
using namespace std;
class multilevel_queue_scheduling{
	int n;
	vector<vector<int> > process;
	enum queue_level {System_Processes=1, Interactive_Processes=2, Interactive_Editing_Processes=3, Batch_Processes=4,Student_Processes=5}; 
	enum scheduling_algo{fcfs=1, sjf=2, priority=3, round_robin=4};
	vector<vector<int> > completed;

public:
	multilevel_queue_scheduling(vector<vector<int> >process, int n):process(process), n(n){}

	void queue_heapify(int i, int time){

		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int smallest = i;
		if(l<n && process[l][0] <= time && process[smallest][0] <= time)
			{
				if(process[l][7] < process[smallest][7])
					smallest = l;
			}
		else if(l<n && process[l][0] <= time && process[smallest][0] > time)
			smallest = l;

		if(r<n && process[r][0] <= time && process[smallest][0] <= time)
			{
				if(process[r][7] < process[smallest][7])
					smallest = r;
			}
		else if(r<n && process[r][0] <= time && process[smallest][0] > time)
			smallest = r;
		
		if(i!=smallest)
		{
			process[i].swap(process[smallest]);
			queue_heapify(smallest, time);
		}
	}

	void priority_queue(int time)
	{
		for(int i=sqrt(n);i>=0;i--)
		{
			queue_heapify(i, time);
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
		queue_heapify(id, time);
	}

	int waiting_time(int id){
		return process[id][3] - process[id][0] - process[id][1];
	}

	int turn_around_time(int id)
	{
		return process[id][3] - process[id][0];
	}

	int min_arr_time(int time){
		return 0;
	}

	void scheduler(){
		int time = 0;
		priority_queue(time);
		cout<<"Process : \n";
		print(process);
		int check = process.size(); 
		while(check){
			int id = -1;
			id = min_arr_time(time);
			process[id][2] -= 1;
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

	void print(vector<vector<int> > v){
		for(int i=0;i<v.size();i++){
			cout<<v[i][0]<<" "<<v[i][2]<<" "<<v[i][7]<<endl;
		}
	}
};

int main()
{
	int n; // number of processes
	cin>>n;
	vector<vector<int> > process(n);
	for(int i=0;i<n;i++)
	{
		process[i] = vector<int>(8, 0);
	}
	for(int i=0;i<n;i++)
	{
		int arrival_time, burst_time, q_level;
		cin>>arrival_time>>burst_time>>q_level;
		process[i][0] = (arrival_time);
		process[i][1] = (burst_time);
		process[i][2] = (burst_time);
		process[i][7] = (q_level);
		cout<<process[i].size()<<endl;
	}
	multilevel_queue_scheduling obj = multilevel_queue_scheduling(process, n);
	obj.scheduler();
}