#include <stdio.h>
#include <io.h>

void login() {
    struct PatientDataStruct{
        char FirstName[30], LastName[30], id[6];
    };
    
    struct PatientDataStruct PatientData;
    while (1) {
        char option = 0;
        char path[40];
        

        printf("Select login option\n");
        printf("1) 6-digit ID \n");
        printf("2) First & Last name \n");
        printf("Press '0' to quit or any other key to exit.\n");

        option = getch();
        if(option == '1') {
            printf("Enter your 6-digit id: ");
            scanf("%s", &PatientData.id);

            sprintf(path, "PatientFolder/%s", PatientData.id);

            printf("%s", path);
            
            if(_access(path, 0) == 0){
                printf("Login successful");
            }
        } else if(option == '2') {
            printf("Enter your First name: ");
            scanf("%s", &PatientData.FirstName);

            // printf("Enter your Last name: ");
            // scanf("%s", &PatientData.LastName);

            // char x = system("cd PatientFolder && dir");
            // printf("%s", x);
            struct _finddata_t fileinfo;
            intptr_t handle;
            char searchPath[256];
            snprintf(searchPath, 256, "%s/*", "PatientFolder");

            handle = _findfirst(searchPath, &fileinfo);
            if (handle == -1) {
                printf("Error: No files found\n");
            } else {
                do {
                    if (fileinfo.attrib & _A_SUBDIR) {
                        
                        printf("Checking -> %s\n", fileinfo.name);

                        char* simplify = strtok(fileinfo.name, "_");
                        simplify = strtok(NULL, "_");

                        printf("Compare \"%s\" with \"%s\"\n", simplify, PatientData.FirstName);

                        if (simplify != NULL && strcmp(simplify, PatientData.FirstName) == 0) {
                            printf("Login successful\n");
                            break;
                        }

                    }
                } while (_findnext(handle, &fileinfo) == 0);
                _findclose(handle);
            }
            
        } else {
            return;
        }
        break;
    }
    return;
}