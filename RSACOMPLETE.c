#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct s2
{
    int sign;
    int *word;
    int size;
} mpint;

int max(int , int);  
mpint add(mpint , mpint);  // checked
void bypass(int** , int*);
int compareword(mpint , mpint);
mpint *createcopy(mpint *);
mpint str2mpint(char *val);
mpint sub(mpint , mpint);  
mpint mult(mpint , mpint);
mpint mulbyint(mpint , int);
mpint mulby10(mpint , int);
int millerrabin(mpint p, int it);
long long int to_int(mpint b);
mpint reminder(mpint , mpint); 
mpint append(mpint , int);
mpint subnum(mpint , int );
mpint addmod(mpint , mpint , mpint);
mpint multmod(mpint, mpint, mpint);
mpint divby2(mpint);
mpint divident(mpint divisor , mpint div );
int mod2(mpint a);
mpint expmod(mpint , mpint , mpint);
mpint genrandom(int);
mpint genrandomprime(int len);
int coprime(mpint a , mpint b);
void keygen(mpint *n,mpint *e, mpint *d,int size);
mpint inverse(mpint , mpint);
void copy(mpint* , mpint*); 
void print(mpint );  // checked

mpint RSAEncrypt(mpint m , mpint e , mpint n);
mpint RSADecrypt(mpint c , mpint d , mpint n);
void testRSA(int size);

/**
* This method is used to find maximum number between two integers.
* @param x This is the first paramter to max method
* @param y  This is the second parameter to max method
* @return int This returns maximum of x and y.
*/

int max(int x , int y){
    return x > y ? x : y ;
}

/**
* This method is used to remove preindexed zero from number.
* @param word This is the first paramter to bypass method
* @param len This is the second parameter to bypass method
* @return void This function just removes leading zero from number.
* like 0045454 to 45454
*/

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

/**
* This method is used to compare two mpint variable.
* @param a This is the first paramter to compareword method
* @param b This is the second parameter to compareword method
* @return int This function compare two mpint variable according to the sign of the variable and return 0,1,-1
* @return 0:- if both the variable is having sign 0
* @return 1:- if a is greater than b
* @return -1:- if a is less than b
*/

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

/**
* This method is used to create copy of one mpint variable to another mpint variable.
* @param x This is the first paramter to createcopy method
* @return mpint This function creates copy of variable
*/

mpint *createcopy(mpint *x){
    mpint *b = (mpint*)malloc(sizeof(mpint));
    b->sign = x->sign;
    b->size = x->size;
    b->word = (int*)malloc(sizeof(int)*b->size);
    int i;
    for(i = 0 ; i < b->size ; i++)
    b->word[i]=x->word[i];
    
    return b;
}

/**
* This method is used to create structure variable according to the passed value.
* @param val This is the first paramter to create method
* @return mpint This function creates structure variable according to the sign of passed value and converts character to integer
*/
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

/**
* This method is used to add two structure variable according to the sign of the variable.
* @param a This is the first paramter to add method
* @param b This is the second paramter to add method
* @return mpint This function is used to add two structure variable according to the sign.
*/

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
    int sign;
    int *word;
    int size = maxlen+1;
    word = (int*)malloc(sizeof(int)*size);
    
    int carry = 0, len=size;
    while (lena>0 || lenb>0){
        
        int x = lena>0 ? a.word[--lena] : 0 ;
        int y = lenb>0 ? b.word[--lenb] : 0 ;
        int z = (x + y + carry)%10;
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

/**
* This method is used to substract two structure variable according to the sign of the variable.
* @param a This is the first paramter to sub method
* @param b This is the second paramter to sub method
* @return mpint This function is used to substract two structure variable according to the sign.
*/
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
            c = 10+(a-borrow-b) ; borrow=1;
        }
        
        word[--len] = c;
    }
    c->word = word;
    c->size = size;
    c->sign = x.sign;
    bypass(&c->word, &c->size);
    return *c;
}

/**
* This method is used to multiply structure variable with 10 based on the times.
* @param a This is the first paramter to mulby10 method
* @param times This is the second paramter to mulby10 method
* @return mpint This function is used to multiply structure variable by 10 according to the times.
* @like a=18 and times =2 result= 1800
*/
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

/**
* This method is used to multiply structure variable with integer variable.
* @param a This is the first paramter to mulbyint method
* @param x This is the second paramter to mulbyint method
* @return mpint This function is used to multiply structure variable by passed integer variable.
*/

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

/**
* This method is used to multiply two structure variable.
* @param a This is the first paramter to mul method
* @param b This is the second paramter to mul method
* @return mpint This function is used to multiply two structure variable.
*/
mpint mult(mpint a , mpint b){
    if(a.sign==0)
    return a;
    if(b.sign==0)
    return b;
    
    mpint *x = (mpint*)malloc(sizeof(mpint));
    int i = 0;
    for(i = 0 ; i < b.size ; i++){
        mpint c = mulbyint(a,b.word[i]);
        c = mulby10(c,b.size-i-1);
        *x = add(*x,c);
    }
    bypass(&x->word, &x->size);
    return *x;
    
}

/**
* This method is used to append one integer value to structure variable.
* @param b This is the first paramter to append method
* @param x This is the second paramter to append method
* @return mpint This function is used to append integer value to mpint variable.
*/
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

/**
* This method is used to keep l size value in mpint variable.
* @param a This is the first paramter to subnum method
* @param l This is the second paramter to subnum method
* @return mpint here in this function l is the size which we have to keep in mpint variable
*  and the remaining part we have to remove from mpint.
*/
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

