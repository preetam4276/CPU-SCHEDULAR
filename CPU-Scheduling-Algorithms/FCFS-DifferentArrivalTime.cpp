#include <iostream>
using namespace std;

class process
{
private:
    int noOfProcess;
    int *processList;
    int *burstTime;
    int *arrivalTime;
    int *waitingTime;
    int *completionTime;
    int *turnAroundTime;

public:
    process(int processCount)
    {
        noOfProcess = processCount;
        processList = new int[processCount];
        burstTime = new int[processCount];
        arrivalTime = new int[processCount];
        waitingTime = new int[processCount];
        turnAroundTime = new int[processCount];
        completionTime = new int[processCount];
    }

    void userPrompt()
    {
        for (int i = 0; i < noOfProcess; ++i)
        {
            processList[i] = i + 1;
            cout << "Enter Burst time for process " << i + 1 << " : ";
            cin >> burstTime[i];
            cout << "Enter Arrival time for process " << i + 1 << " : ";
            cin >> arrivalTime[i];
        }
    }

    void print()
    {
        for (int i = 0; i < noOfProcess; ++i)
        {
            cout << "\nProcess ID: " << processList[i]
                 << " Burst Time: " << burstTime[i]
                 << " Waiting Time: " << waitingTime[i]
                 << " Turnaround Time: " << turnAroundTime[i]
                 << " Completion Time: " << completionTime[i];
        }
        cout << endl;
    }

    void calculateWaitingTime()
    {
        waitingTime[0] = 0; // First process doesn't wait
        for (int i = 1; i < noOfProcess; i++)
        {
            waitingTime[i] = completionTime[i - 1] - arrivalTime[i];
        }
    }

    void calculateCompletionTime()
    {
        completionTime[0] = burstTime[0];
        for (int i = 1; i < noOfProcess; i++)
        {
            completionTime[i] = completionTime[i - 1] + burstTime[i];
        }
    }

    void calculateTurnAroundTime()
    {
        for (int i = 0; i < noOfProcess; i++)
        {
            turnAroundTime[i] = completionTime[i] - arrivalTime[i];
        }
    }

    void calculateAvgWaitingAndTurnAroundTime()
    {
        int totalWaitingTime = 0;
        int totalTurnAroundTime = 0;

        for (int i = 0; i < noOfProcess; i++)
        {
            totalWaitingTime += waitingTime[i];
            totalTurnAroundTime += turnAroundTime[i];
        }

        float avgWaiting = (float)totalWaitingTime / (float)noOfProcess;
        float avgTurnAround = (float)totalTurnAroundTime / (float)noOfProcess;
        cout << "\n\nAverage waiting time = " << avgWaiting << endl;
        cout << "Average turnaround time =  " << avgTurnAround << endl;
    }
};

int main()
{
    cout << "Enter the total number of processes: ";
    int noOfProcess;
    cin >> noOfProcess;
    process p(noOfProcess);

    p.userPrompt();
    p.calculateCompletionTime();
    p.calculateTurnAroundTime();
    p.calculateWaitingTime();
    p.print();
    p.calculateAvgWaitingAndTurnAroundTime();

    return 0;
}
