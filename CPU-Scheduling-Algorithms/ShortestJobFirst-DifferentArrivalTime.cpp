#include <iostream>
using namespace std;

class ProcessScheduler {
private:
    int noOfProcess;
    int** processList;  
    int* waitingTime;   
    int* completionTime; 
    int* turnAroundTime; 

    int burstTimeCol = 1;
    int pIDCol = 0;
    int arrivalTimeCol = 2;

public:
ProcessScheduler(int processCount) {
    noOfProcess = processCount;
    processList = new int*[processCount];
    for (int i = 0; i < processCount; i++)
        processList[i] = new int[3]; 

    waitingTime = new int[processCount];
    turnAroundTime = new int[processCount];
    completionTime = new int[processCount];

    
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < 3; j++) {
            processList[i][j] = 0;
        }
    }
}


~ProcessScheduler() {
    for (int i = 0; i < noOfProcess; i++) {
        delete[] processList[i];
    }
    delete[] processList;
    delete[] waitingTime;
    delete[] turnAroundTime;
    delete[] completionTime;
}


void userPrompt() {
    int burstTime;
    int arrivalTime;
    int pID;
    for (int i = 0; i < noOfProcess; ++i) {
        pID = i + 1;
        cout << "Enter Burst time for process-" << pID << ": ";
        cin >> burstTime;
        cout << "Enter Arrival Time of process-" << pID << ": ";
        cin >> arrivalTime;
        processList[i][pIDCol] = pID; 
        processList[i][burstTimeCol] = burstTime; 
        processList[i][arrivalTimeCol] = arrivalTime;
    }
}


void sortingProcesses() {
    int temp, burst, arri;
    for (int i = 0; i < noOfProcess; i++) {
        for (int j = i + 1; j < noOfProcess; j++) {
            if (processList[j][arrivalTimeCol] < processList[i][arrivalTimeCol]) {
                
                arri = processList[i][arrivalTimeCol];
                processList[i][arrivalTimeCol] = processList[j][arrivalTimeCol];
                processList[j][arrivalTimeCol] = arri;

                
                temp = processList[i][pIDCol];
                processList[i][pIDCol] = processList[j][pIDCol];
                processList[j][pIDCol] = temp;

                
                burst = processList[i][burstTimeCol];
                processList[i][burstTimeCol] = processList[j][burstTimeCol];
                processList[j][burstTimeCol] = burst;
            }
        }
    }

    
    for (int i = 0; i < noOfProcess - 1; i++) {
        if (processList[i][arrivalTimeCol] == processList[i + 1][arrivalTimeCol] &&
            processList[i][burstTimeCol] > processList[i + 1][burstTimeCol]) {

            
            burst = processList[i][burstTimeCol];
            processList[i][burstTimeCol] = processList[i + 1][burstTimeCol];
            processList[i + 1][burstTimeCol] = burst;

            
            temp = processList[i][pIDCol];
            processList[i][pIDCol] = processList[i + 1][pIDCol];
            processList[i + 1][pIDCol] = temp;

            
            arri = processList[i][arrivalTimeCol];
            processList[i][arrivalTimeCol] = processList[i + 1][arrivalTimeCol];
            processList[i + 1][arrivalTimeCol] = arri;
        }
    }
}


void calculateCompletionTime() {
    completionTime[0] = processList[0][burstTimeCol];
    for (int i = 1; i < noOfProcess; i++) {
        completionTime[i] = processList[i][burstTimeCol] + completionTime[i - 1];
    }
}


void calculateTurnAroundTime() {
    for (int i = 0; i < noOfProcess; i++) {
        turnAroundTime[i] = completionTime[i] - processList[i][arrivalTimeCol];
    }
}


void calculateWaitingTime() {
    for (int i = 0; i < noOfProcess; i++) {
        int time = turnAroundTime[i] - processList[i][burstTimeCol];
        waitingTime[i] = (time >= 0) ? time : 0;
    }
}


void print() {
    for (int i = 0; i < noOfProcess; ++i) {
        cout << "\nProcess ID: " << processList[i][pIDCol]
             << " Burst Time: " << processList[i][burstTimeCol]
             << " Waiting Time: " << waitingTime[i]
             << " Turnaround Time: " << turnAroundTime[i]
             << " Completion Time: " << completionTime[i];
    }
}


void avgWaitingAndTurnAroundTime() {
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    for (int i = 0; i < noOfProcess; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }

    float avgWaiting = static_cast<float>(totalWaitingTime) / noOfProcess;
    float avgTurnAround = static_cast<float>(totalTurnAroundTime) / noOfProcess;
    cout << "\n\nAverage waiting time = " << avgWaiting << endl;
    cout << "Average turnaround time = " << avgTurnAround << endl;
}
};



int main() {
    
    cout << "Enter the total number of processes: ";
    int noOfProcess;
    cin >> noOfProcess;

    ProcessScheduler scheduler(noOfProcess); 

    scheduler.userPrompt(); 
    scheduler.sortingProcesses(); 
    scheduler.calculateCompletionTime(); 
    scheduler.calculateTurnAroundTime(); 
    scheduler.calculateWaitingTime(); 
    scheduler.print(); 
    scheduler.avgWaitingAndTurnAroundTime(); 

    return 0;
}
