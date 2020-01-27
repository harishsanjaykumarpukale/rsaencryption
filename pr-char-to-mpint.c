#include<stdio.h>
#include "rsa.h"

void main(){
	int i;
	char p_arr[50],q_arr[50];
	mpint p,q;//two prime numbers

	p=newInt();
	q=newInt();

	printf("\nEnter the first prime number :");
	scanf("%[^\n]s",p_arr);


	assignInt(&p,p_arr);

	for(i=p.size-1;i>=0;i--)
		printf("%ld R\t",p.word[i]);
}

