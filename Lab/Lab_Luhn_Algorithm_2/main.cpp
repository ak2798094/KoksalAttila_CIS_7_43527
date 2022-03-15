/* 
 * File:   main.cpp
 * Author: Attila Koksal
 * Purpose:  Lab Luhn Algorithm 2
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
char *prpLuhn(int,int);       //Prepares the Luhn Sequence
int  cnvrt(char);         //Convert 1 digit char to integer
char cnvrt(int);          //Convert 1 digit integer to a char
void output(char[],int);  //Output the sequence as integers
//Function you are to create
int *Luhn(char*,int);    //Calculate and append the Luhn Digit
int findNum(int*, int);
bool check(char*, char*, int); //Check validity

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare int value for number of valid and invalid cards
    int valid = 0, invalid = 0;
    //Initialize values
    int cardType = 0;
    int SIZE = 0;
    int finalNum = 0;
    int randInd = 0;
    //Make it a loop
    for(int i = 0; i < 10000; i++) {
        //Create function to make valid card depending on what type of card it is.
        //choose which type of card
        cardType = rand()%5;
        //Set values for card
        char *crdCard = new char;
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
        //Create Int array to add numbers
        int *cardInt = new int(SIZE - 2);
        //Create card Numbers
        crdCard = prpLuhn(SIZE-2,cardType);
        //using the Luhn Algorithm
        cardInt = Luhn(crdCard,SIZE);
        //Find luhn num
        finalNum = findNum(cardInt,SIZE);
        //Set last num to luhn
        crdCard[SIZE - 2] = finalNum + 48;
        //Output
        cout << "Valid card number:" << endl;
        //Output valid card
        cout << crdCard << endl << endl;
        //Random for flipp number
        randInd = rand()%SIZE;
        //Allocate memory and initialize
        char *flip = new char(SIZE);
        for(int i = 0; i < SIZE - 1; i++) {
            flip[i] = crdCard[i];
        }
        //Flip a random number
        flip[randInd] = rand()%10 + 48;
        //Output random number flipped
        cout << "Random Number Flipped:" << endl;
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
        //De allocate
        delete [] crdCard;
        delete  cardInt;
        delete [] flip;
    }
    //Percentage
    float perc = 0;
    perc = valid/100;
    //Output results
    cout << "Number of Valid Numbers  : " << valid << endl
         << "Number of Invalid Numbers: " << invalid << endl << endl;
    cout << setprecision(2) << "Percent of validity      : " << perc << "%" << endl;
    //Exit Stage Right
    return 0;
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

int *Luhn(char *crdCard, int SIZE){
    //allocate memory
    int *cardInt = new int(SIZE);
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
    //Return Integer array
    return cardInt;
    //De allocate
    delete []cardInt;
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

char *prpLuhn(int n, int cardType){
    //allocate memory
    char *cc = new char(n);
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
    //Return array
    return cc;
    //Deallocate
    delete []cc;
}

char rndDgit(){
    return rand()%10+'0';//Ascii Code for numbers '0'=48 and '9'=57
    //return rand()%10+48;//Ascii Code for numbers '0'=48 and '9'=57
}