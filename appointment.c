#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>

#define FILENAME "Appointment_schedule.txt"
#define START_HR 8
#define END_HR 18
#define MAX_APPOINTMENTS 1000

void BookingSystem(void);
void AppointmentSaved(void);
int AvailableCheck(int,int,int,int);
void AddAppointment();

time_t rawtime;
struct tm * timeinfo;

struct Appointment { //struct appointment info
    char id[6];
    char name[50];
    char doctorID[6];
    char doctorName[30];
    int date;
    int month;
    int year;
    int hour;
};

struct Appointment a;
struct Appointment booking[MAX_APPOINTMENTS];


char *openingFile;
char *reserveDir;
int booking_amount = 0; //set initial amount of booking as 0

void makeAppointment() {
    openingFile = malloc(256); // Allocate memory for openingFile
    BookingSystem(); // Update every time
    char choice;
    do {
        system("clear");
        retry:
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        printf("Current local time and date: %s", asctime(timeinfo));

        printf("Enter your ID(enter 0 exit): ");
        scanf("%s", a.id);

        if (strcmp(a.id, "0") == 0) {
            free(openingFile); // Free allocated memory
            adminMenu();
        }

        struct dirent *entry;
        DIR *dir = opendir("PatientFolder");
        if (dir != NULL) {
            while ((entry = readdir(dir)) != NULL) {
                char entryNameCopy[256];
                strncpy(entryNameCopy, entry->d_name, sizeof(entryNameCopy) - 1);
                entryNameCopy[sizeof(entryNameCopy) - 1] = '\0';
                char* simplifyID = strtok(entryNameCopy, "_");
                if (simplifyID != NULL && strcmp(simplifyID, a.id) == 0) {
                    goto idFound;
                }
            }
            system("clear");
            printf("ID not found\n");
            goto retry;
        }
        idFound:

        openingFile = dirSeek(a.id);
        reserveDir = malloc(strlen(openingFile) + 1);
        strcpy(reserveDir, openingFile);
        sprintf(openingFile, "%s/record.txt", openingFile);

        
        char *nameSimplified = strtok(openingFile, "_");
        if (nameSimplified == NULL) {
            printf("ID not found\n");
            goto retry;
        }
        

        nameSimplified = strtok(NULL, "_");
        nameSimplified = strtok(nameSimplified, "/");

        if(strcmp(nameSimplified, "admin") == 0) {
            system("clear");
            printf("CANNOT ADPPOINT ADMIN\n");
            goto retry;
        }

        strcpy(a.name, nameSimplified);
        printf("Patient's name, %s\n", a.name);

        // Input date
        printf("Enter date you want to make an appointment (DD MM YYYY): ");
        scanf("%d %d %d", &a.date, &a.month, &a.year);

        // Check if the date is in the past
        struct tm inputDate = {0};
        inputDate.tm_mday = a.date;
        inputDate.tm_mon = a.month - 1; // Months are zero-indexed
        inputDate.tm_year = a.year - 1900;

        time_t inputTime = mktime(&inputDate);
        time_t currentTime = time(NULL);

        if (difftime(inputTime, currentTime) < 0) {
            printf("You cannot book an appointment for a past date.\n");
            // goto retry;
            continue;
        }

        printf("Appointment for which doctor?\n");
        dir = opendir("DoctorFolder");
        if (dir == NULL) {
            printf("Error: DoctorFolder directory does not exist.\n");
            continue;
        } else {
            while ((entry = readdir(dir)) != NULL) {
                char* simplifyID = strtok(entry->d_name, "_");
                if(strcmp(simplifyID, "0") != 0 && strcmp(simplifyID, ".") != 0 && strcmp(simplifyID, "..") != 0) {    
                    printf("%s) ", simplifyID);
                    simplifyID = strtok(NULL, "_");
                    if (simplifyID != NULL) {
                        printf("%s\n", simplifyID);
                    }
                }
            }
        }

        scanf("%s", a.doctorID);

        rewinddir(dir); // Reset directory stream
        while ((entry = readdir(dir)) != NULL) {
            char* simplifyID = strtok(entry->d_name, "_");
            if(strcmp(simplifyID, a.doctorID) == 0 ) {    
                simplifyID = strtok(NULL, "_");
                if (simplifyID != NULL) {
                    strcpy(a.doctorName, simplifyID);
                }
            }
        }
        closedir(dir);

        printf("Doctor's name: %s\n", a.doctorName);

        // Display available times
        printf("Available time on %02d/%02d/%02d:\n", a.date, a.month, a.year);
        int available_time = 0;
        int timetable[END_HR - START_HR][2];
        for (int hour = START_HR; hour < END_HR; hour++) {
            if (AvailableCheck(a.date, a.month, a.year, hour)) {
                timetable[available_time][0] = hour;
                timetable[available_time][1] = hour + 1;
                available_time++;
                printf("%2d. %02d:00 - %02d:00\n", available_time, timetable[available_time - 1][0], timetable[available_time - 1][1]);
            }
        }

        if (available_time == 0) {
            printf("No available slots on this date.\n");
            continue;
        }

        // Select a time slot
        int time_choice;
        printf("Please select appointment time (enter the number): ");
        scanf("%d", &time_choice);

        if (time_choice >= 1 && time_choice <= available_time) {
            a.hour = timetable[time_choice - 1][0];
            AddAppointment(a);
            AppointmentSaved();
            printf("Appointment confirmed for %02d/%02d/%02d at %02d:00 - %02d:00\n",
                   a.date, a.month, a.year, timetable[time_choice - 1][0], timetable[time_choice - 1][1]);
            printf("Thank you, %s\n", a.name);
        } else {
            printf("Invalid selection.\n");
        }

        printf("Do you confirm the appointment (Y/N): ");
        scanf("%c", &choice);

        if (choice == 'n') {
            char makingFile[256];
            strcpy(makingFile, reserveDir);
            char appointTime[20];
            sprintf(appointTime, "%d/%d/%d/%d", a.date, a.month, a.year, a.hour);
            strcpy(appointTime, asctimeFormat(appointTime));
            snprintf(makingFile, sizeof(makingFile), "%s/%s_Appointment.txt", reserveDir, appointTime);
            
            if (remove(makingFile) == 0) {
                printf("Appointment cancelled\n");
            } else {
                printf("Error cancelling appointment\n");
            }
        }

    } while (choice == 'n' || choice == 'N');

    free(openingFile); // Free allocated memory
    adminMenu();
}


