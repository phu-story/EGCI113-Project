#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "patient.h"

struct PatientDataStruct PatientData;

char* dirSeek(char id[6]) {
    struct PatientDataStruct{
            char FirstName[30], LastName[30];
            char id[6];
    };
    struct PatientDataStruct PatientData;

    struct dirent *entry;
    DIR *dir = opendir("PatientFolder");
    if (dir != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            char* simplifyID = strtok(entry->d_name, "_");

            if (simplifyID != NULL && strcmp(simplifyID, id) == 0) {
                simplifyID = strtok(NULL, "_");
                strcpy(PatientData.FirstName, simplifyID);
                
            }
        }
    }
    
    char *openingFile = malloc(100 * sizeof(char));
    if (openingFile == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    sprintf(openingFile, "PatientFolder/%s_%s", id, PatientData.FirstName);
    // printf("%s\n", openingFile);
    
    return openingFile;
}
