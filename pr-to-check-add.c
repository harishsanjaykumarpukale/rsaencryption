#include<stdio.h>
#include<stdlib.h>

typedef struct s2
{
    int sign;
    int *word;
    int size;
} mpint;

mpint add(mpint a , mpint b);
int max(int x , int y){
    return x > y ? x : y ;
}
void bypass(int **wordg , int *len){
    int curr  = 0;
    int size = *len;
    int *word = *wordg;
    while(curr<size && word[curr]==0)
    curr++;

    int i ;
    for(i = 0 ; (i+curr) < size ; i++ )
    word[i] = word[curr+i];

    size = size - curr;
    *len = size;
    *wordg = word;

}

int compareword(mpint a , mpint b){
    if(a.sign==0 && b.sign==0)
    return 0;

    if(a.size > b.size)
    return 1;
    if(b.size > a.size)
    return -1;

    int i = 0;
    for(i = 0 ; i < a.size ; i++)
    {
        if (a.word[i] > b.word[i])
        return 1;
        if (a.word[i] < b.word[i])
        return -1;

    }
    return 0;
}



mpint sub(mpint a , mpint b){

    if(b.sign==0)
    return a;

    b.sign = b.sign == -1 ? 1:-1 ;

    if(a.sign==0){
        return b;
    }

    if(a.sign==b.sign){
        return add(a,b);
    }

    mpint *c = (mpint*) malloc (sizeof(mpint));
    int size = 0;
    int *word ;
    int sign = 0;
    if(compareword(a,b)==0){
        c->sign=0;
        c->word = word;
        c->size=0;
        return *c;
    }

    mpint x , y ;
    x = compareword(a,b)==1 ? a:b;
    y = compareword(a,b)==1 ? b:a;
    size = max(a.size , b.size);
    word = (int*)malloc(sizeof(int)*size);
    int len = size;

    int lenx = x.size;
    int leny = y.size;

    int borrow = 0;
    while(lenx>0 || leny>0){
        int a = lenx>0 ? x.word[--lenx] : 0;
        int b = leny>0 ? y.word[--leny] : 0;
        int c;
        if ( (a-borrow-b)>=0 ){
            c = (a-borrow-b); borrow=0;
        }
        else{
            c = 10+(a-borrow-b) ; 
	    borrow=1;
        }


        word[--len] = c;
    }
    c->word = word;
    c->size = size;
    c->sign = x.sign;
    if(c->word[0]==0)
	    bypass(&c->word, &c->size);
    return *c;
}


mpint add(mpint a , mpint b){
    if(b.sign==0)
    return a;
    if(a.sign==0)
    return b;

    if(a.sign!=b.sign)
    return sub(a,b);

    int maxlen = max(a.size , b.size);
    int lena = a.size;
    int lenb = b.size;
    mpint *c = (mpint*)malloc(sizeof(mpint));
    int sign,x,y,z;
    int *word;
    int size = maxlen+1;
    word = (int*)malloc(sizeof(int)*size);

    int carry = 0, len=size;
    while (lena>0 || lenb>0){

        x = lena>0 ? a.word[--lena] : 0 ;
        y = lenb>0 ? b.word[--lenb] : 0 ;
        z = (x + y + carry)%10;
        carry = z/10;
        word[--len] = z%10;

    }
    word[--len]=carry;

    if (word[0]==0)
    bypass(&word , &size);

    c->word = word;
    c->sign = a.sign;
    c->size = size;
    return *c;
}


void main(){
	int i;
	mpint f,g,h;
	f.sign=1;
	f.size=1;
	f.word = (int*)malloc(sizeof(int));
	f.word[0]=112233;

	g.sign=1;
	g.size=1;
	g.word = (int*)malloc(sizeof(int));
	g.word[0]=220000;

	h=add(g,f);
	printf("Addition of %d and %d is :",g.word[0],f.word[0]);

	for(i=0;i<h.size;i++)
		printf("%d",h.word[i]);
}