void BookingSystem(){
    FILE * fp = fopen(openingFile, "r");
    if(fp==NULL){ // no appointment yet (check)
        return; //back
    }
    booking_amount  = 0;
    for (booking_amount=0; fscanf(fp, "%49[^,],%d,%d,%d,%d", booking[booking_amount].name, &booking[booking_amount].date, &booking[booking_amount].month, &booking[booking_amount].year, &booking[booking_amount].hour) == 5 ; booking_amount++){ //check if the info was read
        if (booking_amount>MAX_APPOINTMENTS){
            printf("Sorry, we have reached the maximum appointments.");
            break;
        }
    }
    fclose(fp);
}

void AppointmentSaved() {
    if (!reserveDir || !openingFile) {
        printf("Error: Missing required file paths.\n");
        return;
    }

    // Construct file path for the record
    snprintf(openingFile, 256, "%s/record.txt", reserveDir);

    FILE *fp = fopen(openingFile, "r");
    if (!fp) {
        perror("Failed to open record file");
        return;
    }

    char makingFile[256];
    snprintf(makingFile, 256, "%s", reserveDir);
    char appointTime[20];
    snprintf(appointTime, 20, "%d/%d/%d/%d", a.date, a.month, a.year, a.hour);

    char buffer[128];
    char readingAppointment[128] = "NoAppointment";

    // Read the record file
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        char *token = strtok(buffer, ": ");
        if (token && strcmp(token, "OpenAppointment") == 0) {
            token = strtok(NULL, ": ");
            if (token) {
                strncpy(readingAppointment, token, sizeof(readingAppointment) - 1);
                readingAppointment[sizeof(readingAppointment) - 1] = '\0';
            }
        }
    }
    fclose(fp);

    // Process the appointment if it exists
    if (strcmp(readingAppointment, "NoAppointment") != 0) {
        int refDateValid = 0; // Flag to check date comparison

        struct tm refDate = {0};
        char *token = strtok(readingAppointment, "/");
        if (token) refDate.tm_mday = atoi(token);
        token = strtok(NULL, "/");
        if (token) refDate.tm_mon = atoi(token) - 1;
        token = strtok(NULL, "/");
        if (token) refDate.tm_year = atoi(token) - 1900;
        token = strtok(NULL, "/");
        if (token) refDate.tm_hour = atoi(token);

        struct tm inputDate = {0};
        inputDate.tm_mday = a.date;
        inputDate.tm_mon = a.month - 1;
        inputDate.tm_year = a.year - 1900;
        inputDate.tm_hour = a.hour;

        // Compare the reference date with the new appointment
        if (difftime(mktime(&refDate), mktime(&inputDate)) < 0) {
            refDateValid = 1;
        }

        // Update the record if the new appointment is valid
        if (refDateValid) {
            FILE *tempFile = fopen("temp.txt", "w");
            if (!tempFile) {
                perror("Failed to create temporary file");
                return;
            }

            fp = fopen(openingFile, "r");
            if (!fp) {
                perror("Failed to reopen record file");
                fclose(tempFile);
                return;
            }

            while (fgets(buffer, sizeof(buffer), fp)) {
                if (strncmp(buffer, "OpenAppointment:", 15) == 0) {
                    fprintf(tempFile, "OpenAppointment: %s\n", appointTime);
                } else {
                    fputs(buffer, tempFile);
                }
            }

            fclose(fp);
            fclose(tempFile);

            // Replace the original file with the updated file
            if (rename("temp.txt", openingFile) != 0) {
                perror("Failed to update record file");
            }
        }
    } else {
        // Add the new appointment directly
        fp = fopen(openingFile, "a");
        if (fp) {
            fprintf(fp, "OpenAppointment: %s\n", appointTime);
            fclose(fp);
        } else {
            perror("Failed to append to record file");
        }
    }

    // Create a new appointment file
    snprintf(makingFile, sizeof(makingFile), "%s/%s_Appointment.txt", reserveDir, appointTime);
    fp = fopen(makingFile, "w");
    if (fp) {
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        fprintf(fp, "Appoint by Dr.%s\nIssue on %s\nAppoint on %s", 
                a.doctorName, asctime(timeinfo), appointTime);
        fclose(fp);
    } else {
        perror("Failed to create appointment file");
    }

    // Update doctor folder with new appointment
    snprintf(makingFile, sizeof(makingFile), "DoctorFolder/%s_%s/%s", a.doctorID, a.doctorName, appointTime);
    fp = fopen(makingFile, "w");
    if (fp) fclose(fp);
    else perror("Failed to update doctor folder");
}


