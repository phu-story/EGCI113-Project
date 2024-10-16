#include <stdio.h>
#include <conio.h>

#define FileName "PatientData"

struct PatientDataStruct {
    char Id[8], FirstName[30], LastName[30], fileName[30];
};

// Global Function
void patientRegitration();
void patientSearch();
void patientList();
void patientModify();

void clear() {
    //system("clear"); // Clear cmd for unix
    system("cls"); // Clear cmd for window
    //printf("\n\n\n\n\n\n\n\n\n\n");
    return;
}

void pressAnyKeyToContinute() {
    printf("\nPress any key to continue...");
    getch();

    return;
}

// Global Variable
struct PatientDataStruct PatientData;
int recordSize = 0;
FILE *fileData;

int main() {
    printf("Loading...");

    char menu = 0;

    // Check File
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
            pressAnyKeyToContinute();
        }
    }

    fclose(fileData);

    printf("Program End.");

    return 0;
}

void patientRegitration() {
    struct PatientDataStruct NewPatientData;
    char action;

    printf("-=-=-=-=-=-=- Patient Regitration -=-=-=-=-=-=-\n");

    printf("Enter patient's ID: ");
    scanf("%s", &NewPatientData.Id);

    printf("Enter patient's firstname: ");
    scanf("%s", &NewPatientData.FirstName);

    printf("Enter patient's lastname: ");
    scanf("%s", &NewPatientData.LastName);

    patientRegitrationCheckDuplicatePatientId:

    // Check duplicate patient Id
    rewind(fileData);
    while (fread(&PatientData, recordSize, 1, fileData) == 1) {
        if(strcmp(NewPatientData.Id, PatientData.Id) == 0) {
            printf("\nPatient Id %s already exist.\n", NewPatientData.Id);
            printf("Do you want to replace exist patient data or change patient Id?\n");
            printf("Exit and do not save: 0\n");
            printf("Replace Exist Patient Data: 1\n");
            printf("Change Patient Id: 2\n");
            printf("What action do you want to make?: ");

            action = getch();

            printf("%c\n\n", action);

            if(action == '0') {
                printf("\n\nNoting change.");
                return pressAnyKeyToContinute();
            } else if(action == '1') {
                fseek(fileData, -recordSize, SEEK_CUR);
                fwrite(&NewPatientData, recordSize, 1, fileData);

                printf("\n\nReplace Patient Data Success.");
                return pressAnyKeyToContinute();
            } else if(action == '2') {
                printf("Enter NEW patient's ID: ");
                scanf("%s", &NewPatientData.Id);

                goto patientRegitrationCheckDuplicatePatientId;
            } else {
                printf("Wrong Action!");
                goto patientRegitrationCheckDuplicatePatientId;
            }

            break;
        }
    }

    rewind(fileData);
    fseek(fileData, 0, SEEK_END);
    fwrite(&NewPatientData, recordSize, 1, fileData);

    printf("\n\nSave Patient Data Success.");
    return pressAnyKeyToContinute();
}

void patientSearch() {
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

    return pressAnyKeyToContinute();
}

void patientList() {
    int recordCount = 0;

    printf("-=-=-=-=-=-=- Patient List -=-=-=-=-=-=-\n");

    rewind(fileData);
    while (fread(&PatientData, recordSize, 1, fileData) == 1) {
        recordCount++;
        printf("Id: %s\n", PatientData.Id);
        printf("FirstName: %s\n", PatientData.FirstName);
        printf("LastName: %s\n", PatientData.LastName);
        printf("\n");
    }

    if(recordCount == 0) {
        printf("No Patient Found.\n");
    } else {
        printf("\nTotal Patient: %d\n", recordCount);
    }

    return pressAnyKeyToContinute();
}

void patientModify() {
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
        return pressAnyKeyToContinute();
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

        printf("%c\n\n", fieldId);

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

    return pressAnyKeyToContinute();
}
