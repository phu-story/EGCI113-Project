#include <stdio.h>

// Global Function
void patient_Regitration();

int main() {
    patient_Regitration();

    return 0;
}

void patient_Regitration() {
    // Local Variable
    char PatientName[100], fileName[20];
    int PatientID;

    printf("Enter patient's name: ");
    scanf("%s", PatientName);

    printf("Enter patient's ID number: ");
    scanf("%d", &PatientID);

    sprintf(fileName, "PatientRecord/%d.txt", PatientID);

    FILE *fptr;
    fptr = fopen(fileName, "w");

    fclose(fptr);
}
