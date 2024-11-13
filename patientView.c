#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

struct PatientDataStruct{
    char FirstName[30], LastName[30], id[6];
};
struct PatientDataStruct PatientData;

void patientView(char id[6]) {
    struct dirent *entry;
    DIR *dir = opendir("PatientFolder");
    if (dir != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            char* simplifyID = strtok(entry->d_name, "_");

            if (simplifyID != NULL && strcmp(simplifyID, id) == 0) {
                simplifyID = strtok(NULL, "_");
                strcpy(PatientData.FirstName, simplifyID);
                
            }
        }
    }
    
    char openingFile[100];
    sprintf(openingFile, "PatientFolder/%s_%s/record.txt", id, PatientData.FirstName);

    system("clear");

    FILE *file = fopen(openingFile, "r");
    char buffer[128];

    char readingID[30], readingFirstName[30], readingLastName[30];

    // rewind(file);

    while (fgets(buffer, 128, file)) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

        char* token = strtok(buffer, " ");

        if(strcmp(token, "PatientID:") == 0) {
            token = strtok(NULL, " ");
            strcpy(readingID, token);
        }
        if (strcmp(token, "PatientName:") == 0) {
            token = strtok(NULL, " ");
            strcpy(readingFirstName, token);
        }
        if (strcmp(token, "PatientLastName:") == 0) {
            token = strtok(NULL, " ");
            strcpy(readingLastName, token);
        }
        
    }

    printf("ID: %s\n", readingID);
    printf("Name: %s %s\n", readingFirstName, readingLastName);

    fclose(file);
    
    return;
}