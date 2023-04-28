#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER 256

int copy_func(char* firstFile, char* secondFile, int iFlag) {
    FILE* file1 = fopen(firstFile, "r");
    FILE* file2 = fopen(secondFile, "r");
    if (!(file1 && file2)) { 
        printf("Error occured during file opening\n");
        return -1;
    }

    char firstBuffer[BUFFER];
    char secondBuffer[BUFFER];
    int isNotSame = 0;
    int length = 0;
    while ((fgets(firstBuffer, BUFFER, file1) != NULL) && (fgets(secondBuffer, BUFFER, file2) != NULL) && !isNotSame) {
        if (iFlag) {
            length = strlen(firstBuffer);
            for (int i = 0; i < length; i++) {
                firstBuffer[i] = tolower(firstBuffer[i]);
            }
            length = strlen(secondBuffer);
            for (int i = 0; i < length; i++) {
                secondBuffer[i] = tolower(secondBuffer[i]);
            }
        }
        if (!strcmp(firstBuffer, secondBuffer)) {
            isNotSame = 1;
        }
    }

    if (!((fgets(firstBuffer, BUFFER, file1) == NULL) && (fgets(secondBuffer, BUFFER, secondFile) == NULL))) {
        isNotSame = 1;
    }

    fclose(file1); 
    fclose(file2);

    return isNotSame;

}

int main(int argc, char* argv[]) {
    if (argc <= 2) { 
        printf("Arguements enterd are not sufficient \n");
        return -1;
    }

    int vFlag = 0;
    int iFlag = 0;

    if ((strcmp(argv[3], "-v") == 0) || (strcmp(argv[4], "-v") == 0)) {
        vFlag = 1;
    }

    if ((strcmp(argv[3], "-i") == 0) || (strcmp(argv[4], "-i") == 0)) {
        iFlag = 1;
    }

    int returnedNum = copy_func(argv[1], argv[2], iFlag);

    if (vFlag){
        if (returnedNum){
            printf("Files are distinct\n");
        } else{
            printf("Files are equal\n");
        }
    }

    return returnedNum;
}