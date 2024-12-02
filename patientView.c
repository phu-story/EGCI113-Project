#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include "patient.h"

char* asctimeFormat(char*);

struct PatientDataStruct{
    char FirstName[30], LastName[30], id[6];
};
struct PatientDataStruct PatientData;

void patientView(char id[6]) {
    struct dirent *entry;
    DIR *dir = opendir("PatientFolder");
    retry:
    if (dir != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            char* simplifyID = strtok(entry->d_name, "_");

            if (simplifyID != NULL && strcmp(simplifyID, id) == 0) {
                simplifyID = strtok(NULL, "_");
                strcpy(PatientData.FirstName, simplifyID);
                if(strcmp(simplifyID, "admin") == 0) {
                    system("clear");
                    printf("CANNOT VIEW ADMIN\n");
                    goto retry;
                }
            }
        }
    }
    
    char openingFile[100];
    sprintf(openingFile, "PatientFolder/%s_%s/record.txt", id, PatientData.FirstName);

    system("clear");

    FILE *file = fopen(openingFile, "r");
    char buffer[128];

    char readingID[30], 
        readingFirstName[30], 
        readingLastName[30], 
        readingDobDay[3],
        readingDobMonth[3], 
        readingDobYear[5], 
        readingAppointment[20];

    // rewind(file);

    while (fgets(buffer, 128, file)) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

        char* token = strtok(buffer, " ");

        if(strcmp(token, "PatientID:") == 0) {
            token = strtok(NULL, " ");
            strcpy(readingID, token);
        }
        if (strcmp(token, "PatientName:") == 0) {
            token = strtok(NULL, " ");
            strcpy(readingFirstName, token);
        }
        if (strcmp(token, "PatientLastName:") == 0) {
            token = strtok(NULL, " ");
            strcpy(readingLastName, token);
        }
        if (strcmp(token, "PatientDOB:") == 0) {
            token = strtok(NULL, " ");
            strcpy(readingDobDay, token);
            token = strtok(NULL, " ");
            strcpy(readingDobMonth, token);
            token = strtok(NULL, " ");
            strcpy(readingDobYear, token);
        }
        
        if (strcmp(token, "OpenAppointment:") == 0) {
            token = strtok(NULL, " ");
            strcpy(readingAppointment, token);
        }
        
    }

    // printf("%s\n", readingAppointment);

    printf("ID: %s\n", readingID);
    printf("Name: %s %s\n", readingFirstName, readingLastName);
    printf("Date of Birth: %s %s %s\n", readingDobDay, readingDobMonth, readingDobYear);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int currentYear = tm.tm_year + 1900;
    int currentMonth = tm.tm_mon + 1;
    int currentDay = tm.tm_mday;

    int ageYears = currentYear - atoi(readingDobYear);
    int ageMonths = currentMonth - atoi(readingDobMonth);
    int ageDays = currentDay - atoi(readingDobDay);

    if (ageDays < 0) {
        ageDays += 30; // Approximate days in a month
        ageMonths--;
    }

    if (ageMonths < 0) {
        ageMonths += 12;
        ageYears--;
    }

    printf("Age: %d years %d months %d days old\n", ageYears, ageMonths, ageDays);

    if (strcmp(readingAppointment, "") != 0) {
        printf("Appointment: %s\n", asctimeFormat(readingAppointment));
    } else {
        printf("No appointment\n");
    }

    fclose(file);
    
    return;
}
