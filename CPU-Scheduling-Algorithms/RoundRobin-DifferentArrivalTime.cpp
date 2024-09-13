#include <iostream>
using namespace std;

class ProcessScheduler {
private:
    int noOfProcess; 
    int** processList; 
    int* waitingTime; 
    int* completionTime; 
    int* turnAroundTime; 

    
    const int remainingBurstTimeCol = 2;
    const int burstTimeCol = 1;
    const int pIDCol = 0;
    const int arrivalTimeCol = 3;
    const int timeSlice = 2;

    
    void calculateWaitingTime() {
        int currentTime = 0;
        int arrivalTime = 0;
        while (true) {
            bool done = true;
            for (int i = 0; i < noOfProcess; i++) {
                if (processList[i][remainingBurstTimeCol] > 0) {
                    done = false;
                    if (processList[i][remainingBurstTimeCol] > timeSlice && processList[i][arrivalTimeCol] <= arrivalTime) {
                        currentTime += timeSlice;
                        processList[i][remainingBurstTimeCol] -= timeSlice;
                        arrivalTime++;
                    } else {
                        if (processList[i][arrivalTimeCol] <= arrivalTime) {
                            arrivalTime++;
                            currentTime += processList[i][remainingBurstTimeCol];
                            waitingTime[i] = currentTime - processList[i][burstTimeCol] - processList[i][arrivalTimeCol];
                            completionTime[i] = currentTime;
                            processList[i][remainingBurstTimeCol] = 0;
                        }
                    }
                }
            }
            if (done) {
                break;
            }
        }
    }

public:
    
    ProcessScheduler(int processCount) : noOfProcess(processCount) {
        processList = new int*[processCount];
        for (int i = 0; i < processCount; i++) {
            processList[i] = new int[4];
        }

        waitingTime = new int[processCount];
        turnAroundTime = new int[processCount];
        completionTime = new int[processCount];

        for (int i = 0; i < processCount; i++) {
            for (int j = 0; j < 4; j++) {
                processList[i][j] = 0;
            }
            waitingTime[i] = 0;
            turnAroundTime[i] = 0;
            completionTime[i] = 0;
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
            cout << "Enter Burst time for process-" << pID ;
            cin >> burstTime;
            cout << "Enter Arrival Time of process-" << pID ;
            cin >> arrivalTime;
            processList[i][pIDCol] = pID; 
            processList[i][burstTimeCol] = burstTime; 
            processList[i][remainingBurstTimeCol] = burstTime; 
            processList[i][arrivalTimeCol] = arrivalTime;
        }
    }

    
    void sortProcesses() {
        for (int i = 0; i < noOfProcess; i++) {
            int min = i;
            for (int j = i + 1; j < noOfProcess; j++) {
                if (processList[j][arrivalTimeCol] < processList[min][arrivalTimeCol] ||
                    (processList[j][arrivalTimeCol] == processList[min][arrivalTimeCol] &&
                     processList[j][burstTimeCol] < processList[min][burstTimeCol])) {
                    min = j;
                }
            }
            if (min != i) {
                swap(processList[i], processList[min]);
            }
        }
    }

    
    void calculateTurnAroundTime() {
        for (int i = 0; i < noOfProcess; i++) {
            turnAroundTime[i] = completionTime[i] - processList[i][arrivalTimeCol];
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

    
    void print() const {
        for (int i = 0; i < noOfProcess; ++i) {
            cout << "\nProcess ID: " << processList[i][pIDCol]
                 << " Burst Time: " << processList[i][burstTimeCol]
                 << " Waiting Time: " << waitingTime[i]
                 << " Turnaround Time: " << turnAroundTime[i]
                 << " Completion Time: " << completionTime[i];
        }
    }

    
    void run() {
        userPrompt(); 
        sortProcesses(); 
        calculateWaitingTime(); 
        calculateTurnAroundTime(); 
        print(); 
        calculateAndPrintAverages(); 
    }
};

int main() {
    cout << "Enter the total number of processes: ";
    int noOfProcess;
    cin >> noOfProcess;

    ProcessScheduler scheduler(noOfProcess); 

    scheduler.run(); 

    return 0;
}
