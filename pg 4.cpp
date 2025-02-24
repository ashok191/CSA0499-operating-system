#include<stdio.h>

int main() {
    int bt[20], p[20], wt[20], tat[20], i, j, n, total = 0, pos, temp;
    float avg_wt, avg_tat;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst time
    printf("\nEnter Burst Time:\n");
    for(i = 0; i < n; i++) {
        printf("p%d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;  // Store process ID
    }

    // Sorting processes based on burst time (Shortest Job First)
    for(i = 0; i < n; i++) {
        pos = i;
        for(j = i + 1; j < n; j++) {
            if(bt[j] < bt[pos])  // Find the process with the shortest burst time
                pos = j;
        }
        
        // Swap burst time and process ID
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Waiting time for the first process is 0
    wt[0] = 0;
    for(i = 1; i < n; i++) {
        wt[i] = 0;
        for(j = 0; j < i; j++) {
            wt[i] += bt[j];  // Calculate waiting time
        }
        total += wt[i];  // Accumulate total waiting time
    }

    avg_wt = (float)total / n;  // Calculate average waiting time
    total = 0;

    // Print the process table
    printf("\nProcess  Burst Time  Waiting Time  Turnaround Time\n");
    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];  // Turnaround time = Burst time + Waiting time
        total += tat[i];  // Accumulate total turnaround time
        printf("P%d      %d          %d             %d\n", p[i], bt[i], wt[i], tat[i]);
    }

    avg_tat = (float)total / n;  // Calculate average turnaround time

    // Print average waiting and turnaround times
    printf("\nAverage Waiting Time = %f\n", avg_wt);
    printf("Average Turnaround Time = %f\n", avg_tat);

    return 0;
}

