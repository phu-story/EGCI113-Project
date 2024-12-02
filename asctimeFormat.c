#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "asctimeFormat.h"

char* asctimeFormat(char* readingAppointment){
    char *appointmentArr[4];
    int appointmentDay, appointmentMonth, appointmentYear, appointmentTime;

    appointmentArr[0] = strtok(readingAppointment, "/");
    for (int i = 1; i != 4; i++) {
        appointmentArr[i] = strtok(NULL, "/");
        if (appointmentArr[i] == NULL) {
            fprintf(stderr, "Error: Invalid appointment format\n");
            return NULL;
        }
    }

    // Convert strings to integers
    appointmentDay = atoi(appointmentArr[0]);
    appointmentMonth = atoi(appointmentArr[1]);
    appointmentYear = atoi(appointmentArr[2]);
    appointmentTime = atoi(appointmentArr[3]);

    // Set up the tm struct for formatting
    struct tm timeinfo = {0};
    timeinfo.tm_mday = appointmentDay;
    timeinfo.tm_mon = appointmentMonth - 1;
    timeinfo.tm_year = appointmentYear - 1900;
    timeinfo.tm_hour = appointmentTime;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;

    // Format and print the time in asctime format
    char *formatted_time = asctime(&timeinfo);
    formatted_time[strcspn(formatted_time, "\n")] = 0; // Remove newline character
    
    return formatted_time;
}
