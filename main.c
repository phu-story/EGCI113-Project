// Import Library
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>
#include <io.h>

// Import Function
#include "generalFunction.c"
#include "login.c"
#include "adminMenu.c"

#define FolderName "PatientFolder"

int main() {
    printf("Status: Initiating\n");

    char menu = 0;

    if(_access(FolderName, 0) == -1){
        if(_mkdir(FolderName) == 0 ) {
            char password[256];
            printf("Set-Up admin password: ");
            scanf("%255s", password);
            printf("Initiation: Folder created\n");
            char adminFolder[256];
            snprintf(adminFolder, 256, "PatientFolder/admin_%s", password);
            _mkdir(adminFolder);
        } else {
            printf("Error: File not created\n");
            return 0;
        }
    } else if(_access(FolderName, 0) == 0){
        printf("Initiation: Folder existed\n");
    } else{
        printf("Error: Bad reading");
    }

    printf("Status: Ready\n");

    clear();

    // login();
    adminMenu();
    
    getch();

    printf("Program End");

    return 0;
}