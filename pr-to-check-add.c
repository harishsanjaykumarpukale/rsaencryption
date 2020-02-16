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


mpint subnum(mpint a , int l){
    mpint *c = (mpint*)malloc(sizeof(mpint));
    c->size = l;
    c->sign = a.sign;
    c->word = (int*) malloc(sizeof(int)*l);
    int i;
    for(i = 0 ; i < l ; i++)
    c->word[i] = a.word[i];
    return *c;
}

mpint reminder(mpint a , mpint b){


    if(b.sign==0)
    {
        printf("Exception case of 0 divisorn");
        exit(0);
    }
    if(a.sign==0)
    {
        return a;
    }

    if (compareword(a,b)==-1){

        return a;
    }
    if(compareword(a,b)==0){

        mpint *c = (mpint*)malloc(sizeof(mpint));
        c->size=0;
        c->sign =  0 ;

        return *c;
    }

    int len = b.size;

    mpint t=  subnum(a,len);
    while(compareword(t,b)==-1){
        len++;
        t = subnum(a,len);
    }
    int appendzeroes = a.size - len ;
    t = mulby10(b , appendzeroes);
    a = sub(a,t);
    return reminder(a,b);
}

mpint multmod(mpint a, mpint b, mpint n){
    return reminder(mult(a,b),n);
}


void copy(mpint *to , mpint *from){
    to->size = from->size;
    to->sign = from->sign;
    free(to->word);
    to->word = (int*)malloc(sizeof(int)*to->size);
    int i;
    for(i = 0 ; i < to->size ; i++)
    to->word[i] = from->word[i];

}

mpint divby2(mpint a){
    mpint *c = (mpint*)malloc(sizeof(mpint));

    int len = a.size;
    int *word = (int*)malloc(sizeof(int)*len);
    int sign = a.sign;
    int carry = 0;
    int i;
    for(i = 0 ; i < len ; i++){
        int x = carry*10 + a.word[i];
        int v = x/2;
        carry = x%2;
        word[i]=v;
    }
    c->word = word;
    c->sign = sign;
    c->size = len;
    bypass(&c->word , &c->size);
    return *c;
}


mpint divident(mpint divisor , mpint div ){

    mpint l = str2mpint("1");
    mpint h = *createcopy(&divisor);
    mpint rem = reminder(divisor , div);
    divisor = sub(divisor,rem);
    mpint ONE = str2mpint("1");

    while(1){
        mpint mid = divby2(add(l,h));
        mpint tmp = mult(div , mid);
        int cmp = compareword( divisor , tmp ) ;
        if (cmp==0)
        return mid;
        else if ( cmp == 1)
        l = add(mid,ONE);
        else
        h = sub(mid,ONE);
    }

}

mpint inverse(mpint a , mpint n){
    mpint ONE = str2mpint("1");
    mpint ZERO = str2mpint("0");
    mpint t = str2mpint("0");
    mpint newt = str2mpint("1");
    mpint newn = *createcopy(&n);
    mpint newa = *createcopy(&a);

    mpint p_i_2 = str2mpint("0");
    mpint p_i_1 = str2mpint("1");
    do{
        mpint q_i_2 = divident(newn , newa);
        mpint rem = reminder(newn , newa);
        mpint p = sub(p_i_2 , reminder( mult(p_i_1,q_i_2), n));
        if(p.sign==-1){
            p.sign = 1;
            mpint tmp = sub( n , p);
            copy(&p , &tmp);

        }

        copy(&p_i_2 ,&p_i_1 );
        copy(&p_i_1 , &p );
        copy(&newn ,&newa );
        copy(&newa , &rem);
        if(compareword(rem,ONE)==0)
        return p;
    }while(1);
}

long long int to_int(mpint b){
    long long int sum = 0;
    int i ;
    for (i = 0; i < b.size ; ++i)
    {
        sum = sum*10 + b.word[i] ;
    }
    return sum;
}

int mod2(mpint a){

    int len = a.size;
    int sign = a.sign;
    int carry = 0;
    int i;
    for(i = 0 ; i < len ; i++){
        int x = carry*10 + a.word[i];
        carry = x%2;
    }
    return carry;
}

mpint expmod(mpint m , mpint e , mpint n){
    mpint ZERO = str2mpint("0");
    mpint ONE = str2mpint("1");

    if(compareword(e,ONE)==0)
    return m;
    if(compareword(e,ZERO)==0)
    return ONE;

    int r = mod2(e);
    e = divby2(e);

    mpint tmp = expmod(m , e , n);
    tmp = multmod(tmp,tmp,n);

    if(r==1)
    tmp = multmod(tmp,m,n);
    return tmp;
}



mpint genrandom(int bits){

    mpint TWO = str2mpint("2");
    mpint ONE = str2mpint("1");
    mpint ZERO = str2mpint("0");
    mpint pow2 = str2mpint("0");

    mpint sum = str2mpint("0");
    while(bits--)
    {
        int bit = rand()%2;

        if(compareword(pow2,ZERO)==0)
        pow2=ONE;

        else if(compareword(pow2,ONE)==0)
        pow2=TWO;

        else pow2 = mult(pow2,TWO);


        if(bit==1){
            sum = add(sum , pow2);
        }

    }
    return sum;
}



