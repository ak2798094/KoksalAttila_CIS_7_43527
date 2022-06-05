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
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    string code,guess;  //code to break, and current guess
    char rr,rw;         //right digit in right place vs. wrong place
    int nGuess;         //number of guesses
    
    //Initialize Values
    nGuess=0;
    code=set();
    rr=rw=0;
    
    //Loop until solved and count to find solution
    do{
       nGuess++;
       guess=AI(rr,rw);
    }while(eval(code,guess,rr,rw)&&nGuess<100);
    
    //Output the solution
    cout<<"Number of guesses with AI = "<<nGuess<<endl;
    cout<<code<<"="<<guess<<endl;

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
    static char cGuess[] = {0,0,0,0};// Will hold the correct digit, not in order
    
    static int index = 0;
    static char n = 0;//Index for cGuess
    static char m = 0;//Index for cCode
    static char p = 0;//Index for sGuess
    
    int sum = 0;
    
    string sGuess = "xxxx";
    static string cCode = "xxxx";
    
    
    // We need to find which vals are correct
    if(index <= ARRSIZE && !allFour){
        
        if(firstTime){
            sGuess = "0000";
            index++;

            firstTime = false;
        }

        else if(!firstTime){
            // Check if previous val was one of the numbers,
            // if rr != 0 then we know that the prev val is correct
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
            // Find first number
            // Set first index in cGuess into first index in sGuess
            sGuess[p] = cGuess[n]  + '0';
            aiFirst=false;
        }
        
        else if(aiFirst==false){
            
            if(foundFir==false){
                if(rr==1){
                    // Store first digit in first pos in cCode
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
                // Find the second digit since first digit was found
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
                    // We now can find the last digit. We just need to find the
                    // position that is not found within cCode
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
    //Check how many are right place
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            rr++;
            check[i]='x';
            guess[i]='x';
        }
    }
    //Check how many are wrong place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                rw++;
                check[i]='x';
                break;
            }
        }
    }
    
    //Found or not
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
