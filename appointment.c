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
        strcpy(a.name, nameSimplified);
        printf("Hello, %s\n", a.name);

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

        closedir(dir);
        scanf("%s", a.doctorID);

        while ((entry = readdir(dir)) != NULL) {
                char* simplifyID = strtok(entry->d_name, "_");
                if(strcmp(simplifyID, a.doctorID) == 0 ) {    
                simplifyID = strtok(NULL, "_");
                if (simplifyID != NULL) {
                    strcpy(a.doctorName, simplifyID);
                }
            }
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
    strcpy(openingFile, reserveDir);
    sprintf(openingFile, "%s/record.txt", openingFile);
    
    FILE *fp = fopen(openingFile, "a");

    char makingFile[256];
    strcpy(makingFile, reserveDir);
    char appointTime[20];
    sprintf(appointTime, "%d/%d/%d/%d_Appoint", a.date, a.month, a.year, a.hour);
    printf("%s\n", appointTime);
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    snprintf(makingFile, sizeof(makingFile), "%s/%s_Appointment.txt", reserveDir, asctimeFormat(appointTime));
    fp = fopen(makingFile, "w");
    fprintf(fp, "Appoint by Dr.%s\nIssue on %s\nAppoint on %s", 
                a.doctorName, asctime(timeinfo), asctimeFormat(appointTime)
            );
    fclose(fp);

}

int AvailableCheck(int date, int month, int year, int hour){
    for(int i=0; i<booking_amount;i++){
        if(booking[i].date==date && booking[i].month==month && booking[i].year==year && booking[i].hour==hour){
            return 0; //unavailable
        }
    }
    return 1; //available
}

void AddAppointment(struct Appointment a){
    if(booking_amount>=MAX_APPOINTMENTS){
        printf("Sorry, we have reached the maximum appointments.");
    }
    booking[booking_amount++]=a;
}