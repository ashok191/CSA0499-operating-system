#include <stdio.h>

int main() {
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0;
    int at[10], bt[10], temp[10];
    float avg_wt, avg_tat;

    // Input number of processes and time quantum
    printf("Enter the total number of processes in the system: ");
    scanf("%d", &NOP);

    printf("Enter the time quantum: ");
    scanf("%d", &quant);

    y = NOP;

    // Input Arrival Time and Burst Time for each process
    for(i = 0; i < NOP; i++) {
        printf("\nEnter Arrival Time and Burst Time for Process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        temp[i] = bt[i];  // Store the burst time in a temp array
    }

    // Round Robin Scheduling
    printf("\nProcess No\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    while(y > 0) {
        for(i = 0; i < NOP; i++) {
            if(temp[i] > 0) {
                if(temp[i] > quant) {
                    sum += quant;
                    temp[i] -= quant;
                } else {
                    sum += temp[i];
                    wt += sum - at[i] - bt[i];
                    tat += sum - at[i];
                    printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], sum - at[i] - bt[i], sum - at[i]);
                    temp[i] = 0;
                    y--;
                }
            }
        }
    }

    avg_wt = (float)wt / NOP;
    avg_tat = (float)tat / NOP;

    printf("\nAverage Waiting Time: %f", avg_wt);
    printf("\nAverage Turnaround Time: %f", avg_tat);

    return 0;
}

