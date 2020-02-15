#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
	//printf("\n%d\n",x);
        y = lenb>0 ? b.word[--lenb] : 0 ;
	//printf("\n%d\n",y);
        z = (x + y + carry)%10;
	//printf("\n%d\n",z);
        carry = (x+y+carry)/10;
        word[--len] = z;

    }
    word[--len]=carry;

    if (word[0]==0)
    bypass(&word , &size);

    c->word = word;
    c->sign = a.sign;
    c->size = size;
    return *c;
}

void print(mpint c){
    int i , j , k;
    if(c.sign==-1)
    printf("-" );
    if(c.sign==0)
    printf("0");
    for(i = 0 ; i < c.size ; i++)
    printf("%d",c.word[i] );

    printf("\n");
}


mpint str2mpint(char *val){
    mpint *b = (mpint*)malloc(sizeof(mpint));
    int sign;
    int *word;
    int size;

    int curr = 0;

    if (val[0]=='-')
    sign=-1;
    else
    sign=1;

    if(val[0]=='-' || val[0]=='+')
    curr++;

    while(val[curr]=='0' && curr<strlen(val))
    curr++;

    size = strlen(val) - curr;

    if(size==0)
    sign=0;

    word = (int*) malloc(sizeof(int)*size);

    int i , j;
    for(i=0,j=curr ; j<strlen(val) ; i++,j++)
    word[i] = val[j]-'0';

    b->sign = sign;
    b->word = word;
    b->size = size;
    return *b;
}

mpint* createcopy(mpint *x){
    mpint *b = (mpint*)malloc(sizeof(mpint));
    b->sign = x->sign;
    b->size = x->size;
    b->word = (int*)malloc(sizeof(int)*b->size);
    int i;
    for(i = 0 ; i < b->size ; i++)
    b->word[i]=x->word[i];

    return b;
}

mpint mulbyint(mpint a , int x){
    mpint *b = (mpint*)malloc(sizeof(mpint));
    if(x==0){
        b->sign=0;
        b->size=0;
        return *b;
    }

    int *word = (int*)malloc(sizeof(int)*(a.size+1));
    int len = a.size;

    int carry=0 , i ;

    for(i = len ; i>0 ; i--){
        int m = a.word[i-1]*x + carry ;
        carry = m/10;
        m = m%10;
        word[i]=m;
    }

    word[0]=carry;
    b->word=word;
    b->size = a.size+1;
    b->sign = a.sign;
    bypass(&b->word,&b->size);
    return *b;
}

mpint mulby10(mpint a, int times){
    mpint *c = (mpint*)malloc(sizeof(mpint));
    int *word = (int*)malloc(sizeof(int)*(a.size+times));
    int len = a.size+times;
    int i = 0;
    for(i = 0 ; i < a.size ; i++)
    word[i] = a.word[i];

    while(times--)
    word[i++] = 0;

    c->word = word;
    c->size = len;
    c->sign = a.sign;
    return *c;

}


mpint mult(mpint a , mpint b){
    if(a.sign==0)
    return a;
    if(b.sign==0)
    return b;

    mpint c,*x = (mpint*)malloc(sizeof(mpint));
    int i = 0;
    for(i = 0 ; i < b.size ; i++){
        c = mulbyint(a,b.word[i]);
	//print(c);
        c = mulby10(c,b.size-i-1);
	//print(c);
        *x = add(*x,c);
	//print(*x);
    }
    bypass(&x->word, &x->size);
    return *x;

}

void main(){
	int i;
	mpint f,g,h,*x,y;
	f=str2mpint("49200");
	g=str2mpint("3690");
	h=add(g,f);

	printf("\nadd");
	print(h);

	printf("Add checked \n");

	f=str2mpint("00011123");
	bypass(&f.word,&f.size);
	print(f);

	 printf("\nBYpass checked \n");
	if(compareword(f,g)==1)
		printf("\nF is Greater than G \n");
	else
		printf("\nG is Greater than F \n");

	 printf("\nCompare word checked \n");

	 y=str2mpint("12345678");

	 x=createcopy(&y);
	 print(*x);
	 printf("\ncreatecopy checked\n");


	 f=str2mpint("123");
	 g=str2mpint("432");

	 print(f);
	 print(g);
	 y=mult(f,g);
	 print(y);
}


