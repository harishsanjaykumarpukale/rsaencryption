// RSA library 
#ifndef _RSA_H
#define _RSA_H

typedef struct{
    int size;
    char sign;
    long *word;
} mpint;

mpint newInt(){
    mpint x; //Declaring a variable;
    x.word = NULL; //setting the pointer to NULL
    x.size=0;
    x.sign='\0';
    return x;
}



#endif
