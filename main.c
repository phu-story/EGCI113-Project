#include <stdio.h>

#define FileName "PatientData"

struct PatientData {
    char Id[8], FirstName[30], LastName[30], fileName[30];
} PatientData;

// Global Function
void patientRegitration();
void patientSearch();
void patientList();
void patientModify();

void clear() {
    system("clear"); // Clear cmd for unix
    system("cls"); // Clear cmd for window
}

void pressAnyKeyToContinute() {
    printf("\nPress any key to continute...");
    getch();
}

// Global Variable
int recordSize = 0;

int main() {
    char menu = 0;

    // Check File
    FILE *fileData;
    fileData = fopen(FileName, "rb+");
    if(fileData == NULL) {
        fileData = fopen(FileName, "wb+");
        if(fileData == NULL) {
            printf("Can't open file.");
            return 0;
        }
    }

    // Set Struct Size
    recordSize = sizeof(PatientData);

    while (1) {
        clear();

        printf("Exit: 0\n");
        printf("Patient Regitration: 1\n");
        printf("Patient Search: 2\n");
        printf("Patient List: 3\n");
        printf("Patient Modify: 4\n");
        printf("What do you want to do?: ");

        menu = getch();

        clear();

        if(menu == '0') {
            break;
        } else if(menu == '1') {
            patientRegitration(fileData);
        } else if(menu == '2') {
            patientSearch(fileData);
        } else if(menu == '3') {
            patientList(fileData);
        } else if(menu == '4') {
            patientModify(fileData);
        } else {
            printf("\nWrong Command.");
        }
    }

    fclose(fileData);

    printf("Program End.");

    return 0;
}

void patientRegitration(fileData) {
    printf("-=-=-=-=-=-=- Patient Regitration -=-=-=-=-=-=-\n");

    printf("Enter patient's ID number: ");
    scanf("%s", &PatientData.Id);

    printf("Enter patient's firstname: ");
    scanf("%s", &PatientData.FirstName);

    printf("Enter patient's lastname: ");
    scanf("%s", &PatientData.LastName);

    rewind(fileData);
    fseek(fileData, 0, SEEK_END);
    fwrite(&PatientData, recordSize, 1, fileData);

    printf("\n\nSave Patient Data Success.");
    pressAnyKeyToContinute();
}

void patientSearch(fileData) {
    char queryId[8];
    int isFound = 0;
    printf("-=-=-=-=-=-=- Patient Search -=-=-=-=-=-=-\n");

    printf("Enter patient's ID: ");
    scanf("%s", &queryId);

    rewind(fileData);
    while (fread(&PatientData, recordSize, 1, fileData) == 1) {
        if(strcmp(queryId, PatientData.Id) == 0) {
            printf("Id: %s\n", PatientData.Id);
            printf("FirstName: %s\n", PatientData.FirstName);
            printf("LastName: %s\n", PatientData.LastName);
            printf("\n");
            isFound = 1;
            break;
        }
    }

    if(!isFound) {
        printf("Patient Id %s not found.\n", queryId);
    }

    pressAnyKeyToContinute();
}

void patientList(fileData) {
    printf("-=-=-=-=-=-=- Patient List -=-=-=-=-=-=-\n");

    rewind(fileData);
    while (fread(&PatientData, recordSize, 1, fileData) == 1) {
        printf("Id: %s\n", PatientData.Id);
        printf("FirstName: %s\n", PatientData.FirstName);
        printf("LastName: %s\n", PatientData.LastName);
        printf("\n");
    }

    pressAnyKeyToContinute();
}

void patientModify(fileData) {
    char queryId[8], fieldId;
    int isFound = 0;
    printf("-=-=-=-=-=-=- Patient Modify -=-=-=-=-=-=-\n");

    printf("Enter patient's ID: ");
    scanf("%s", &queryId);

    rewind(fileData);
    while (fread(&PatientData, recordSize, 1, fileData) == 1) {
        if(strcmp(queryId, PatientData.Id) == 0) {
            isFound = 1;
            break;
        }
    }

    if(!isFound) {
        printf("Patient Id %s not found.\n", queryId);
        pressAnyKeyToContinute();
        return 0;
    }


    printf("Id: %s\n", PatientData.Id);
    printf("FirstName: %s\n", PatientData.FirstName);
    printf("LastName: %s\n", PatientData.LastName);
    printf("\n");

    while (1) {
        printf("Exit: 0\n");
        printf("FirstName: 1\n");
        printf("LastName: 2\n");
        printf("What field do you want to edit?: ");

        fieldId = getch();

        printf("\n\n");

        if(fieldId == '0') {
            fseek(fileData, -recordSize, SEEK_CUR);
            fwrite(&PatientData, recordSize, 1, fileData);

            break;
        } else if(fieldId == '1') {
            printf("FirstName: ");
            scanf("%s", &PatientData.FirstName);
        } else if(fieldId == '2') {
            printf("LastName: ");
            scanf("%s", &PatientData.LastName);
        } else {
            printf("\nField Not Found.");
        }

        printf("\n\n");
    }

    return 0;
}
