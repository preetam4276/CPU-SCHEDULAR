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

    
    void userPrompt() {
        int burstTime;
        int arrivalTime;
        int pID;
        cout << "Enter the common arrival time for all processes: ";
        cin >> arrivalTime;
        for (int i = 0; i < noOfProcess; ++i) {
            pID = i + 1;
            cout << "Enter Burst time for process-" << pID << ": ";
            cin >> burstTime;
            processList[i][pIDCol] = pID; 
            processList[i][burstTimeCol] = burstTime; 
            processList[i][arrivalTimeCol] = arrivalTime; 
        }
    }

    
    void sortingProcesses() {
        int temp, burst;
        
        for (int i = 0; i < noOfProcess; i++) {
            for (int j = i + 1; j < noOfProcess; j++) {
                if (processList[j][burstTimeCol] < processList[i][burstTimeCol]) {
                    
                    burst = processList[i][burstTimeCol];
                    processList[i][burstTimeCol] = processList[j][burstTimeCol];
                    processList[j][burstTimeCol] = burst;

                    
                    temp = processList[i][pIDCol];
                    processList[i][pIDCol] = processList[j][pIDCol];
                    processList[j][pIDCol] = temp;
                }
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

    void run() {
        userPrompt(); 
        sortingProcesses(); 
        calculateCompletionTime(); 
        calculateTurnAroundTime(); 
        calculateWaitingTime(); 
        print(); 
        avgWaitingAndTurnAroundTime(); 
    }
};

int main() {
    cout << "Enter the total number of processes: ";
    int noOfProcess;
    cin >> noOfProcess;

    ProcessScheduler scheduler(noOfProcess); 
    scheduler.run(); `

    return 0;
}
