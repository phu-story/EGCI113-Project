// Import Library

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void clear() {
    //system("clear"); // Clear cmd for unix
    system("cls"); // Clear cmd for window
    //printf("\n\n\n\n\n\n\n\n\n\n");
    return;
}

int pressAnyKeyToContinue() {
    printf("\nPress any key to continue...");
    getch();

    return 0;
}