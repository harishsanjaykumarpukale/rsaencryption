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

mpint add(mpint , mpint); //adds the integers a and b.
mpint sub(bignum , bignum); //return a - b.
mpint mult(bignum , bignum); //returns the product of a and b.
mpint reminder(bignum , bignum); //returns the remainder of the division of a by n.


mpint expmod(mpint , mpint , mpint);// returns a + b mod n.
mpint addmod(mpint , mpint , mpint);  // returns a * b mod n.
mpint multmod(mpint, mpint, mpint);  //returns ab mod n


#endif
