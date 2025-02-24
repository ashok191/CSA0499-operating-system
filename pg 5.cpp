#include <stdio.h>

struct priority_scheduling {
    char process_name;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int priority;
};

int main() {
    int number_of_process;
    int total = 0;
    struct priority_scheduling temp_process;
    int ASCII_number = 65;  // ASCII value of 'A'
    int position;
    float average_waiting_time;
    float average_turnaround_time;

    // Input number of processes
    printf("Enter the total number of Processes: ");
    scanf("%d", &number_of_process);

    struct priority_scheduling process[number_of_process];
    
    // Input Burst Time and Priority for each process
    printf("\nPlease Enter the Burst Time and Priority of each process:\n");
    for (int i = 0; i < number_of_process; i++) {
        process[i].process_name = (char)ASCII_number;
        printf("\nEnter details for process %c:\n", process[i].process_name);
        printf("Enter the burst time: ");
        scanf("%d", &process[i].burst_time);
        printf("Enter the priority: ");
        scanf("%d", &process[i].priority);
        ASCII_number++;
    }

    // Sort processes based on priority (higher priority first)
    for (int i = 0; i < number_of_process; i++) {
        position = i;
        for (int j = i + 1; j < number_of_process; j++) {
            if (process[j].priority > process[position].priority) {
                position = j;
            }
        }
        // Swap processes
        temp_process = process[i];
        process[i] = process[position];
        process[position] = temp_process;
    }

    // Calculate waiting time
    process[0].waiting_time = 0;  // First process has 0 waiting time
    for (int i = 1; i < number_of_process; i++) {
        process[i].waiting_time = 0;
        for (int j = 0; j < i; j++) {
            process[i].waiting_time += process[j].burst_time;
        }
        total += process[i].waiting_time;
    }

    // Calculate average waiting time
    average_waiting_time = (float)total / number_of_process;
    total = 0;

    // Print Process Table with Waiting and Turnaround Time
    printf("\n\nProcess Name\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < number_of_process; i++) {
        process[i].turn_around_time = process[i].burst_time + process[i].waiting_time;  // Turnaround time = Burst Time + Waiting Time
        total += process[i].turn_around_time;
        printf("%c\t\t%d\t\t%d\t\t%d\n", process[i].process_name, process[i].burst_time, process[i].waiting_time, process[i].turn_around_time);
    }

    // Calculate average turnaround time
    average_turnaround_time = (float)total / number_of_process;

    // Print average waiting and turnaround time
    printf("\nAverage Waiting Time: %f", average_waiting_time);
    printf("\nAverage Turnaround Time: %f\n", average_turnaround_time);

    return 0;
}

