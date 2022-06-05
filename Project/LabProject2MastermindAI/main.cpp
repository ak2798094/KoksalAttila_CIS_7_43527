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
string compAI(char,char);
bool calculate(string,string,char &,char &);
string solution();

int main(int argc, char** argv) {
    //Set random number seed generator
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    string code,guess;  //code breaker and holds the current guess
    char correct,wrong; //right digit in correct place and right digit in incorrect place
    int numGuess;         //number of guesses
    
    //Initialize Values
    numGuess=0;
    code=set();
    correct=0;
    wrong=0;
    
    //Loop until code is solved and keep track of the number of guesses used to find the final solution
    do{
       numGuess++;
       guess=compAI(correct,wrong);
    }while(calculate(code,guess,correct,wrong)&&numGuess<100);

    //Exit the program
    return 0;
}

string compAI(char correct,char wrong){
    static const int arrSize = 10;
    static const int gSize = 4;
    
    static bool firstTime = true;
    static bool allFour = false;
    static bool aiFirst = true;
    static bool foundFir = false;
    static bool foundSec = false;
    static bool foundThr = false;
    static bool foundFou = false;
    
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
    if(index <= arrSize && !allFour){
        
        if(firstTime){
            sGuess = "0000";
            index++;

            firstTime = false;
        }

        else if(!firstTime){
            // Check previous value to see if its one of the numbers
            // if correct is not equal to 0, then the previous value is correct
            if(correct!=0){
                cArray[index-1]=correct;
            }
            
            for(int i=0;i<arrSize;i++){
                sum += (int)cArray[i];
            }
            if(sum!=4){
                for(int i=0;i<gSize;i++){
                    sGuess[i] = index + '0';
                }
            }
            else if(sum==4){
                allFour = true;
            }
            index++;
        }
        
        if(allFour){
            for(int i=0;i<arrSize;i++){
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
                if(correct==1){
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
                else if(correct==0){
                    m++;
                    sGuess[++p]=cGuess[n] + '0';
                }
            }
            
            else if(foundFir==true && foundSec==false){
                //After finding the first digit, find the second digit
                if(correct==1){
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
                
                else if (correct==0){
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
                if(correct==1){
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
                
                else if(correct==0){
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
                    for(int i=0;i<gSize;i++){
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

bool calculate(string code,string guess,char &correct,char &wrong){
    string check="    ";
    correct=0,wrong=0;
    //Check how many digits are in the correct place
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            correct++;
            check[i]='x';
            guess[i]='x';
        }
    }
    //Check how many digits are in the incorrect place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                wrong++;
                check[i]='x';
                break;
            }
        }
    }
    
    //Is the code broken or not
    if(correct==4)return false;
    return true;
}

string solution(){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%10+'0';
    }
    return code;
}