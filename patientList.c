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

void patientList() {
    int recordCount = 0;

    printf("-=-=-=-=-=-=- Patient List -=-=-=-=-=-=-\n");

    rewind(fileData);
    while (fread(&PatientData, recordSize, 1, fileData) == 1) {
        recordCount++;
        printf("Id: %s\n", PatientData.Id);
        printf("FirstName: %s\n", PatientData.FirstName);
        printf("LastName: %s\n", PatientData.LastName);
        printf("\n");
    }

    if(recordCount == 0) {
        printf("No Patient Found.\n");
    } else {
        printf("\nTotal Patient: %d\n", recordCount);
    }

    return pressAnyKeyToContinute();
}