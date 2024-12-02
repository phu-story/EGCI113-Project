#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "adminMenu.h"
#include "patientRegistration.h"
#include "patientModification.h"
#include "appointment.h"
#include "appointmentNote.h"
#include "doctorRegistration.h"

void adminMenu() {
    while (1) {
        system("clear");
        printf("Welcome, admin\n");
        printf("1) Patient Registration\n");
        printf("2) Patient Modification\n");
        printf("3) Make Appointment\n");
        printf("4) Doctor Registration\n");
        printf("5) Appointment Notes\n");
        printf("0) Logout\n");
        printf("Enter your choice: ");

        char choice;
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                patientRegistraion();
                break;
            case '2':
                patientModification();
                break;
            case '3':
                makeAppointment();
                break;
            case '4':
                doctorRegistration();
                break;
            case '5':
                appointmentNote();
                break;
            case '0':
                return;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
}
