#include <stdio.h>

#include "authentication.c"

void login() {
    struct PatientDataStruct{
        char FirstName[30], LastName[30], id[6];
    };
    
    struct PatientDataStruct PatientData;
    while (1) {
        char option = 0;
        char argument[256];

        printf("Select login option\n");
        printf("1) 6-digit ID \n");
        printf("2) First & Last name \n");
        printf("Press '0' to quit or any other key to exit.\n");
        
        option = getch();
        if(option == '1') {
            printf("Enter your 6-digit id: ");
            scanf("%s", &PatientData.id);

            sprintf(argument, "id+%s", PatientData.id);
            authentication(argument);
        } else if(option == '2') {
            printf("Enter your First name: ");
            scanf("%s", &PatientData.FirstName);

            printf("Enter your Last name: ");
            scanf("%s", &PatientData.LastName);

            sprintf(argument, "name+%s+%s", PatientData.FirstName, PatientData.LastName);
            authentication(argument);
        } else {
            return;
        }
        break;
    }

    printf("ID = %d, First Name = %s, Last Name = %s", PatientData.id, PatientData.FirstName, PatientData.LastName);
    return;
}