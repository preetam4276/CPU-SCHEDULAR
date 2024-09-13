#include <iostream>
using namespace std;


int remainingBurstTimeCol = 2;
int burstTimeCol = 1;
int pIDCol = 0;

int timeSlice = 2;

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
	for(int i = 0; i < p.noOfProcess; ++i){
		pID= i + 1;
		cout<<"Enter Brust time for process-"<< pID <<": "; 
		cin >> burstTime;	
		p.processList[i][0] = pID;
		p.processList[i][1] = burstTime;
		p.processList[i][2]= burstTime;
	} 

}


void print(process p){
      for (int i = 0; i < p.noOfProcess; ++i) {
        cout << "\nProcess ID: " << p.processList[i][0]
          << " Burst Time: " << p.processList[i][burstTimeCol]
          << " Waiting Time: " << p.waitingTime[i]
          << " turn around time: "<< p.turnAroundTime[i]
          << " completion time: "<< p.completionTime[i];
      }
}


void waitingTime(process p){
	int t =0;
	while (1){ 
        bool done = true; 
        for (int i = 0 ; i < p.noOfProcess; i++){ 
            
            if (p.processList[i][2] > 0) { 
                done = false; 
  				if (p.processList[i][2] > timeSlice) { 
                    t += timeSlice; 
                    p.processList[i][2] -= timeSlice; 
                } 
  				
                else{ 
                    t = t + p.processList[i][2];
                    p.waitingTime[i] = t - p.processList[i][1]; 
                    p.processList[i][2] = 0; 
                } 
            } 
        } 
        
        if (done == true) 
          break; 
    }
}


void completionTime(process p){
    p.completionTime[0] = p.processList[0][2];
    for(int i = 1; i < p.noOfProcess; i++){
    	p.completionTime[i] = p.completionTime[i - 1] + p.processList[i][1];
    }
}
	

void turnAroundTime(process p) { 
	for (int i = 0; i < p.noOfProcess; i++) {
		p.turnAroundTime[i] = p.waitingTime[i] + p.processList[i][1];}
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
