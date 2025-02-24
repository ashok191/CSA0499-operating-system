#include <stdio.h>

void bestfit(int mp[], int p[], int m, int n) {
    int j = 0;  // Pointer for process
    for (int i = 0; i < n; i++) {
        if (mp[i] >= p[j]) {  // Check if the partition can accommodate the process
            printf("\nProcess %d fits in partition %d\n", p[j], mp[i]);
            mp[i] = mp[i] - p[j];  
            j++;  
            if (j >= m) break; 
        }
    }
    if (j < m) {  
        printf("\nProcess %d must wait for a suitable partition\n", p[j]);
    }
}

void rsort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] < a[j]) {  
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {  
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void firstfit(int mp[], int p[], int m, int n) {
    sort(mp, n);  
    sort(p, m);   
    bestfit(mp, p, m, n);  
}

void worstfit(int mp[], int p[], int m, int n) {
    rsort(mp, n);  
    sort(p, m);    
    bestfit(mp, p, m, n);  
}

int main() {
    int m, n, mp[20], p[20], ch;
    
    printf("Number of memory partitions: ");
    scanf("%d", &n);
    
    printf("Number of processes: ");
    scanf("%d", &m);
    
    printf("Enter the memory partitions:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &mp[i]);
    }
    
    printf("Enter process sizes:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &p[i]);
    }
    
    printf("1. Firstfit\t2. Bestfit\t3. Worstfit\nEnter your choice: ");
    scanf("%d", &ch);
    
    switch(ch) {
        case 1:
            firstfit(mp, p, m, n);
            break;
        case 2:
            bestfit(mp, p, m, n);
            break;
        case 3:
            worstfit(mp, p, m, n);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
    
    return 0;
}

