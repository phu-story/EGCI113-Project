#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// Function prototype declaration
void patientRegistraion();
void patientModification();
void makeAppointment();
void doctorRegistration();

void adminMenu() {
    struct PatientDataStruct{
        char FirstName[30], LastName[30];
        char id[6];
    };

    struct PatientDataStruct PatientInfo;
    struct dirent *entry;

    while(1) {
        system("clear");

        printf("Welcome, admin\n");
        
        char option;
        
        printf("Patient Management Section\n");
        printf("1) Patient Regitration: \n");
        printf("2) Patient records update: \n");
        printf("3) Making patient appointment: \n");

        printf("-----------------------------\n");

        // printf("Doctor Management Section\n");
        printf("4) Doctor Registration: \n");
        printf("5) Appointment note: \n");

        printf("Press '0' to quit\n");
        printf("What do you want to do?: ");

        option = getchar();
        
        if (option == '0') {
            system("clear");
            login();
        } else if(option == '1') {
            patientRegistraion();
        } else if(option == '2') {
            patientModification();
        } else if(option == '3') {
            makeAppointment();
        } else if (option == '4') {
            doctorRegistration();
        } else if (option == '5') {
            system("clear");
            printf("Appointment note\n");
        } else {
            system("clear");
            printf("Invalid input\n");
            adminMenu();
        } 
    }
}