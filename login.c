#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "login.h"
#include "adminMenu.h"
#include "patientView.h"

void login() {
    struct PatientDataStruct{
        char FirstName[30], LastName[30], id[6];
    };
    
    struct PatientDataStruct PatientData;
    while (1) {
        char option;
        retry:

        printf("Select login option\n");
        printf("1) 6-digit ID \n");
        // printf("2) First & Last name \n");
        printf("Press '0' to quit or any other key to exit.\n");

        option = getchar();
        struct dirent *entry;

        if(option == '1') {
            printf("Enter your 6-digit id: ");
            scanf("%s", PatientData.id);
            printf("ID: %s\n", PatientData.id);
            
            DIR *dir = opendir("PatientFolder");
            if (dir != NULL) {
                while ((entry = readdir(dir)) != NULL) {
                    char* simplifyID = strtok(entry->d_name, "_");

                    if (simplifyID != NULL && strcmp(simplifyID, PatientData.id) == 0) {
                    simplifyID = strtok(NULL, "_");
                        if (simplifyID != NULL && strcmp(simplifyID, "admin") == 0) {
                            char password[30];
                            printf("Enter the password: ");
                            scanf("%s", password);
                            if (strcmp(password, "admin") == 0) {
                                adminMenu();
                            } else {
                                system("clear");
                                printf("Invalid password\n");
                                login();
                            }
                            break;
                        } else {
                            patientView(PatientData.id);
                            char quit;
                            printf("Enter any thing to continue\n");
                            scanf(" %c", &quit);

                        }
                    }
                }
            }
        
        // } else if(option == '2') {
        //     printf("Enter your First name: ");
        //     scanf("%s", PatientData.FirstName);
        //     printf("Enter your Last name: ");
        //     scanf("%s", PatientData.LastName);
        //     printf("Name: %s, %s", PatientData.FirstName, PatientData.LastName);
            
        //     DIR *dir = opendir("PatientFolder");
        //     if (dir != NULL) {
        //         while ((entry = readdir(dir)) != NULL) {
        //             char* simplifyName = strtok(entry->d_name, "_");
        //             simplifyName = strtok(NULL, "_");

        //             if (simplifyName != NULL && strcmp(simplifyName, PatientData.FirstName) == 0) {

        //                 // To-do <-----------------------------
                        
        //             }
        //         }
        //     }
        } else if (option == '0') {
            printf("\nAre you sure you want to quit? (y/n): ");
            char quit;
            scanf(" %c", &quit);
            if (quit == 'y' || quit == 'Y') {
                return;
            } else {
                system("clear");
                goto retry;
            }
        } else {
            system("clear");
            printf("Invalid input\n");
            goto retry;
        }
        system("clear");
        printf("No ID found\n");
        goto retry;
    }
    return;
}
