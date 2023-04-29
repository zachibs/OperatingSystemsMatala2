#include "codec.h"

char* encode(char* string, int length){
    for(int i=0; i< length; i++){
        string[i] += 3;
    }
    return string;
}

char* decode(char* string, int length){
    for(int i=0; i< length; i++){
        string[i] -= 3;
    }
    return string;
}