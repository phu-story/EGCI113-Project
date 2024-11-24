#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void patientRegistraion() {
    struct PatientDataStruct{
        char FirstName[30], LastName[30], dobDate[3], dobMonth[3], dobYear[5];
        char id[6];
    };

    struct PatientDataStruct PatientInfo;
    struct dirent *entry;

    retry:

    printf("Enter patient ID(Enter 0 to exit): ");
    scanf("%6s", PatientInfo.id);

    DIR *dir = opendir("PatientFolder");
        if (dir != NULL) {
            while ((entry = readdir(dir)) != NULL) {
                char* simplifyName = strtok(entry->d_name, "_");

                if (simplifyName != NULL && strcmp(simplifyName, PatientInfo.id) == 0) {
                    system("clear");
                    printf("Error: ID already existed\n");
                    goto retry;
                }
            }
        }
    
    if (strcmp(PatientInfo.id, "0") == 0) {
        adminMenu();
    }

    printf("Enter patient First name: ");
    scanf("%s", PatientInfo.FirstName);

    printf("Enter patient Last name: ");
    scanf("%s", PatientInfo.LastName);

    printf("Enter patient Date of Birth (DD MM YYYY): ");
    scanf("%s %s %s", PatientInfo.dobDate, PatientInfo.dobMonth, PatientInfo.dobYear);

    if (strlen(PatientInfo.id) != 6) {
        printf("Press any key to continue\n");
        system("clear");
        printf("Error: ID must be 6 digits\n");
        goto retry;
    } else if(strlen(PatientInfo.FirstName) == 0 || strlen(PatientInfo.LastName) == 0) {
        system("clear");
        printf("Error: Name cannot be empty\n");
        goto retry;
    }


    char creatingFolder[100];
    sprintf(creatingFolder, "PatientFolder/%s_%s", PatientInfo.id, PatientInfo.FirstName);

    if (mkdir(creatingFolder, 0777) == 0) {
        char creatingFile[100];
        sprintf(creatingFile, "PatientFolder/%s_%s/record.txt", PatientInfo.id, PatientInfo.FirstName);

        printf("Registration: Folder created\n");
        FILE *file = fopen(creatingFile, "w");
        if (file != NULL) {
            fprintf(file, "PatientID: %s\n", PatientInfo.id);
            fprintf(file, "PatientName: %s\n", PatientInfo.FirstName);
            fprintf(file, "PatientLastName: %s\n", PatientInfo.LastName);
            fprintf(file, "PatientDOB: %s %s %s\n", PatientInfo.dobDate, PatientInfo.dobMonth, PatientInfo.dobYear);
            fclose(file);
        } else {
            printf("Error: File not created\n");
        }
    } else {
        printf("Error: Folder not created\n");
    }
}