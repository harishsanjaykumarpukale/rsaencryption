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

void assignInt(mpint *n,char c[]){

	int i,num,r=33554432,k=0,j=0,inpSize=strlen(c);
	long int size=( inpSize / 8) + 1;
	char str[9];
	int que[inpSize];

	//strcpy(que,c);

	n->word = (long* ) calloc( 2 * size ,  sizeof(long));

	for(i=0;i<8;i++)
		str[i]=c[i];
	num = atoi(str);

	if(inpSize<8){

		n->word[0]=num;

                return ;
        }

	do {
		for(;i<inpSize;i++){
			que[k++]=num/r;
			num=(num%r)*10 + c[i] -'0';
			}

		que[k++]=num/r;
		que[k++]='\0';

		n->word[j++]=num % r;

		printf("\nbefore c:%s",c);

		printf("\nbefore que:");

		for(k=0;k<inpSize;k++)
			printf("%d",que[k]);

		//strcpy(c,que);

		printf("\nafter c:%s",c);
		printf("\nafter que:");

		for(k=0;k<inpSize;k++)
			printf("%d",que[k]);
		
		inpSize=sizeof(que); //or inpSize=sizeof(c);

		for(i=0;i<inpSize;i++)
			str[i]=c[i];
		
		num = atoi(str);

		printf("\n%d\n",num);

		k=0;
	} while(num>=r);

	n->word[j++]=num;
	n->size=j;

	n->sign='+'; //to be discussed how to set it 
}




#endif
