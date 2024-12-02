#ifndef PATIENT_H
#define PATIENT_H

struct PatientDataStruct {
    char FirstName[30];
    char LastName[30];
    char id[6];
};

// Prototype
void patientView(char id[6]);
void patientRegistration();

#endif // PATIENT_H
