#include <iostream>
using namespace std;

class ProcessScheduler {
private:
    int noOfProcess;
    int** processList;
    int* waitingTime;
    int* completionTime;
    int* turnAroundTime;

    void sortProcesses() {
        for (int i = 0; i < noOfProcess; i++) {
            int min = i;
            for (int j = i + 1; j < noOfProcess; j++) {
                if (processList[j][arrivalTimeCol] < processList[min][arrivalTimeCol] ||
                    (processList[j][arrivalTimeCol] == processList[min][arrivalTimeCol] &&
                     processList[j][priorityCol] < processList[min][priorityCol])) {
                    min = j;
                }
            }
            if (min != i) {
                swap(processList[i], processList[min]);
            }
        }
    }

public:
    static const int arrivalTimeCol = 3;
    static const int burstTimeCol = 2;
    static const int pIDCol = 0;
    static const int priorityCol = 1;

    ProcessScheduler(int processCount) : noOfProcess(processCount) {
        processList = new int*[processCount];
        for (int i = 0; i < processCount; i++)
            processList[i] = new int[4];

        waitingTime = new int[processCount];
        turnAroundTime = new int[processCount];
        completionTime = new int[processCount];

        for (int i = 0; i < processCount; i++) {
            for (int j = 0; j < 4; j++) {
                processList[i][j] = 0;
            }
        }
    }

    ~ProcessScheduler() {
        for (int i = 0; i < noOfProcess; ++i) {
            delete[] processList[i];
        }
        delete[] processList;
        delete[] waitingTime;
        delete[] turnAroundTime;
        delete[] completionTime;
    }

    void userPrompt() {
        int burstTime, priority, arrivalTime;
        for (int i = 0; i < noOfProcess; ++i) {
            int pID = i + 1;
            cout << "Enter Burst time for process " << pID << ": ";
            cin >> burstTime;
            cout << "Enter the priority for process " << pID << ": ";
            cin >> priority;
            cout << "Enter the arrival time for process " << pID << ": ";
            cin >> arrivalTime;
            processList[i][pIDCol] = pID;
            processList[i][priorityCol] = priority;
            processList[i][burstTimeCol] = burstTime;
            processList[i][arrivalTimeCol] = arrivalTime;
        }
        sortProcesses();
    }

    void calculateCompletionTime() {
        completionTime[0] = processList[0][burstTimeCol];
        for (int i = 1; i < noOfProcess; i++) {
            completionTime[i] = completionTime[i - 1] + processList[i][burstTimeCol];
        }
    }

    void calculateTurnAroundTime() {
        for (int i = 0; i < noOfProcess; i++) {
            turnAroundTime[i] = completionTime[i] - processList[i][arrivalTimeCol];
        }
    }

    void calculateWaitingTime() {
        waitingTime[0] = 0;
        for (int i = 1; i < noOfProcess; i++) {
            waitingTime[i] = turnAroundTime[i] - processList[i][burstTimeCol];
        }
    }

    void print() const {
        for (int i = 0; i < noOfProcess; ++i) {
            cout << "\nProcess ID: " << processList[i][pIDCol]
                 << " Burst Time: " << processList[i][burstTimeCol]
                 << " Priority: " << processList[i][priorityCol]
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
    scheduler.calculateTurnAroundTime();
    scheduler.calculateWaitingTime();
    scheduler.print();
    scheduler.calculateAndPrintAverages();

    return 0;
}
