#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[]){
    if (argc <= 2){ 
        printf("Arguements enterd are not sufficient \n");
        return -1;
    }
    int length = 0;
    for(int i=2; i< argc; i++){
        length+= strlen(argv[i])+1;
    }
    char *string = (char*) malloc(sizeof(char)*length);
    if(string == NULL){
        return -1;
    }
    for (int i = 2; i < argc; i++){
        strcat(string, argv[i]);
        if(i!=argc-1){
            strcat(string, " ");
        }
    }
    length--;
    char *libName = argv[1];
    char *libString = "";
    void *dlopenHandler;
    if(!strcmp(libName, "codecA")){
        libString = "./libcodecA.so";
        dlopenHandler = dlopen(libString, RTLD_LAZY);
    }
    else if(!strcmp(libName, "codecB")){
        libString = "./libcodecB.so";
        dlopenHandler = dlopen(libString, RTLD_LAZY);
    }
    else{
        printf("Arguements enterd are not sufficient \n");
        return -1; 
    }
    
    if(dlopenHandler == NULL){
        printf("dlopen failed: \n");
        return -1;
    }
    typedef char *(*sym)(char *, int);
    sym encode = (sym)dlsym(dlopenHandler,"encode");
    char *ret = encode(string, length);
    printf("%s\n", ret);
    free(string);
    dlclose(dlopenHandler);
    return 0;
}