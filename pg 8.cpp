#include <stdio.h>

int main() {
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;

    // Input total number of processes
    printf("Total number of processes in the system: ");
    scanf("%d", &NOP);

    // Input the arrival time and burst time of each process
    for(i = 0; i < NOP; i++) {
        printf("Enter Arrival Time and Burst Time for Process P%d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        temp[i] = bt[i];  // Store burst time in temp array for modification
    }

    // Input the time quantum for Round Robin Scheduling
    printf("Enter Time Quantum: ");
    scanf("%d", &quant);

    y = NOP; // Number of remaining processes
    printf("\nProcess No\tBurst Time\tWaiting Time\tTurnaround Time\n");

    // Round Robin Scheduling
    while(y > 0) {
        for(i = 0; i < NOP; i++) {
            if(temp[i] > 0) {
                if(temp[i] > quant) {
                    sum += quant;
                    temp[i] -= quant;
                } else {
                    sum += temp[i];
                    temp[i] = 0;
                    y--;  // Process finished
                    // Calculate waiting time and turnaround time
                    printf("P%d\t\t%d\t\t%d\t\t%d\n", i+1, bt[i], sum - at[i] - bt[i], sum - at[i]);
                    wt += sum - at[i] - bt[i];  // Waiting time calculation
                    tat += sum - at[i];         // Turnaround time calculation
                }
            }
        }
    }

    // Calculate average waiting time and turnaround time
    avg_wt = (float)wt / NOP;
    avg_tat = (float)tat / NOP;

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f", avg_tat);

    return 0;
}