int millerrabin(mpint p, int it){

    mpint TWO = str2mpint("2");
    mpint ONE = str2mpint("1");

    if(compareword(p, TWO)==-1)
    return 0;

    if( ( compareword(p,TWO)==0 ) || ( mod2(p)==0 ) )
    return 0;

    mpint d = sub(p,ONE);
    int s=0;
    while(mod2(d)==0){
        d = divby2(d);
        s++;
    }

    witnessloop: do{
        mpint a = add(reminder( genrandom(100) , sub(p,str2mpint("4")) ), TWO);
        mpint x = expmod(a , d , p);
        if( (compareword(x , ONE)==0) || ( compareword(x, sub(p,ONE))==0 ))
        continue;
        int i;
        for(i = 0 ; i < s-1 ; i++){
            x = multmod(x,x,p);
            if(compareword(x,ONE)==0)
            return 0;
            if(compareword(x,sub(p,ONE))==0)
            goto witnessloop;
        }
        return 0;

    }while(it--);
    return 1;
}


mpint genrandomprime(int len){
    mpint PRIME_PRODUCT = str2mpint("152125131763605");
    mpint ONE = str2mpint("1");
    mpint TWO = str2mpint("2");
    mpint ran = genrandom(len);

    if(mod2(ran)==0)
    ran = add(ran,ONE);

    while(1){
        mpint rem = reminder(ran ,PRIME_PRODUCT);
        long long int r = to_int(rem);
        if ((r%3==0)  || (r%5==0)  || (r%7==0)  || (r%11==0) ||
        (r%13==0) || (r%17==0) || (r%19==0) || (r%23==0) ||
        (r%29==0) || (r%31==0) || (r%37==0) || (r%41==0)) {

            ran = add(ran , TWO);
            continue;
        }
        if(millerrabin(ran,2)==1)
        return ran;

        ran = add(ran,PRIME_PRODUCT);

    }
    return ran;
}


mpint append(mpint b , int x){

    int *word = (int*)malloc(sizeof(int)*(b.size+1));
    int i;
    for(i = 0 ; i < b.size ; i++)
    word[i] = b.word[i];
    word[i] = x;
    b.size++;
    free(b.word);
    b.word = word;
    return b;

}

mpint RSADecrypt(mpint c , mpint d , mpint n){
    return expmod(c , d, n);
}

mpint RSAEncrypt(mpint m , mpint e , mpint n){
    return expmod(m , e, n);
}


int coprime(mpint a , mpint b){
    while(b.sign!=0){
        mpint t = b;
        b = reminder(a,b);
        a = t;
    }
    mpint ONE = str2mpint("1");
    if (compareword(a,ONE)==0)
    return 1;
    else
    return 0;
}


void keygen(mpint *n,mpint *e, mpint *d,int size){
    mpint ONE = str2mpint("1");
    mpint p = genrandomprime(size/2);
    mpint q = genrandomprime(size/2);
    *n = mult(p,q);
    mpint phi = mult(sub(p,ONE), sub(q,ONE));
    do{
        *e = reminder(genrandom(256),phi);
    }while( coprime (phi,*e)!=1);
    *d = inverse(*e , phi);

}

void testRSA(int size){
    mpint n , e , d ;
    printf("generating primes P and Qn");
    keygen(&n , &e , &d, size);
    //n=str2mpint("33");
    //e=str2mpint("7");
    //d=str2mpint("1");

    printf("\nValue of public key (e , n ) \n");
    print(e);
    print(n);
    printf("\nValue of Private key ( d , n ) \n");
    print(d);
    print(n);

    //mpint message = reminder(genrandom(512),n);
    mpint message = str2mpint("89");

    printf("\nRandom generated messege \n");
    print(message);

    mpint cipher=RSAEncrypt(message , e , n);
    printf("\nCipher text \n");
    print(cipher);

    message = RSADecrypt(cipher , d , n);
    printf("\nCipher Decrypted\n");
    print(message);
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

	 f=str2mpint("123456");
	 g=str2mpint("654321");

	 y=str2mpint("23");

	 h=multmod(f,g,y);

	 print(h);


	 f=str2mpint("5");
         g=str2mpint("47");

	 h=inverse(f,g);
	 print(h);

	 h=genrandomprime(100);
	 print(h);

	 i=123;
	 f=str2mpint("4567330999");
	 h=append(f,i);
	 print(h);


	 f=str2mpint("47");
	 g=str2mpint("78");
	 h=str2mpint("23");

	 y=expmod(f,g,h);
	 print(y);

	 f=str2mpint("3057601");
	 i=99908;
	 i=millerrabin(f,i);
	 printf("\n%d\n \n TEst function caliing\n",i);


	 testRSA(512);


}


