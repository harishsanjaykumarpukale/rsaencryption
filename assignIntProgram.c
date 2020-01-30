#include <stdio.h>
#include <string.h>


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

void quotient(char *q, int *index, int n){
  while (n>0){
    *(q + *(index))=n%10;
    n/=10;
    (*index)++;
    
  }
  
}
void assignInt(mpint *n,char c[]){

  int i,num,r=33554432,k=0,j=0,inpSize=strlen(c);
  long int size=( inpSize / 8) + 1;
  char str[9];
  char que[inpSize];

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
      quotient(&que[0],&k,num/r);
      num=(num%r)*10 + c[i] -'0';
      }

    quotient(&que[0],&k,num/r);
    que[k++]='\0';

    n->word[j++]=num % r;

    printf("\nbefore c:%s",c);
    
    printf("\nbefore que:");

    for(k=0;k<inpSize;k++)
      printf("%c",que[k]);

    strcpy(c,que);

    printf("\nafter c:%s",c);
    printf("\nafter que:");

    for(k=0;k<inpSize;k++)
      printf("%c",que[k]);
    
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

//Compiler version gcc  6.3.0

int main()
{
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
