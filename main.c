// Import Library
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Import Function
#include "login.c"
#include "adminMenu.c"
#include "doctorRegistration.c"
#include "patientRegistration.c"
#include "patientView.c"
#include "patientModification.c"
#include "dirSeek.c"
#include "appointment.c"
#include "appointmentNote.c"
#include "asctimeFormat.c"

#define FolderName "PatientFolder"

int main() {
    printf("Status: Initiating\n");

    char menu = 0;

    if(access(FolderName, 0) == 0 ){
        printf("Initiation: Folder existed\n");
    } else if(access(FolderName, 0) == -1) {
        printf("Initiation: Folder not found\n");

        if(mkdir(FolderName, 0777) == 0) {
            char password[30];
            printf("Set-Up admin password: ");
            scanf("%s", password);
            printf("Initiation: Folder created\n");
            char adminFolder[126];
            snprintf(adminFolder, 126, "PatientFolder/%s_admin", password);
            mkdir(adminFolder, 0777);
        } else {
            printf("Error: File not created\n");
            return 0;
        }
        
    }

    if(access("DoctorFolder", 0) == 0 ){
        printf("Initiation: Folder existed\n");
    } else if(access("DoctorFolder", 0) == -1) {
        printf("Initiation: Folder not found\n");
        if (mkdir("DoctorFolder", 0777) == 0) {
            char doctorInitialFolder[126];
            snprintf(doctorInitialFolder, 126, "DoctorFolder/0_DEMO");
            mkdir(doctorInitialFolder, 0777);
        }
    }

    printf("Status: Ready\n");

    system("clear");

    login();
    // adminMenu();
    // patientView("333333");
    // patientModification();
    // makeAppointment();
    // printf("%s", dirSeek("111111"));
    // appointmentNote();

    // remove("PatientFolder/111111_bro/Sun May 12 10:00:00 2006_Appointment.txt");
    
    getchar();

    printf("Program End");

    return 0;
}