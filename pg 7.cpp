#include <stdio.h>

int main() {
    int at[10], bt[10], pr[10];  // Arrival Time, Burst Time, Priority
    int n, i, j, temp, time = 0, count = 0, over = 0;
    int sum_wait = 0, sum_turnaround = 0, start;
    float avgwait, avgturn;

    // Input the number of processes
    printf("Enter the number of processes\n");
    scanf("%d", &n);

    // Input Arrival Time, Burst Time, and Priority for each process
    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time, and Priority for process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &pr[i]);
    }

    // Sort processes based on priority (ascending order of priority)
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(pr[i] > pr[j]) {
                // Swap arrival times
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                // Swap priorities
                temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;
            }
        }
    }

    printf("\n\nProcess\t|Arrival Time\t|Burst Time\t|Priority\t|Start Time\t|End Time\t|Waiting Time\t|Turnaround Time\n");
    
    // Execute each process in the order of priority
    while(over < n) {
        start = time;
        time += bt[over];  // Update the current time after executing the process

        // Print process details
        printf("P[%d]\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\n", 
               over + 1, at[over], bt[over], pr[over], start, time, time - at[over] - bt[over], time - at[over]);

        // Calculate waiting time and turnaround time
        sum_wait += time - at[over] - bt[over];
        sum_turnaround += time - at[over];

        over++;
    }

    // Calculate and display average waiting time and turnaround time
    avgwait = (float)sum_wait / (float)n;
    avgturn = (float)sum_turnaround / (float)n;

    printf("\nAverage Waiting Time: %f\n", avgwait);
    printf("Average Turnaround Time: %f\n", avgturn);

    return 0;
}

