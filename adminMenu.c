#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void adminMenu() {
    struct PatientDataStruct{
        char id[6], FirstName[30], LastName[30];
    };

    struct PatientDataStruct PatientInfo;

    while(1) {
        system("cls");

        char option;

        printf("Welcome, admin\n");
        
        printf("1) Patient Regitration: \n");
        printf("2) Patient records update: \n");
        printf("3) Making patient appointment: \n");
        printf("What do you want to do?: ");

        option = getch();
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