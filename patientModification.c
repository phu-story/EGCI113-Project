#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

char* directoryRead(char id[6]);
void modifiedFile(char*, char*, char*);


void patientModification() {

    struct PatientDataStruct{
            char FirstName[30], LastName[30];
            char id[6];
    };
    struct PatientDataStruct PatientData;
    struct dirent *entry;

    while (1) {
        retry:

        printf("Patient data modification\n");

        struct dirent *entry;
        char* recordsDir;

        printf("Enter 6-digit id(Press '0' to exit): ");
        scanf("%s", PatientData.id);
        printf("ID: %s\n", PatientData.id);
        if (PatientData.id == "0") {
            adminMenu();
        }
        

        recordsDir = directoryRead(PatientData.id);
        
        if (recordsDir == NULL) {
            printf("ID not found\n");
            goto retry;
        } else if(recordsDir != NULL) {
            char newFirstName[30], newLastName[30];
            int selectingField;

            FILE *file = fopen(recordsDir, "r");
            char buffer[128];

            // rewind(file);

            while (fgets(buffer, 128, file)) {
                buffer[strcspn(buffer, "\n")] = 0;

                char* token = strtok(buffer, " ");

                if(strcmp(token, "PatientID:") == 0) {
                    token = strtok(NULL, " ");
                    if (token != NULL) {
                        strcpy(PatientData.id, token);
                    }
                }
                if (strcmp(token, "PatientName:") == 0) {
                    token = strtok(NULL, " ");
                    if (token != NULL) {
                        strcpy(PatientData.FirstName, token);
                    }
                }
                if (strcmp(token, "PatientLastName:") == 0) {
                    token = strtok(NULL, " ");
                    if (token != NULL) {
                        strcpy(PatientData.LastName, token);
                    }
                }
                
            }

            system("clear");
            printf("Patient Found\n");
            printf("Patient ID: %s\n", PatientData.id);
            printf("Current Patient Name: %s %s\n\n", PatientData.FirstName, PatientData.LastName);
            printf("What do you want to modify?\n");
            printf("1) First Name\n");
            printf("2) Last Name\n");
            printf("3) Both\n");
            printf("Press '0' to quit or any other key to exit.\n");
            scanf("%d", &selectingField);

            if (selectingField == 1) {
                printf("Enter new first name: ");
                scanf("%s", newFirstName);
                modifiedFile(PatientData.id, newFirstName, PatientData.LastName);
                // system("clear");
                printf("Patient data modified\n");
                printf("New Name: %s %s\n\n", newFirstName, PatientData.LastName);
            } else if (selectingField == 2) {
                printf("Enter new last name: ");
                scanf("%s", newLastName);
                modifiedFile(PatientData.id, PatientData.FirstName, newLastName);
                system("clear");
                printf("Patient data modified\n");
                printf("New Name: %s %s\n\n", PatientData.FirstName, newLastName);
            } else if (selectingField == 3) {
                printf("Enter new first name: ");
                scanf("%s", newFirstName);
                printf("Enter new last name: ");
                scanf("%s", newLastName);
                modifiedFile(PatientData.id, newFirstName, newLastName);
                system("clear");
                printf("Patient data modified\n");
                printf("New Name: %s %s\n\n", newFirstName, newLastName);
            } else {
                system("clear");
                printf("Invalid input\n");
                goto retry;
            }
            goto retry;
            
        }

    } 
        
        
        
}

char* directoryRead(char* id) {
    struct PatientDataStruct{
        char FirstName[30], LastName[30];
        char id[6];
    };

    struct PatientDataStruct PatientData;

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
    
    char* openingFile = malloc(100 * sizeof(char));
    if (openingFile == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    sprintf(openingFile, "PatientFolder/%s_%s/record.txt", id, PatientData.FirstName);

    return openingFile;

    FILE *file = fopen(openingFile, "r");
    char buffer[128];

    char readingID[30], readingFirstName[30], readingLastName[30];

    // rewind(file);

    while (fgets(buffer, 128, file)) {
        buffer[strcspn(buffer, "\n")] = 0;

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

    fclose(file);
}

void modifiedFile(char* id, char* newName, char* newLastName) {
    struct dirent *entry;

    char oldPath[128];
    char newPath[128];
    char* oldFile = directoryRead(id);
    sprintf(newPath, "PatientFolder/%s_%s", id, newName);
    strncpy(oldPath, oldFile, sizeof(oldPath) - 1);
    oldPath[sizeof(oldPath) - 1] = '\0';
    
    char *pos = strstr(oldPath, "/record.txt");
    if (pos != NULL) {
        *pos = '\0';
    }
    
    if (rename(oldPath, newPath) == 0) {
        printf("Folder renamed successfully\n");
    } else {
        printf("Error renaming the folder\n");
        return;
    }

    char* creatingFile = directoryRead(id);
    FILE *file = fopen(creatingFile, "w");
    if (file != NULL) {
        fprintf(file, "PatientID: %s\n", id);
        fprintf(file, "PatientName: %s\n", newName);
        fprintf(file, "PatientLastName: %s\n", newLastName);
        fclose(file);
    } else {
        printf("Error: File not created\n");
    }
}