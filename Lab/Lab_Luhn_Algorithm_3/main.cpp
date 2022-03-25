/* 
 * File:   main.cpp
 * Author: Attila Koksal
 * Purpose:  Lab Luhn Algorithm 3
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //Random Function Library
#include <iomanip>
#include <ctime>     //Time Library
using namespace std;

//Global Constants
enum cardLst {AmEx, Visa, MstrCrd, Disc, All};

//Function Prototypes
char rndDgit();          //Randomly generates digit characters
void prpLuhn(int,int,char[]);       //Prepares the Luhn Sequence
int  cnvrt(char);         //Convert 1 digit char to integer
char cnvrt(int);          //Convert 1 digit integer to a char
void output(char[],int);  //Output the sequence as integers
//Function you are to create
void Luhn(char[],int,int[]);       //Calculate and append the Luhn Digit
int findNum(int[], int);
bool check(char[], char[], int);   //Check validity
void flipNum(char[], int);         //Flip numbers
void transNum(char[], int);        //Transpose numbers

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare int value for number of valid and invalid cards
    int valid = 0, invalid = 0;
    //Initialize values
    int maxSize = 20;
    int cardType = 0;
    int SIZE = 0;
    int finalNum = 0;
    char choice = 'y';
    //Initialize cardArray
    char crdCard[maxSize];
    //Create Int array to add numbers
    int cardInt[maxSize];
    
    //Ask which option they would like to do
    cout << "Would you like to transpose or flip numbers?" << endl;
    cout << "transpose = t" << endl
         << "flip      = f" << endl;
    //Loop to validate user choice
    while(choice != 't' && choice != 'f') {
        cout << "Input: ";
        cin >> choice;
    }
    //Make it a loop
    for(int i = 0; i < 10000; i++) {
        //Create function to make valid card depending on what type of card it is.
        //choose which type of card
        cardType = rand()%5;
        //Set values for card
        if(cardType == AmEx) {
            cout << "American Express Card:" << endl << endl;
            //One more than actual size to account for null
            SIZE = 16;
        }
        else if(cardType == Visa) {
            cout << "Visa Card:" << endl << endl;
            //One more than actual size to account for null
            SIZE = 17;
        }
        else if(cardType == MstrCrd) {
            cout << "Master Card:" << endl << endl;
            //One more than actual size to account for null
            SIZE = 17;
        }
        else if(cardType == Disc) {
            cout << "Discover Card:" << endl << endl;
            //One more than actual size to account for null
            SIZE = 20;
        }
        else if(cardType == All) {
            cout << "Random Card:" << endl << endl;
            //One more than actual size to account for null
            SIZE = rand() % (21 - 16) + 16;
        }
        //Initialize array to 0
        for(int i = 0; i < maxSize; i++) {
            crdCard[i] = 0;
            cardInt[i] = 0;
        }
        //Create card Numbers
        prpLuhn(SIZE-2,cardType,crdCard);
        //using the Luhn Algorithm
        Luhn(crdCard,SIZE,cardInt);
        //Find luhn num
        finalNum = findNum(cardInt,SIZE);
        //Set last num to luhn
        crdCard[SIZE - 2] = finalNum + 48;
        //Output
        cout << "Valid card number:" << endl;
        //Output valid card
        cout << crdCard << endl << endl;
        //initialize for flipped
        char flip[SIZE];
        //Set Equal to valid value
        for(int i = 0; i < SIZE - 1; i++) {
            flip[i] = crdCard[i];
        }
        //IF statement for flip or transpose
        if(choice == 'f') {
            flipNum(flip, SIZE);
            cout << "Random Number Flipped:" << endl;
        }
        else if(choice == 't') {
            transNum(flip, SIZE);
            cout << "Random Number Flipped:" << endl;
        }
        //Output random number flipped
        for(int i = 0; i < SIZE - 1; i++) {
            cout << flip[i];
        }
        cout << endl << endl;
        //count valid and invalid flips
        if(check(crdCard,flip,SIZE)) {
            cout << "Valid" << endl << endl;
            valid++;
        }
        else {
            cout << "Invalid" << endl << endl;
            invalid++;
        }
    }
    //Percentage
    float percV = 0;
    float percI = 0;
    percV = valid*.01;
    percI = invalid*.01;
    //Output results
    cout << "Number of Valid Numbers  : " << valid << endl
         << "Number of Invalid Numbers: " << invalid << endl << endl;
    cout << fixed << setprecision(2) << "Percent of Valids        : " << percV << "%" << endl;
    cout << fixed << setprecision(2) << "Percent of Invalids      : " << percI << "%" << endl;
    //Exit Stage Right
    return 0;
}

void flipNum(char flip[], int SIZE) {
    //Random for switch number position
    int randInd = rand()%SIZE;
    int randInd2 = rand()%SIZE;
    //Loop so not 2 position is chosen
    while(randInd == randInd2){
        randInd2 = rand()%SIZE;
    }
    //Flip a random number
    flip[randInd] = rand()%10 + 48;
    flip[randInd2] = rand()%10 + 48;
}

void transNum(char flip[], int SIZE) {
    //Random for switch number position
    int randInd = rand()%SIZE;
    int randInd2 = 0;
    //Determine where to transpose
    if(randInd <  SIZE - 1 && randInd >= 1){
        randInd2 = randInd - 1;
    }
    else {
        randInd2 = randInd + 1;
    }
    //Temporary value
    int temp;
    //Transpose 2 values
    temp = flip[randInd];
    flip[randInd] = flip[randInd2];
    flip[randInd2] = temp;
}

bool check(char *a, char *b, int SIZE) {
    bool validity = true;
    //Check validity
    for(int i = 0; i < SIZE - 1; i++) {
        if(a[i] == b[i]) {
            validity = true;
        }
        else {
            validity = false;
            return validity;
        }
    }
    //Return
    return validity;
}

int findNum(int *cardInt, int SIZE) {
    int num;
    //Add all numbers together
    for(int i = 0; i < SIZE - 2; i++){
        //Subtract 9 if its over 10
        if(cardInt[i] >= 10) {
            cardInt[i] -= 9;
            num += cardInt[i];
        }
        else {
            num += cardInt[i];
        }
    }
    //take modulus of 10
    num = num%10;
    //Return number
    return num;
}

void Luhn(char crdCard[], int SIZE, int cardInt[]){
    int placeholder = 0;
    //Initialize all to 0
    for(int i = 0; i < SIZE; i++) {
        cardInt[i] = 0;
    }
    //Loop to get int array reversed and doubled
    for(int i = SIZE - 3; i >= 0; i--) {
        //Set placeholder to equal to number value
        placeholder = cnvrt(crdCard[i]);
        //Double number if its odd;
        //Boolean statement is for evens as number count starts at 0
        if(i%2 == 0) {
            //Multiply Placeholder value by 2
            placeholder = placeholder*2;
            //Set i value equal
            cardInt[i] = placeholder;
        }
        else {
            cardInt[i] = placeholder;
        }
    }
}

void output(char cc[],int n){
    cout << "The char array output as each integer digit" << endl;
    for(int i = 0; i < n; i++){
        cout << cnvrt(cc[i]);
    }
    cout << endl << endl;
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

void prpLuhn(int n, int cardType, char cc[]){
    //Change first number depending on what type
    if(cardType == AmEx) {
        cc[0] = 3 + 48;
    }
    else if(cardType == Visa) {
        cc[0] = 4 + 48;
    }
    else if(cardType == MstrCrd) {
        cc[0] = 5 + 48;
    }
    else if(cardType == Disc) {
        cc[0] = 6 + 48;
    }
    else if(cardType == All) {
        cc[0] = (rand() % (7 - 4) + 4) + 48;
    }
    //Create a random cc in prep for Luhn checksum
    for(int i = 1; i < n; i++){
        cc[i] = rndDgit();
    }
    //Put null terminator at the end
    for(int i = n; i <= n + 1; i++){
        cc[i] = '\0';
    }
}

char rndDgit(){
    return rand()%10+'0';//ASCII Code for numbers '0'=48 and '9'=57
    //return rand()%10+48;//ASCII Code for numbers '0'=48 and '9'=57
}