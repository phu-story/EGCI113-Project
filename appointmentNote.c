#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

void adminMenu();

void appointmentNote() {
    struct PatientDataStruct {
        char FirstName[30], LastName[30];
        char id[6];
    };

    struct dateTimeStruct {
        char* day;
        char* month;
        char* date;
        char* hour;
        char* year;
    };

    char *noting[12][6];

    struct PatientDataStruct PatientInfo;
    struct dateTimeStruct dateTime;
    struct dirent *entry;

    system("clear");
    retry:

    printf("Enter patient ID (Enter 0 to exit): ");
    scanf("%6s", PatientInfo.id);

    DIR *dir = opendir("PatientFolder");
        if (dir != NULL) {
            while ((entry = readdir(dir)) != NULL) {
                char* simplifyName = strtok(entry->d_name, "_");

                if (simplifyName != NULL && strcmp(simplifyName, PatientInfo.id) == 0) {
                    simplifyName = strtok(NULL, "_");
                    strcpy(PatientInfo.FirstName, simplifyName);
                    if(strcmp(simplifyName, "admin") == 0) {
                        system("clear");
                        printf("CANNOT ADPPOINT ADMIN\n");
                        goto retry;
                    }
                    printf("Patient Name: %s\n", PatientInfo.FirstName);
                }
            }
        }
    
    if (strcmp(PatientInfo.id, "0") == 0) {
        adminMenu();
    }

    char openFolder[100];
    sprintf(openFolder, "PatientFolder/%s_%s", PatientInfo.id, PatientInfo.FirstName);
    dir = opendir(openFolder);
    if (dir == NULL) {
        printf("Could not open directory: %s\n", openFolder);
        return;
    }

    int count = 1;
    int noteFound = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, "record.txt") != 0 && 
            strcmp(entry->d_name, ".") != 0 && 
            strcmp(entry->d_name, "..") != 0 
            )
        {
            noteFound = 1;
            dateTime.day = strtok(entry->d_name, " ");
            dateTime.month = strtok(NULL, " ");
            dateTime.date = strtok(NULL, " ");
            dateTime.hour = strtok(NULL, " ");
            dateTime.year = strtok(NULL, " ");
            dateTime.year = strtok(dateTime.year, "_");


            struct tm inputDate = {0};
            if (dateTime.date != NULL) {
                inputDate.tm_mday = atoi(dateTime.date);
            }
            if (dateTime.month != NULL) {
                inputDate.tm_mon = atoi(dateTime.month) - 1;
            }
            if (dateTime.year != NULL) {
                inputDate.tm_year = atoi(dateTime.year) - 1900;
            }
            if (dateTime.hour != NULL) {
                char simplifyHour[10];
                strcpy(simplifyHour, dateTime.hour);
                char *tempHour = strtok(simplifyHour, ":");
                inputDate.tm_hour = atoi(dateTime.hour);
                char hourStr[3];
                snprintf(hourStr, sizeof(hourStr), "%d", inputDate.tm_hour);
                noting[count][5] = strdup(hourStr);
                // printf("Here: %s\n", noting[count][5]);
            }

            time_t inputTime = mktime(&inputDate);
            time_t currentTime = time(NULL);
            
            if (difftime(inputTime, currentTime) != 0){
                printf("%d) %s/%s/%s at %s\n", count, dateTime.date, dateTime.month, dateTime.year, dateTime.hour);
                noting[count][0] = dateTime.day;
                noting[count][1] = dateTime.month;
                noting[count][2] = dateTime.date;
                noting[count][3] = dateTime.hour;
                noting[count][4] = dateTime.year;

                count++;
            }
        }
        
    }
    closedir(dir);

    if (noteFound == 0) {
        system("clear");
        printf("No appointment found\n");
        goto retry;
    }
    
    enterNoteNumber:
    printf("Enter the note number: ");
    int noteNumber;
    scanf("%d", &noteNumber);

    int monthInt = 0;
    if (strcmp(noting[noteNumber][1], "Jan") == 0) {
        monthInt = 1;
    } else if (strcmp(dateTime.month, "Feb") == 0) {
        monthInt = 2;
    } else if (strcmp(dateTime.month, "Mar") == 0) {
        monthInt = 3;
    } else if (strcmp(dateTime.month, "Apr") == 0) {
        monthInt = 4;
    } else if (strcmp(dateTime.month, "May") == 0) {
        monthInt = 5;
    } else if (strcmp(dateTime.month, "Jun") == 0) {
        monthInt = 6;
    } else if (strcmp(dateTime.month, "Jul") == 0) {
        monthInt = 7;
    } else if (strcmp(dateTime.month, "Aug") == 0) {
        monthInt = 8;
    } else if (strcmp(dateTime.month, "Sep") == 0) {
        monthInt = 9;
    } else if (strcmp(dateTime.month, "Oct") == 0) {
        monthInt = 10;
    } else if (strcmp(dateTime.month, "Nov") == 0) {
        monthInt = 11;
    } else if (strcmp(dateTime.month, "Dec") == 0) {
        monthInt = 12;
    }

    char ascAppointTime[30];
    snprintf(ascAppointTime, 30, "%s/%d/%s/%s", noting[noteNumber][2], monthInt, noting[noteNumber][4], noting[noteNumber][5]);
    strcpy(ascAppointTime, asctimeFormat(ascAppointTime));
    // printf("here; %s", ascAppointTime);


    if (noteNumber < 1 || noteNumber >= count) {
        printf("Invalid note number\n");
        goto enterNoteNumber;
    }

    char openFile[100];
    sprintf(openFile, "PatientFolder/%s_%s/%s_Appointment.txt", PatientInfo.id, PatientInfo.FirstName, ascAppointTime);
    FILE *fp = fopen(openFile, "a");
    if (fp == NULL) {
        printf("Could not open file: %s\n", openFile);
        return;
    } else {
        char note[2500];
        printf("Enter the note: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Clear input buffer
        fgets(note, sizeof(note), stdin);
        fprintf(fp, "\nNote: %s", note);
        printf("Note added (press enter to continue)\n");
    }

    fclose(fp);
    adminMenu();
}