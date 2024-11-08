#include <stdio.h>
#include <stdlib.h>

void adminMenu() {
    struct PatientDataStruct{
        char FirstName[30], LastName[30];
        int id[6];
    };

    struct PatientDataStruct PatientInfo;

    while(1) {
        system("clear");

        char option;

        printf("Welcome, admin\n");
        
        printf("1) Patient Regitration: \n");
        printf("2) Patient records update: \n");
        printf("3) Making patient appointment: \n");
        printf("What do you want to do?: ");

        option = getchar();
        if(option = '1') {
            printf("Enter patient ID: ");
            scanf("%d", PatientInfo.id);

            printf("Enter patient First name: ");
            scanf("%s", PatientInfo.FirstName);

            printf("Enter patient Last name: ");
            scanf("%s", PatientInfo.LastName);
        }
    }
}