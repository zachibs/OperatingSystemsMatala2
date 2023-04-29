#include "codec.h"

char* encode(char* string, int length){
    for(int i=0; i < length; i++){
        if(islower(string[i])){
            string[i] = toupper(string[i]);
        }else if(isupper(string[i])){
            string[i] = tolower(string[i]);
        }
    }
    return string;
}

char* decode(char* string, int length){
    return encode(string, length);
}