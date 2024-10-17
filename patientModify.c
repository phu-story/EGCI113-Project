// Import Library
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


// Import Function
#include "patientRegitration.c"

#define FileName "PatientData"

struct PatientDataStruct {
    char Id[8], FirstName[30], LastName[30], fileName[30];
};

// Global Function

void patientSearch();
void patientList();
void patientModify();

// General Function
void clear() {
    //system("clear"); // Clear cmd for unix
    system("cls"); // Clear cmd for window
    //printf("\n\n\n\n\n\n\n\n\n\n");
    return;
}

void pressAnyKeyToContinute() {
    printf("\nPress any key to continue...");
    getch();

    return;
}

// Global Variable
struct PatientDataStruct PatientData;
int recordSize = 0;
FILE *fileData;

void patientModify() {
    char queryId[8], fieldId;
    int isFound = 0;
    printf("-=-=-=-=-=-=- Patient Modify -=-=-=-=-=-=-\n");

    printf("Enter patient's ID: ");
    scanf("%s", &queryId);

    rewind(fileData);
    while (fread(&PatientData, recordSize, 1, fileData) == 1) {
        if(strcmp(queryId, PatientData.Id) == 0) {
            isFound = 1;
            break;
        }
    }

    if(!isFound) {
        printf("Patient Id %s not found.\n", queryId);
        return pressAnyKeyToContinute();
    }


    printf("Id: %s\n", PatientData.Id);
    printf("FirstName: %s\n", PatientData.FirstName);
    printf("LastName: %s\n", PatientData.LastName);
    printf("\n");

    while (1) {
        printf("Exit: 0\n");
        printf("FirstName: 1\n");
        printf("LastName: 2\n");
        printf("What field do you want to edit?: ");

        fieldId = getch();

        printf("%c\n\n", fieldId);

        if(fieldId == '0') {
            fseek(fileData, -recordSize, SEEK_CUR);
            fwrite(&PatientData, recordSize, 1, fileData);

            break;
        } else if(fieldId == '1') {
            printf("FirstName: ");
            scanf("%s", &PatientData.FirstName);
        } else if(fieldId == '2') {
            printf("LastName: ");
            scanf("%s", &PatientData.LastName);
        } else {
            printf("\nField Not Found.");
        }

        printf("\n\n");
    }

    return pressAnyKeyToContinute();
}