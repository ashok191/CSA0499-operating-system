#include <stdio.h>

int main() {
    int A[100][4];  // Array to store process information
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;

    // Input number of processes
    printf("Enter number of process: ");
    scanf("%d", &n);

    // Input Burst Time
    printf("Enter Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]);
        A[i][0] = i + 1;  // Store process ID
    }

    // Sorting processes based on Burst Time (Shortest Job First)
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++)
            if (A[j][1] < A[index][1])  // Find the process with the shortest burst time
                index = j;
        
        // Swap Burst Time and Process ID to ensure they are in order
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;

        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }

    A[0][2] = 0;  // Waiting time for the first process is 0
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++)
            A[i][2] += A[j][1];  // Calculate waiting time for each process

        total += A[i][2];  // Accumulate total waiting time
    }

    avg_wt = (float)total / n;  // Calculate average waiting time
    total = 0;

    printf("P  BT WT TAT\n");
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2];  // Turnaround time = Burst Time + Waiting Time
        total += A[i][3];  // Accumulate total turnaround time

        // Print process ID, Burst Time, Waiting Time, and Turnaround Time
        printf("P%d  %d  %d  %d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }

    avg_tat = (float)total / n;  // Calculate average turnaround time

    // Print average waiting and turnaround time
    printf("Average Waiting Time= %f\n", avg_wt);
    printf("Average Turnaround Time= %f\n", avg_tat);

    return 0;
}

