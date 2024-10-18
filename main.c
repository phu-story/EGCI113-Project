// Import Library
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


// Import Function
#include "patientList.c"
#include "patientModify.c"
#include "patientRegitration.c"
#include "patientSearch.c"

#define FileName "PatientData"

// General Function
// void pressAnyKeyToContinute() {
//     printf("\nPress any key to continue...");
//     getch();

//     return;
// }

// Global Variable
struct PatientDataStruct PatientData;
FILE *fileData;

int main() {
    printf("Loading...");

    char menu = 0;

    // Check File
    fileData = fopen(FileName, "rb+");
    if(fileData == NULL) {
        fileData = fopen(FileName, "wb+");
        if(fileData == NULL) {
            printf("Can't open file.");
            return 0;
        }
    }

    // Set Struct Size
    recordSize = sizeof(PatientData);

    while (1) {
        clear();

        printf("Exit: 0\n");
        printf("Patient Regitration: 1\n");
        printf("Patient Search: 2\n");
        printf("Patient List: 3\n");
        printf("Patient Modify: 4\n");
        printf("What do you want to do?: ");

        menu = getch();

        clear();

        if(menu == '0') {
            break;
        } else if(menu == '1') {
            patientRegitration(fileData);
        } else if(menu == '2') {
            patientSearch(fileData);
        } else if(menu == '3') {
            patientList(fileData);
        } else if(menu == '4') {
            patientModify(fileData);
        } else {
            printf("\nWrong Command.");
            pressAnyKeyToContinue();
        }
    }

    fclose(fileData);

    printf("Program End.");

    return 0;
}