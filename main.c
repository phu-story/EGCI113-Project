// Import Library
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Import Function
#include "login.c"
#include "adminMenu.c"

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
            scanf("%255s", password);
            printf("Initiation: Folder created\n");
            char adminFolder[256];
            snprintf(adminFolder, 256, "PatientFolder/%s_admin", password);
            mkdir(adminFolder, 0777);
        } else {
            printf("Error: File not created\n");
            return 0;
        }
    }

    printf("Status: Ready\n");

    system("clear");

    // login();
    adminMenu();
    
    getchar();

    printf("Program End");

    return 0;
}