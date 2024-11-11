#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// Function prototype declaration
void patientRegistraion();

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

        printf("Press '0' to quit\n");
        printf("What do you want to do?: ");

        option = getchar();
        
        if (option == '0') {
            return;
        } else if(option == '1') {
            patientRegistraion();
        }
    }
}