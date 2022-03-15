/* 
 * File:   main.cpp
 * Author: Attila Koksal
 * Purpose: Lab Luhn Algorithm 2
 * Created on March 15, 2022, 2:40 PM
 */

//System Libraries - Post Here
//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //Random Function Library
#include <ctime>     //Time Library
#include <cstring>
using namespace std;

//Global Constants
//Enum       15   34 or 37   16 4  16 5        16 6011
enum CrdCard{AmericanExpress,Visa,MasterCard,Discover,ALL}; // make an if statement if ALL is picked set to randomly pick the other for cards
int valid=0, invalid=0;

//Function Prototypes
char rndDgit();           //Randomly generates digit characters
void prpLuhn(char[],int); //Prepares the Luhn Sequence
int  cnvrt(char);         //Convert 1 digit char to integer
char cnvrt(int);          //Convert 1 digit integer to a char
void output(char[],int);  //Output the sequence as integers
//Function you are to create
bool Luhn(char[],int,int);    //Calculate and append the Luhn Digit
void genCC(CrdCard, char[],int);
void flipDig(char[]);
bool validCC(char[]);


int main(int argc, char** argv) {
    
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Set the Credit Card size
    int SIZE=17;
    char crdCard[SIZE];
    CrdCard CC;
    int num; //counter
    
    for(int i=0; i<10000; i++){
        SIZE=17;
        num=rand()%4;
        if(num==0){
            CC=AmericanExpress;
            SIZE=16;
        }
        else if(num==1){
            CC=Visa;
        }
        else if (num==2){
            CC=MasterCard;
        }
        else if(num==3){
            CC=Discover;
        }
        
        if(CC==ALL){
            num=rand()%3;
            if(num==0){
                CC=AmericanExpress;
                SIZE=16;
            }
            else if(num==1){
                CC=Visa;
            }
            else if (num==2){
                CC=MasterCard;
            }
        }
        
        genCC(CC, crdCard, SIZE-2);
        
    }
    cout<<"Amount of Valid Credit Cards: "<<valid<<endl;
    cout<<"Amount of Invalid Credit Cards: "<<invalid<<endl;

    return 0;
}

// GENERATE CC HERE
void genCC(CrdCard CC, char cc[], int n){
    
    for(int i=0;i<n+1;i++){
        cc[i]=rndDgit();
    }
    int last=cnvrt(cc[n]); // holds last digit in array
 
    for(int i=n;i<=n+1;i++){
        cc[i]='\0';
    }
    
    Luhn(cc, n, last);
    flipDig(cc);

    if(Luhn(cc, n, last)==true){
        validCC(cc);
    }
    else{
        invalid++;
    }
}
void flipDig(char cc[]){
    int length=strlen(cc);
    int num, num2, add;
        
    if(length==15){
        num=rand()%15;
        num2=cnvrt(cc[num]);
        add=num2+1;
        if(add>=9){
            add=9;
        }
        cc[num]=cnvrt(add);
    }
    else if(length==14){
        num=rand()%14;
        num2=cnvrt(cc[num]);
        add=num2+1;   
        if(add>=9){
            add=9;
        }
        cc[num]=cnvrt(add);
//        cout<<"New num"<<cc[num]<<endl;;
    }
//        cout<<"Rand flipped dig "<<cc[num]<<endl;

}
bool validCC(char cc[]){   
        if(cc[0]==6 && cc[1]==0 && cc[2]==1 && cc[3]==1){
            valid++;
        }
        else if(cc[0]=3 && (cc[1]==4 || cc[1]==7)){
            valid++;
        }
        else if(cc[0]=4){
            valid++;
        }
        else if(cc[0]=5){
            valid++;
        }
    
    return valid;
}
bool Luhn(char ccc[],int n,int last){
    int checkSum;
        
    // 1st step is done in the prepLun function
    
//    // 2nd step
    // Use a for loop used to swap each element in the array
    char temp;
    for(int i=0, j=n-1; i<=6; i++,j--){ 
        temp=ccc[i];
        ccc[i]=ccc[j];
        ccc[j]=temp;
//        cout<<ccc[i];
    }

    // 3rd step
    // multiply every odd element and subtract 9 to all any result higher than 9
    int num;
    int sum=0;
    
    for(int i=0; i<=n-1 ;i++){
        
        num=cnvrt(ccc[i]);
       
        
        if(i%2==0){
            num=num*2;
            if(num>9){
                num=num-9;
                ccc[i]=cnvrt(num);
            }
            ccc[i]=cnvrt(num);
        }       
        
        ccc[i]=cnvrt(num);
//        cout<<ccc[i]<<endl;
        sum+=num;
    }
//    cout<<endl<<"Luhn Output step 3"<<endl;
//    cout<<ccc<<endl;
    
    //  last step   
    checkSum=sum%10;
    // put the last steps here
//    int count=0;
    bool credit=false;
    if(checkSum==last){
        credit==true;
        return true;
    }
    return false;
//    cout<<count<<endl; 
    
}
void output(char cc[],int n){
    cout<<"The char array output as each integer digit"<<endl;
    for(int i=0;i<n;i++){
        cout<<cnvrt(cc[i]);
    }
    cout<<endl;
}
char  cnvrt(int digit){
    if(digit<0||digit>9){
        cout<<"You don't know what you are doing"<<endl;
        exit(0);
    }
    return digit+'0';
    return digit+48;
}
int  cnvrt(char digit){
    if(digit<'0'||digit>'9'){
        cout<<"You don't know what you are doing"<<endl;
        exit(0);
    }
    return digit-'0';
}
void prpLuhn(char cc[],int n){
    //Create a random cc in prep for Luhn checksum
    for(int i=0;i<n;i++){
        cc[i]=rndDgit();
    }

    //Put null terminator at the end
    for(int i=n;i<=n+1;i++){
        cc[i]='\0';
    }
}
char rndDgit(){
    return rand()%10+'0';//Ascii Code for numbers '0'=48 and '9'=57
    //return rand()%10+48;//Ascii Code for numbers '0'=48 and '9'=57
}