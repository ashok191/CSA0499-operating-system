#include <stdio.h>
#include <stdlib.h>

int main() {
    char mainDirectory[] = "C:/Users/itssk/OneDrive/Desktop";
    char subDirectory[] = "os";
    char fileName[] = "example.txt";
    char filePath[200];
    char mainDirPath[200];

    // Construct the main directory path
    snprintf(mainDirPath, sizeof(mainDirPath), "%s/%s/", mainDirectory, subDirectory);

    // Construct the full file path
    snprintf(filePath, sizeof(filePath), "%s%s", mainDirPath, fileName);

    // Create and open the file for writing
    FILE *file = fopen(filePath, "w");

    if (file == NULL) {
        printf("Error creating file.\n");
        return 1;
    }

    // Write content to the file
    fprintf(file, "This is an example file content.");

    // Print success message
    printf("File created successfully: %s\n", filePath);

    // Close the file after writing
    fclose(file);

    return 0;
}

