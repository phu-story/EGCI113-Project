// Import Library
#include <stdio.h>
#include <stdlib.h>

void clear() {
    //system("clear"); // Clear cmd for unix
    system("cls"); // Clear cmd for window
    //printf("\n\n\n\n\n\n\n\n\n\n");
    return;
}

void pressAnyKeyToContinue() {
    printf("\nPress any key to continue...");
    getch();

    return;
}