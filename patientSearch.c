// Import Library
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define FileName "PatientData"

// Global Variable
struct PatientDataStruct PatientData;
FILE *fileData;

void patientSearch() {
    char queryId[8];
    int isFound = 0;
    printf("-=-=-=-=-=-=- Patient Search -=-=-=-=-=-=-\n");

    printf("Enter patient's ID: ");
    scanf("%s", &queryId);

    rewind(fileData);
    while (fread(&PatientData, recordSize, 1, fileData) == 1) {
        if(strcmp(queryId, PatientData.Id) == 0) {
            printf("Id: %s\n", PatientData.Id);
            printf("FirstName: %s\n", PatientData.FirstName);
            printf("LastName: %s\n", PatientData.LastName);
            printf("\n");
            isFound = 1;
            break;
        }
    }

    if(!isFound) {
        printf("Patient Id %s not found.\n", queryId);
        printf("Press 1 to retry or 2 to return to main menu\n");
        char retryQ = getch();
        // printf("retryQ -> %c", retryQ);

        if (retryQ == '1'){
            clear();
            return patientSearch();
        } else if (retryQ == '2') {
            return pressAnyKeyToContinue();
        }
    }

    return pressAnyKeyToContinue();
}