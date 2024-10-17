// Import Library
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Variable for Filename
#define FileName "PatientData"

// Declare for Function
struct PatientDataStruct {
    char Id[8], FirstName[30], LastName[30], fileName[30];
};

// Global Variable
struct PatientDataStruct PatientData;
int recordSize = 0;
FILE *fileData;

// General Function
void pressAnyKeyToContinute() {
    printf("\nPress any key to continue...");
    getch();

    return;
}

void clear() {
    //system("clear"); // Clear cmd for unix
    system("cls"); // Clear cmd for window
    //printf("\n\n\n\n\n\n\n\n\n\n");
    return;
}

// Actual Function
void patientRegitration() {
    struct PatientDataStruct NewPatientData;
    char action;

    printf("-=-=-=-=-=-=- Patient Regitration -=-=-=-=-=-=-\n");

    printf("Enter patient's ID: ");
    scanf("%s", &NewPatientData.Id);

    printf("Enter patient's firstname: ");
    scanf("%s", &NewPatientData.FirstName);

    printf("Enter patient's lastname: ");
    scanf("%s", &NewPatientData.LastName);

    patientRegitrationCheckDuplicatePatientId:

    // Check duplicate patient Id
    rewind(fileData);
    while (fread(&PatientData, recordSize, 1, fileData) == 1) {
        if(strcmp(NewPatientData.Id, PatientData.Id) == 0) {
            printf("\nPatient Id %s already exist.\n", NewPatientData.Id);
            printf("Do you want to replace exist patient data or change patient Id?\n");
            printf("Exit and do not save: 0\n");
            printf("Replace Exist Patient Data: 1\n");
            printf("Change Patient Id: 2\n");
            printf("What action do you want to make?: ");

            action = getch();

            printf("%c\n\n", action);

            if(action == '0') {
                printf("\n\nNoting change.");
                return pressAnyKeyToContinute();
            } else if(action == '1') {
                fseek(fileData, -recordSize, SEEK_CUR);
                fwrite(&NewPatientData, recordSize, 1, fileData);

                printf("\n\nReplace Patient Data Success.");
                return pressAnyKeyToContinute();
            } else if(action == '2') {
                printf("Enter NEW patient's ID: ");
                scanf("%s", &NewPatientData.Id);

                goto patientRegitrationCheckDuplicatePatientId;
            } else {
                printf("Wrong Action!");
                goto patientRegitrationCheckDuplicatePatientId;
            }

            break;
        }
    }

    rewind(fileData);
    fseek(fileData, 0, SEEK_END);
    fwrite(&NewPatientData, recordSize, 1, fileData);

    printf("\n\nSave Patient Data Success.");
    return pressAnyKeyToContinute();
}