int AvailableCheck(int date, int month, int year, int hour){
    struct dateTimeStruct{
        char* day;
        char* month;
        char* date;
        char* hour;
        char* year;
    };
    struct dateTimeStruct dateTime;
    struct dirent *entry;

    char openFolder[100];
    sprintf(openFolder, "DoctorFolder/%s_%s", a.doctorID, a.doctorName);

    DIR *dir = opendir(openFolder);
    if (dir == NULL) {
        printf("Could not open directory: %s\n", openFolder);
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && 
            strcmp(entry->d_name, "..") != 0
            )
        {
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
                if (strcmp(dateTime.month, "January") == 0) {
                    inputDate.tm_mon = 1;
                } else if (strcmp(dateTime.month, "February") == 0) {
                    inputDate.tm_mon = 2;
                } else if (strcmp(dateTime.month, "March") == 0) {
                    inputDate.tm_mon = 3;
                } else if (strcmp(dateTime.month, "April") == 0) {
                    inputDate.tm_mon = 4;
                } else if (strcmp(dateTime.month, "May") == 0) {
                    inputDate.tm_mon = 5;
                } else if (strcmp(dateTime.month, "June") == 0) {
                    inputDate.tm_mon = 6;
                } else if (strcmp(dateTime.month, "July") == 0) {
                    inputDate.tm_mon = 7;
                } else if (strcmp(dateTime.month, "August") == 0) {
                    inputDate.tm_mon = 8;
                } else if (strcmp(dateTime.month, "September") == 0) {
                    inputDate.tm_mon = 9;
                } else if (strcmp(dateTime.month, "October") == 0) {
                    inputDate.tm_mon = 10;
                } else if (strcmp(dateTime.month, "November") == 0) {
                    inputDate.tm_mon = 11;
                } else if (strcmp(dateTime.month, "December") == 0) {
                    inputDate.tm_mon = 12;   
                }
            }

            if (dateTime.year != NULL) {
                    inputDate.tm_year = atoi(dateTime.year);
            }  

            if (inputDate.tm_mday == date && inputDate.tm_mon == month && inputDate.tm_year == year && atoi(dateTime.hour) == hour) {
                return 0;
            } else {
                return 1;
            }
            
                closedir(dir); 
                
            }
        }
        return 1;
    }

    // char appointTime[20];
    // sprintf(appointTime, "%d/%d/%d/%d_Appoint", a.date, a.month, a.year, a.hour);

    // char doctorFilePath[256];
    // snprintf(doctorFilePath, sizeof(doctorFilePath), "DoctorFolder/%s_%s/%s.txt", a.doctorID, a.doctorName, asctimeFormat(appointTime));
    // if (access(doctorFilePath, F_OK) == 0){
        
    //     return 0;
    // } else {
    //     return 1;
    // }

void AddAppointment(struct Appointment a){
    if(booking_amount>=MAX_APPOINTMENTS){
        printf("Sorry, we have reached the maximum appointments.");
    }
    booking[booking_amount++]=a;
}