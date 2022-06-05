/*
    Author: Attila Koksal
    Purpose: Mastermind AI Project 2
    Date: June 1st, 2022
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

//Function Prototypes
string AI(char,char);
bool eval(string,string,char &,char &);
string set();

int main(int argc, char** argv) {
    //Set random number seed generator
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    string code,guess;  //code breaker and holds the current guess
    char rr,rw;         //right digit in correct place and right digit in incorrect place
    int nGuess;         //number of guesses
    
    //Initialize Values
    nGuess=0;
    code=set();
    rr=rw=0;
    
    //Loop until code is solved and keep track of the number of guesses used to find the final solution
    do{
       nGuess++;
       guess=AI(rr,rw);
    }while(eval(code,guess,rr,rw)&&nGuess<100);

    //Exit the program
    return 0;
}

string AI(char rr,char rw){
    static const int ARRSIZE = 10;
    static const int GSIZE   = 4;
    
    static bool firstTime = true;
    static bool allFour   = false;
    static bool aiFirst   = true;
    static bool foundFir  = false;
    static bool foundSec  = false;
    static bool foundThr  = false;
    static bool foundFou  = false;
    
    static char cArray[] = {0,0,0,0,0,0,0,0,0,0};
    static char cGuess[] = {0,0,0,0};//Holds the correct digit out of order
    
    static int index = 0;
    static char n = 0;//cGuess Index
    static char m = 0;//cCode Index
    static char p = 0;//sGuess Index
    
    int sum = 0;
    
    string sGuess = "xxxx";
    static string cCode = "xxxx";
    
    
    // Determine which values are correct
    if(index <= ARRSIZE && !allFour){
        
        if(firstTime){
            sGuess = "0000";
            index++;

            firstTime = false;
        }

        else if(!firstTime){
            // Check previous value to see if its one of the numbers
            // if rr is not equal to 0, then the previous value is correct
            if(rr!=0){
                cArray[index-1]=rr;
            }
            
            for(int i=0;i<ARRSIZE;i++){
                sum += (int)cArray[i];
            }
            if(sum!=4){
                for(int i=0;i<GSIZE;i++){
                    sGuess[i] = index + '0';
                }
            }
            else if(sum==4){
                allFour = true;
            }
            index++;
        }
        
        if(allFour){
            for(int i=0;i<ARRSIZE;i++){
                if(cArray[i]!=0){
                    for(int j=0;j<(int)cArray[i];j++){
                        cGuess[n++]= i;
                    }
                }
            }
        }
    }
    else{
        if(aiFirst){
            n=0;
            m=0;
            p=0;
            //Find the first number
            //Set the first index of cGuess to the first index of sGuess
            sGuess[p] = cGuess[n]  + '0';
            aiFirst=false;
        }
        
        else if(aiFirst==false){
            
            if(foundFir==false){
                if(rr==1){
                    //Keep the first digit in the first position of cCode
                    cCode[m]=cGuess[n++] + '0';

                    foundFir = true;
                    if(cCode[0]=='x'){
                        m=p=0;
                    }
                    else if(cCode[0]!='x'){
                        m=p=1;
                    }
                    sGuess[p] = cGuess[n] + '0';
                }
                else if(rr==0){
                    m++;
                    sGuess[++p]=cGuess[n] + '0';
                }
            }
            
            else if(foundFir==true && foundSec==false){
                //After finding the first digit, find the second digit
                if(rr==1){
                    cCode[m++]=cGuess[n++] + '0';

                    foundSec = true;
                    if(cCode[0]=='x'){
                        m=p=0;
                    }
                    else if(cCode[0]!='x' && cCode[1]=='x'){
                        m=p=1;
                    }
                    else if(cCode[0]!='x' && cCode[1]!='x' && cCode[2]=='x'){
                        m=p=2;
                    }
                    sGuess[p] = cGuess[n] + '0';
                }
                
                else if (rr==0){
                    if(cCode[m+1]=='x'){
                        sGuess[++p]= cGuess[n] + '0';
                        
                        m++;
                    }
                    else if(cCode[m+1]!='x'){
                        p+=2;
                        m+=2;
                        sGuess[p]=cGuess[n] + '0';
                    }
                }
            }
            
            else if(foundFir==true && foundSec==true && foundThr==false){
                if(rr==1){
                    cCode[m++]=cGuess[n++] + '0';
                    
                    foundThr=true;
                    if(cCode[0]=='x'){
                        m=p=0;
                    }
                    else if(cCode[0]!='x' && cCode[1]=='x'){
                        m=p=1;
                    }
                    else if(cCode[0]!='x' && cCode[1]!='x' && cCode[2]=='x'){
                        m=p=2;
                    }
                    else if(cCode[0]!='x' && cCode[1]!='x' && cCode[2]!='x'){
                        m=p=3;
                    }
                    sGuess[p] = cGuess[n] + '0';
                }
                
                else if(rr==0){
                    if(cCode[m+1]=='x'){
                        m++;
                        p++;
                    }
                    else if(cCode[m+1]!='x' && cCode[m+2]=='x'){
                        m+=2;
                        p+=2;
                    }
                    else if(cCode[m+1]!='x' && cCode[m+2]!='x' && cCode[m+3]=='x'){
                        m+=3;
                        p+=3;
                        
                    }
                    sGuess[p]=cGuess[n] + '0';
                }
                if(foundThr==true){
                    //Find the last digit by finding the position that's not found within cCode
                    for(int i=0;i<GSIZE;i++){
                        if(cCode[i]=='x'){
                            cCode[i] = cGuess[n] + '0';
                            sGuess = cCode;
                            break;
                        }
                    }
                }
            }
        }
    }
    return sGuess;
}

bool eval(string code,string guess,char &rr,char &rw){
    string check="    ";
    rr=0,rw=0;
    //Check how many digits are in the correct place
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            rr++;
            check[i]='x';
            guess[i]='x';
        }
    }
    //Check how many digits are in the incorrect place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                rw++;
                check[i]='x';
                break;
            }
        }
    }
    
    //Is the code broken or not
    if(rr==4)return false;
    return true;
}

string set(){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%10+'0';
    }
    return code;
}