#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void doctorRegistration() {

    struct DoctorDataStruct{
        char FirstName[30], LastName[30];
        char id[6];
    };

    struct DoctorDataStruct DoctorData;
    struct dirent *entry;

    system("clear");
    retry:

    printf("Enter doctor's name(Enter 0 to exit): ");
    scanf("%s", DoctorData.FirstName);

    if (strcmp(DoctorData.FirstName, "0") == 0) {
        adminMenu();
    }

    DIR *dir = opendir("DoctorFolder");
        if (dir != NULL) {
            while ((entry = readdir(dir)) != NULL) {
                char* simplifyNumber = strtok(entry->d_name, "_");


                if (simplifyNumber != NULL) {
                    int idNumber = atoi(simplifyNumber) + 1;
                    sprintf(DoctorData.id, "%d", idNumber);
                }
            }
        }

    printf("Enter doctor's Last name: ");
    scanf("%s", DoctorData.LastName);

    if(strlen(DoctorData.FirstName) == 0 || strlen(DoctorData.LastName) == 0) {
        system("clear");
        printf("Error: Name cannot be empty\n");
        goto retry;
    }


    char creatingFolder[100];
    sprintf(creatingFolder, "DoctorFolder/%s_%s", DoctorData.id, DoctorData.FirstName);

    if (mkdir(creatingFolder, 0777) == 0) {
        char creatingFile[100];
        sprintf(creatingFile, "PatientFolder/%s_%s/record.txt", DoctorData.id, DoctorData.FirstName);

        printf("Registration: Folder created\n");
        FILE *file = fopen(creatingFile, "w");
        if (file != NULL) {
            fprintf(file, "PatientID: %s\n", DoctorData.id);
            fprintf(file, "PatientName: %s\n", DoctorData.FirstName);
            fprintf(file, "PatientLastName: %s\n", DoctorData.LastName);
            fclose(file);
        } else {
            printf("Error: File not created\n");
        }
    } else {
        printf("Error: Folder not created\n");
    }
}