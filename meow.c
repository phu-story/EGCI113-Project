#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "Appointment_schedule.txt"
#define START_HR 8
#define END_HR 18
#define MAX_APPOINTMENTS 1000
void BookingSystem(void);
void AppointmentSaved(void);
int AvailableCheck(int,int,int,int);
void AddAppointment();

struct Appointment { //struct appointment info
    char name[50];
    int date;
    int month;
    int year;
    int hour;
};

struct Appointment booking[MAX_APPOINTMENTS];
int booking_amount = 0; //set initial amount of booking as 0

int main(int argc, const char * argv[]) {
    BookingSystem(); //update everytime
    char choice;
    do{
        struct Appointment a;
        printf("Enter your name (Firstname Surename): ");
        scanf("%[^\n]", a.name); //to be able to read full name with space
        printf("Enter date you want to make appointment (DD MM YYYY): ");
        scanf("%d %d %d", &a.date, &a.month, &a.year);
        printf("Available time on %02d/%02d/%02d:\n", a.date, a.month, a.year);
        int available_time = 0; // set initial
        int timetable[END_HR - START_HR][2]; //size of timetable
        for(int hour = START_HR; hour<END_HR;hour++){
            if(AvailableCheck(a.date, a.month, a.year, hour)){ //call function to check time available
                timetable[available_time][0] = hour;       // Start hour
                timetable[available_time][1] = hour + 1;   // End hour
                available_time++;
                printf("%2d. %02d:00 - %02d:00\n", available_time, timetable[available_time - 1][0], timetable[available_time - 1][1]);
            }
        }
        if (available_time==0) {
            printf("This time is unavailable\n");
        } else {
            int time_choice;
            printf("Please select appointment time (enter the number): ");
            scanf("%d", &time_choice);
            if (time_choice>=1 && time_choice<=available_time) {
                a.hour = timetable[time_choice - 1][0];
                AddAppointment(a);
                AppointmentSaved();
                printf("Appointment Successful for %02d/%02d/%02d at  %02d:00 - %02d:00 \n",a.date, a.month, a.year, timetable[time_choice - 1][0], timetable[time_choice - 1][1] );
                printf("Thank you %s\n", a.name);
            } else {
                printf("Invalid selection");
            }
        }
        printf("Do you confirm the appointment (Y/N): ");
        scanf(" %c", &choice);
    } while(choice=='n' || choice=='n');
        
    return 0;
}

void BookingSystem(void){
    FILE * fp = fopen(FILENAME, "r");
    if(fp==NULL){ // no appointment yet (check)
        return; //back
    }
    booking_amount  = 0;
    for (booking_amount=0; fscanf(fp, "%49[^,] %d %d %d %d", &booking[booking_amount].name, &booking[booking_amount].date, &booking[booking_amount].month, &booking[booking_amount].year, &booking[booking_amount].hour) == 5 ; booking_amount++){ //check if the info was read
        if (booking_amount>MAX_APPOINTMENTS){
            printf("Sorry, we have reached the maximum appointments.");
            break;
        }
    }
    fclose(fp);
}

void AppointmentSaved(void) {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(fp, "Date,Month,Year,Hour\n"); 
    for (int i = 0; i < booking_amount; i++) {
        fprintf(fp, "%s %d,%d,%d,%d\n",
                booking[i].name,
                booking[i].date,
                booking[i].month,
                booking[i].year,
                booking[i].hour);
    }
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

