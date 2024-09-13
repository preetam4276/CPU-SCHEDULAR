#include <iostream>
using namespace std;



struct process {
	int noOfProcess; 
	int** processList; 
	int* waitingTime; 
	int* completionTime; 
	int* turnAroundTime;
	
	process(int processCount){ 
		
		noOfProcess = processCount;
    	
    	processList = new int* [processCount];
		for (int i = 0; i < processCount; i++)
			processList[i] = new int[3];
		
		for(int i = 0; i < processCount; i++){
			for(int j=0; j < 3; j++){
				processList[i][j] =0;
			}
		}
		
    	waitingTime = new int [processCount];
    	turnAroundTime = new int [processCount];
    	completionTime = new int [processCount];
	}
};

void userPrompt(process p);
void print(process p); 
void waitingTime(process p); 
void completionTime(process p); 
void turnAroundTime(process p);
void avgWaitingAndTurnAroundTime(process p); 

int main(){
	
	
	cout<<"ENter the total number of process: ";
	int noOfProcess;
  	cin >> noOfProcess;
  	
	process p(noOfProcess); 
	
	userPrompt(p);
	completionTime(p); 
	waitingTime(p);  
	turnAroundTime(p);
	print(p); 
	avgWaitingAndTurnAroundTime(p);
}
void userPrompt(process p){
	int burstTime;
	int pID;
	int priority;
	for(int i = 0; i < p.noOfProcess; ++i){
		pID=i+1;
		cout<<"Enter Brust time for process-"<< pID <<"	"; 
		cin>>burstTime;	
		cout<< "ENter the priority for process-"<< pID <<" ";
		cin>>priority;
		p.processList[i][0] = pID;
		p.processList[i][1] = priority;
		p.processList[i][2] = burstTime;
	} 
	
	for (int i = 0; i < p.noOfProcess; i++) {
        int min = i;
        for (int j = i + 1; j < p.noOfProcess; j++) {
            if (p.processList[j][1] > p.processList[min][1]) {
                min = j; 
            }
        }
        int tempID = p.processList[i][0];
        int tempPriority = p.processList[i][1];
        int tempBurstTime = p.processList[i][2];
        p.processList[i][0] = p.processList[min][0];
        p.processList[i][1] = p.processList[min][1];
        p.processList[i][2] = p.processList[min][2];
        p.processList[min][0] = tempID;
        p.processList[min][1] = tempPriority;
        p.processList[min][2] = tempBurstTime;
    }
}


void print(process p){
      for (int i = 0; i < p.noOfProcess; ++i) {
        cout << "\nProcess ID: " << p.processList[i][0]
          << " Burst Time: " << p.processList[i][2]
          << " Priority: "<<p.processList[i][1]
          << " Waiting Time: " << p.waitingTime[i]
          << " turn around time: "<< p.turnAroundTime[i]
          << " completion time: "<< p.completionTime[i];
      }
}


void waitingTime(process p){
	p.waitingTime[0] = 0; 
	for (int i = 1; i < p.noOfProcess; i++ ) {
		p.waitingTime[i] = p.processList[i-1][2] + p.waitingTime[i-1];
	}
}


void completionTime(process p){
    p.completionTime[0] = p.processList[0][2];
    for(int i = 1; i < p.noOfProcess; i++){
    	p.completionTime[i] = p.completionTime[i - 1] + p.processList[i][2];
    }
}
	

void turnAroundTime(struct process p) { 
	for (int i = 0; i < p.noOfProcess; i++) {
		p.turnAroundTime[i] = p.waitingTime[i] + p.processList[i][2];}
}


void avgWaitingAndTurnAroundTime(process p){
	int totalWaitingTime=0;
	int totalTurnAroundTime=0;
	
	for(int i = 0; i<p.noOfProcess; i++){
		totalWaitingTime += p.waitingTime[i];
		totalTurnAroundTime += p.turnAroundTime[i];
	}
	
	int avgWaiting = (float)totalWaitingTime/(float)p.noOfProcess; 
	int avgTurnAround = (float)totalTurnAroundTime / (float)p.noOfProcess; 
	cout << "\n\nAverage waiting time = "<< avgWaiting <<endl;
	cout<<"Average turn around time =  "<< avgTurnAround <<endl;
}
