#include<iostream>
#include<stdio.h>
using namespace std;

class Jobs{
	int startTime;
	int finishTime;
	bool isScheduled = false;
	public:
		void setStartTime(int start){
			startTime = start;
		}
		void setFinishTime(int finish){
			finishTime = finish;
		}                                                      //hello 
		int getStartTime(){
			return startTime;
		}
		void setScheduled(bool schedule){
			isScheduled = schedule;
		}
		int getFinishTime(){
			return finishTime;
		}
		bool checkScheduled(){
			return isScheduled;
		}
		bool checkOVerlapping(Jobs temp){
			if((startTime>= temp.getFinishTime()) || (finishTime<= temp.getStartTime())){
				return false;
			}else{
				return true;
			}
		}
		void printJob(){
			printf("%d %d\n",startTime,finishTime);
		}
};

int main(){
	int numberOfJobs;
	cin>>numberOfJobs;
	Jobs job[numberOfJobs];
	int timming[numberOfJobs][2];
	for(int i=0;i<numberOfJobs;i++){
		cin>>timming[i][0];
		cin>>timming[i][1];
		job[i].setStartTime(timming[i][0]);
		job[i].setFinishTime(timming[i][1]);
	}
	for(int i=0;i<numberOfJobs;i++){
		for(int j=0;j<numberOfJobs-1;j++){
			if(job[j].getStartTime()>job[j+1].getStartTime()){
				Jobs temp;
				temp = job[j];
				job[j] = job[j+1];
				job[j+1] = temp;
			}
		}
	}
	int numberOfMachines = 0;
	int jobUnscheduled = 0;
	int k=0;
	for(int i=0;i<numberOfJobs;i++){
		if(job[i].checkScheduled() == false){
			k=i;
			numberOfMachines++;
			for (int j=k+1;j<numberOfJobs;j++){
				if((job[j].checkScheduled()==false) && (job[k].checkOVerlapping(job[j]) == false)){
					job[k].setScheduled(true);
					job[j].setScheduled(true);
					k=j;	
				}
			}
		}
	}
	cout<<numberOfMachines;
}
