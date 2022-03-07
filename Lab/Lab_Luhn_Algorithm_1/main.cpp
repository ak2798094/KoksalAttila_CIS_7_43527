/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Edited By: Attila Koksal
 * Created on Feb 1st, 2021, 8:35 AM
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //Random Function Library
#include <ctime>     //Time Library
using namespace std;

//Global Constants

//Function Prototypes
char rndDgit();           //Randomly generates digit characters
void prpLuhn(char[],int); //Prepares the Luhn Sequence
int  cnvrt(char);         //Convert 1 digit char to integer
char cnvrt(int);          //Convert 1 digit integer to a char
void output(char[],int);  //Output the sequence as integers
//Function you are to create
void Luhn(char[],int);    //Calculate and append the Luhn Digit

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Set the Credit Card size
    const int SIZE=17;
    char crdCard[SIZE];
    //Prepare for Luhn encoding
    cout<<"A random number created in Prep for Luhn Digit"<<endl;
    prpLuhn(crdCard,SIZE-2);
    
    //Output the preLuhn credit card
    cout<<crdCard<<endl;
    output(crdCard,SIZE-2);
    
    //Now create a function that fills the last digit
    //using the Luhn Algorithm
    Luhn(crdCard,SIZE);
    cout<<"The random number with Luhn Encoding, Output Here!"<<endl;
    cout<<crdCard<<endl;
    
    //Exit Stage Right
    return 0;
}

void Luhn(char ccc[],int n){
    int temp=0;
    int temp2=0;
    int crdTtl=0;
    int luhn=0;
    
    for(int i=0;i<n-2;i++) {
        if (i%2!=0) {
            temp=cnvrt(ccc[i]) * 2;
            
            if(temp>9) {
                temp2=temp%10;
                temp/=10;
                temp+=temp2;
            }

            crdTtl+=temp;
        } else {
            cout<<cnvrt(ccc[i])<<" ";
            crdTtl+=cnvrt(ccc[i]);
        }
    }
    
    
    luhn=crdTtl*9;
    luhn%=100;
    luhn%=10;
    
    ccc[n-2]=cnvrt(luhn);
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