/**
* This method is used to get divident from mpint divisor and mpint div
* @param divisor This is the first paramter to divident method
* @param div This is the second paramter to divident method
* @return mpint this function used to divide two mpint variable
*/
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

/**
* This method is used to get reminder from mpint
* @param a This is the first paramter to reminder method
* @param b This is the second paramter to reminder method
* @return mpint this function used to get reminder from two mpint variable
*/

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

/**
* This method is used to divide mpint by 2
* @param a This is the first paramter to reminder method
* @return mpint this function used to divide mpint by 2
*/
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

/**
* This method is used to get mod of mpint by 2
* @param a This is the first paramter to mod2 method
* @return int this function used to get mod of 2 of a mpint variable
*/
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

/**
* This method is used to get m^e mod n
* @param m This is the first paramter to expmod method
* @param e This is the second paramter to expmod method
* @param n This is the third paramter to expmod method
* @return mpint this function used to get exponent mod by the efficient way
*/
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


/**
* This method is used to generate random number based on bits size
* @param bits This is the first paramter to genrandom method
* @return mpint this function used to generate random number based on bit size.
*/
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

/**
* This method is used to return 0 or 1 based on the mpint p is prime or not
* @param p This is the first paramter to millerrabin method
* @param it This is the second paramter to millerrabin method
* @return int from this function checking the mpint p is prime or not according to the it which is the accuracy of the test
*/
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

/**
* This method is used to convert mpint variable to long long integer
* @param b This is the first paramter to to_int method
* @return long long int from this function just converting mpint variable to long int
*/
long long int to_int(mpint b){
    long long int sum = 0;
    int i ;
    for (i = 0; i < b.size ; ++i)
    {
        sum = sum*10 + b.word[i] ;
    }
    return sum;
}

/**
* @param len This is the first paramter to genrandomprime method
* @return mpint this function is used to generate random prime number based on the given size
*/
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

/**
* This method is used to generate addition mod (a+b mod n)
* @param a This is the first paramter to addmod method
* @param b This is the second paramter to addmod method
* @param n This is the third paramter to addmod method
* @return mpint
*/
mpint addmod(mpint a , mpint b , mpint n)
{
    return reminder(add(a,b),n);
}

/**
* This method is used to generate multiplication mod (a*b mod n)
* @param a This is the first paramter to multmod method
* @param b This is the second paramter to multmod method
* @param n This is the third paramter to multmod method
* @return mpint
*/
mpint multmod(mpint a, mpint b, mpint n){
    return reminder(mult(a,b),n);
}

/**
* print method to print any mpint variable
* @param c This is the first paramter to print method
* @return void
*/
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

/**
* This method is used to get co-prime of two mpint variable
* @param a This is the first paramter to multmod method
* @param b This is the second paramter to multmod method
* @return int either 0 or 1
*/
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

/**
* This method is used to generate key which is being used by the rsa algorith.
* @param n This is the first paramter to keygen method
* @param e This is the second paramter to keygen method
* @param d This is the third paramter to keygen method
* @param size This is the fourth paramter to keygen method
* @return void
*/
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

/**
* This method is used to copy one mpint to another mpint
* @param to This is the first paramter to copy method
* @param from This is the second paramter to copy method
* @return void
*/
void copy(mpint *to , mpint *from){
    to->size = from->size;
    to->sign = from->sign;
    free(to->word);
    to->word = (int*)malloc(sizeof(int)*to->size);
    int i;
    for(i = 0 ; i < to->size ; i++)
    to->word[i] = from->word[i];
    
}

/**
* This method is used to inverse of a such that a * inverse(a) = 1 mod(n)
* @param a This is the first paramter to inverse method
* @param n This is the second paramter to inverse method
* @return mpint
*/
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

/**
* This method is used encrypt the data
* @param m This is the first paramter to RSAEncrypt method
* @param e This is the second paramter to RSAEncrypt method
* @param n This is the third paramter to RSAEncrypt method
* @return mpint
*/
mpint RSAEncrypt(mpint m , mpint e , mpint n){
    return expmod(m , e, n);
}

/**
* This method is used decrypt the data
* @param c This is the first paramter to RSADecrypt method
* @param d This is the second paramter to RSADecrypt method
* @param n This is the third paramter to RSADecrypt method
* @return mpint
*/
mpint RSADecrypt(mpint c , mpint d , mpint n){
    return expmod(c , d, n);
}


/**
* testRSA is used to generate public and private key and then generating the random message
* and then encrypt and decrypt that generated random message
* @param size This is the first paramter to testRSA method
* @return void
*/

void testRSA(int size){
    mpint n , e , d ;
    printf("generating primes P and Qn");
    keygen(&n , &e , &d, size);
    
    printf("nnValue of public key (e , n ) n");
    print(e);
    print(n);
    printf("nnValue of Private key ( d , n ) n");
    print(d);
    print(n);
    
    //mpint message = reminder(genrandom(512),n);
    mpint message = str2mpint("123456789");
    
    printf("nnRandom generated messege n");
    print(message);
    
    mpint cipher=RSAEncrypt(message , e , n);
    printf("nnCipher text n");
    print(cipher);
    
    message = RSADecrypt(cipher , d , n);
    printf("nnCipher Decryptedn");
    print(message);
}

// main function to call the above utility functions.

int main(){
    testRSA(512);
    
    return 0;
}

