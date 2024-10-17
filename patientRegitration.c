// Import Library
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Variable for Filename
#define FileName "PatientData"

// Global Variable
struct PatientDataStruct PatientData;
FILE *fileData;

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
                return pressAnyKeyToContinue();
            } else if(action == '1') {
                fseek(fileData, -recordSize, SEEK_CUR);
                fwrite(&NewPatientData, recordSize, 1, fileData);

                printf("\n\nReplace Patient Data Success.");
                return pressAnyKeyToContinue();
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
    return pressAnyKeyToContinue();
}