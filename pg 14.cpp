#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

// Function to copy a file
void copy() {
    const char *sourcefile = "C:/Users/itssk/OneDrive/Desktop/sasi.txt";
    const char *destination_file = "C:/Users/itssk/OneDrive/Desktop/sk.txt";
    
    int source_fd = open(sourcefile, O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return;
    }

    int dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten == -1) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return;
        }
    }

    if (bytesRead == -1) {
        perror("Error reading from source file");
    }

    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
}

// Function to create a new file and write some content into it
void create() {
    const char *path = "C:/Users/itssk/OneDrive/Desktop/sasi.txt";
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        perror("Error creating file");
        return;
    }

    // You can write some initial content to the file if needed
    fprintf(fp, "This is the content of the newly created file.\n");
    
    fclose(fp);
    printf("File created successfully.\n");
}

// Function to delete a file
void delete() {
    const char *path = "C:/Users/itssk/OneDrive/Desktop/sasi.txt";
    if (remove(path) == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("Error deleting file");
    }
}

int main() {
    int n;
    printf("1. Create \t2. Copy \t3. Delete\nEnter your choice: ");
    scanf("%d", &n);

    switch (n) {
        case 1:
            create();  // Create a new file
            break;
        case 2:
            copy();  // Copy the file
            break;
        case 3:
            delete();  // Delete the file
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}

