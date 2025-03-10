#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

int main() {
    FILE *filePtr;
    struct Employee emp;

    // Open the file in read/write binary mode, or create it if it doesn't exist
    filePtr = fopen("employee.dat", "rb+");
    if (filePtr == NULL) {
        filePtr = fopen("employee.dat", "wb+");
        if (filePtr == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
    }

    int choice;
    do {
        // Print the menu
        printf("\nEmployee Database Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add employee
                printf("Enter Employee ID: ");
                scanf("%d", &emp.empId);
                printf("Enter Employee Name: ");
                scanf("%49s", emp.empName);  // Limit input size to prevent overflow
                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);

                // Seek to the correct position based on empId and write the employee data
                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                printf("Employee details added successfully.\n");
                break;

            case 2:
                // Display employee details
                printf("Enter Employee ID to display: ");
                scanf("%d", &emp.empId);
                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                fread(&emp, sizeof(struct Employee), 1, filePtr);

                // Check if the employee exists
                if (emp.empId != 0) {
                    printf("Employee ID: %d\n", emp.empId);
                    printf("Employee Name: %s\n", emp.empName);
                    printf("Employee Salary: %.2f\n", emp.empSalary);
                } else {
                    printf("Employee not found.\n");
                }
                break;

            case 3:
                // Update employee details
                printf("Enter Employee ID to update: ");
                scanf("%d", &emp.empId);
                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                fread(&emp, sizeof(struct Employee), 1, filePtr);

                // Check if employee exists before updating
                if (emp.empId != 0) {
                    printf("Enter Employee Name: ");
                    scanf("%49s", emp.empName);  // Limit input size to prevent overflow
                    printf("Enter Employee Salary: ");
                    scanf("%f", &emp.empSalary);

                    // Write updated data back to the file
                    fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                    fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                    printf("Employee details updated successfully.\n");
                } else {
                    printf("Employee not found.\n");
                }
                break;

            case 4:
                // Exit the program
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    // Close the file after finishing all operations
    fclose(filePtr);

    return 0;
}

