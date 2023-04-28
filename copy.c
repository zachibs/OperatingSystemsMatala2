#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 256

int copy_func(char* firstFile, char* secondFile, int vFlag, int fFlag) {

    FILE *sourceFile = fopen(firstFile, "rb");
    if (sourceFile == NULL) {
        if (vFlag) {
            printf("general failure\n");
        }
        return 1;
    }

    if (!fFlag) {
        if (fopen(secondFile, "r") != NULL) {
            if (vFlag) {
                printf("target file exist\n");
            }
            return 1;
        }
    }


    FILE *targetFile = fopen(secondFile, "wb");
    if (targetFile == NULL) {
        fclose(sourceFile);
        if (vFlag) {
            printf("general failure\n");
        }
        return 1;
    }

    char buffer[BUFFER];
    size_t data;
    while ((data = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, data, targetFile);
    }

    fclose(sourceFile);
    fclose(targetFile);
}

int main(int argc, char *argv[]) {

    if (argc <= 2) { 
        printf("Arguements enterd are not sufficient \n");
        return -1;
    }
    
    int fFlag = 0;
    int vFlag = 0;
    char *firstFile, *secondFile;

    if ((strcmp(argv[3], "-v") == 0) || (strcmp(argv[4], "-v") == 0)) {
        vFlag = 1;
    }

    if ((strcmp(argv[3], "-i") == 0) || (strcmp(argv[4], "-f") == 0)) {
        fFlag = 1;
    }

    int returnedNum = copy_func(argv[1], argv[2], vFlag, fFlag);

    return returnedNum;
}