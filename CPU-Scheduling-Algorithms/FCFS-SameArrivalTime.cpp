#include <iostream>
using namespace std;

class ProcessScheduler {
private:
    int noOfProcess; 
    int* processList; 
    int* burstTime; 
    int* waitingTime; 
    int* completionTime; 
    int* turnAroundTime; 

public:
    
    ProcessScheduler(int processCount) {
        noOfProcess = processCount;
        
        
        processList = new int[noOfProcess];
        burstTime = new int[noOfProcess];
        waitingTime = new int[noOfProcess];
        turnAroundTime = new int[noOfProcess];
        completionTime = new int[noOfProcess];
    }

    
    ~ProcessScheduler() {
        delete[] processList;
        delete[] burstTime;
        delete[] waitingTime;
        delete[] turnAroundTime;
        delete[] completionTime;
    }

    
    void userPrompt() {
        int burstTimeInput;
        for (int i = 0; i < noOfProcess; ++i) {
            processList[i] = i + 1;
            cout << "Enter Burst time for process " << i + 1 << ": ";
            cin >> burstTimeInput;
            burstTime[i] = burstTimeInput;
        }
    }

    
    void calculateCompletionTime() {
        completionTime[0] = burstTime[0];
        for (int i = 1; i < noOfProcess; i++) {
            completionTime[i] = completionTime[i - 1] + burstTime[i];
        }
    }

    
    void calculateWaitingTime() {
        waitingTime[0] = 0;
        for (int i = 1; i < noOfProcess; i++) {
            waitingTime[i] = burstTime[i - 1] + waitingTime[i - 1];
        }
    }

    
    void calculateTurnAroundTime() {
        for (int i = 0; i < noOfProcess; i++) {
            turnAroundTime[i] = waitingTime[i] + burstTime[i];
        }
    }

    
    void print() const {
        for (int i = 0; i < noOfProcess; ++i) {
            cout << "\nProcess ID: " << processList[i]
                 << " Burst Time: " << burstTime[i]
                 << " Waiting Time: " << waitingTime[i]
                 << " Turnaround Time: " << turnAroundTime[i]
                 << " Completion Time: " << completionTime[i];
        }
    }

    
    void calculateAndPrintAverages() const {
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
    scheduler.calculateCompletionTime(); 
    scheduler.calculateWaitingTime(); 
    scheduler.calculateTurnAroundTime(); 
    scheduler.print(); 
    scheduler.calculateAndPrintAverages(); 

    return 0;
}
