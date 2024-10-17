// Import Library
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define FileName "PatientData"

#include "generalFunction.c"

struct PatientDataStruct {
    char Id[8], FirstName[30], LastName[30], fileName[30];
};

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

    return pressAnyKeyToContinue();
}