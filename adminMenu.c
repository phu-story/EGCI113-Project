#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void adminMenu() {
    struct PatientDataStruct{
        char FirstName[30], LastName[30];
        char id[6];
    };

    struct PatientDataStruct PatientInfo;
    struct dirent *entry;

    while(1) {
        system("clear");

        char option;

        printf("Welcome, admin\n");
        
        printf("1) Patient Regitration: \n");
        printf("2) Patient records update: \n");
        printf("3) Making patient appointment: \n");
        printf("What do you want to do?: ");

        option = getchar();
        // option = 1;
        if(option == '1') {
            retry:

            printf("Enter patient ID(Enter 0 to exit): ");
            scanf("%6s", PatientInfo.id);

            DIR *dir = opendir("PatientFolder");
                if (dir != NULL) {
                    while ((entry = readdir(dir)) != NULL) {
                        char* simplifyName = strtok(entry->d_name, "_");

                        if (simplifyName != NULL && strcmp(simplifyName, PatientInfo.id) == 0) {
                            printf("Error: ID already existed\n");
                            printf("Press any key to continue\n");
                            
                            goto retry;
                        }
                    }
                }

            printf("Enter patient First name: ");
            scanf("%s", PatientInfo.FirstName);

            printf("Enter patient Last name: ");
            scanf("%s", PatientInfo.LastName);

            if (strcmp(PatientInfo.id, "0") == 0) {
                break;
            } else if (strlen(PatientInfo.id) != 6) {
                printf("Error: ID must be 6 digits\n");
                printf("Press any key to continue\n");
                goto retry;
            } else if(strlen(PatientInfo.FirstName) == 0 || strlen(PatientInfo.LastName) == 0) {
                printf("Error: Name cannot be empty\n");
                printf("Press any key to continue\n");
                getchar();
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
                    fprintf(file, "PatientID:%s\n", PatientInfo.id);
                    fprintf(file, "PatientName: %s\n", PatientInfo.FirstName);
                    fprintf(file, "PatientLastName: %s\n", PatientInfo.LastName);
                    fclose(file);
                } else {
                    printf("Error: File not created\n");
                }
            } else {
                printf("Error: Folder not created\n");
            }
            
        }
    }
}