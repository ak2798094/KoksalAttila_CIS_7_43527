/* 
 * File:    main.cpp
 * Author:  Attila Koksal
 * Created: May 8, 2022, 3:50 PM
 * Purpose: Lab Project 1A Mastermind                  
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <fstream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
void mapDgts(map<int,char>&);           
char srchMap(map<int,char>,int);       
void gameSet(int&,bool&,bool&);
string genCode(map<int,char>,string&,bool,bool,int); 
string genInpt(map<int,char>,string,int,int);
void inptChk(string,string,int,int,char**,fstream&,int*,int*,int*); 
char **initBrd(int,int);                    
void outBrd(char**,string,int,int,fstream&,int*,int*,int*);
void dstroy(char**,int);                    
void rgtInpt(char*,string,string,string&,int &,vector<int>&,vector<int>&);
void wrgInpt(string,string,string&,int&,vector<int>&,vector<int>&);
void totals(int,int*,int*,int*,fstream&);   

//Execution Starts Here

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    
    fstream out;            
    bool duplic8;           
    char **gameBrd;        
    int nGuess,count;      
    int row,col,seqLnth;    
    string numSeq, cpuInpt; 
    map<int,char> digits;
    int *correct;           
    int *crctWrg;           
    int *sum;               
    bool test=false;        
    
    gameSet(seqLnth,duplic8,test);
    out.open("gameResult.txt", ios::out);
            
    count=0;
    col= seqLnth;
    nGuess=row=10000;
    correct = new int[row];    
    crctWrg = new int[row];
    sum     = new int[row];
    
    mapDgts(digits);           
    gameBrd= initBrd(row,col*2);
    numSeq= genCode(digits,cpuInpt,duplic8,test,seqLnth); 
    cout<<"\nThe Character Number Seq. Generated : "<<numSeq<<endl<<endl;
    
    do{
        cpuInpt= genInpt(digits,cpuInpt,count,seqLnth);
        inptChk(cpuInpt,numSeq,seqLnth,count,gameBrd,out,correct,crctWrg,sum);
        ++count;
    }while(count<nGuess);   
    
    outBrd(gameBrd,numSeq,row,seqLnth,out,correct,crctWrg,sum);           
    totals(row,correct,crctWrg,sum,out);
    
    dstroy(gameBrd,row);
    delete []correct;
    delete []crctWrg;
    delete []sum;
    out.close();
    
    return 0;
}
void mapDgts(map<int,char> &dgtMap){          
    dgtMap.insert(pair<int,char>(0,'0'));     
    dgtMap.insert(pair<int,char>(1,'1'));     
    dgtMap.insert(pair<int,char>(2,'2'));     
    dgtMap.insert(pair<int,char>(3,'3'));     
    dgtMap.insert(pair<int,char>(4,'4'));     
    dgtMap.insert(pair<int,char>(5,'5'));     
    dgtMap.insert(pair<int,char>(6,'6'));     
    dgtMap.insert(pair<int,char>(7,'7'));     
    dgtMap.insert(pair<int,char>(8,'8'));     
    dgtMap.insert(pair<int,char>(9,'9'));     
}
char srchMap(map<int,char> digits,int num){   
    char digit;                                
    map<int,char>::iterator itr;               
    itr= digits.find(num);                     
    digit= itr->second;                       
    return digit; 
} 
void gameSet(int &seqLnth,bool &duplic8,bool &test){
    int length[]= {4,6,8};  
    string choice;          
    seqLnth= length[0];                        
    duplic8= rand()%2==1 ? true:false;         
    
    cout<<"Welcome to Digit-Mind, MasterMind's Pre-AI Game\n"<<endl;
    cout<<"\nEntering test input? [y/n] : ";
    cin >> choice;
    while (choice != "y" && choice != "n"){
        cout<<"Re-Enter Test Choice: ";
        cin >> choice;
    }
    if(choice == "y") test= true;
}
string genCode(map<int,char> digits,string &cpuInpt,bool repeat,bool test,int len){
    int key;                                   
    string numSeq;                             
    bool duplcte= false;                      
    
    numSeq= len==4 ? "0000":                  
            len==6 ? "000000": 
            len==8 ? "00000000": "0000"; 
    
    cpuInpt= numSeq;
    
    if (test){                                
        cout<<"Enter 4 Digit Test Input : ";
        cin >> numSeq;
    }else{
        if(repeat==true){
            for(int i=0; i<numSeq.length();i++){
                key= rand()%10;                       
                numSeq[i]= srchMap(digits,key);      
            }
        }else{    
            for(int i=0; i<numSeq.length();i++){
                key= rand()%10;
                if(i==0) numSeq[i]= srchMap(digits,key);
                else{
                    int count=0;
                    char digit= srchMap(digits,key);
                    do{
                        char cmpr= numSeq[count];     
                        if(digit==cmpr){
                           duplcte=true;               
                           count=0;                    
                           key= rand()%10;             
                           digit= srchMap(digits,key); 
                        }
                        else{           
                            duplcte=false;             
                            ++count;                  
                        }
                    }while(duplcte || count!=i);
                    numSeq[i]= digit;
                }
            }
        }
    }
    return numSeq;
}
string genInpt(map<int,char> digits,string inpt,int count,int len){
    int diffrce;   
    string numStr, 
           cpuStr; 
    
    numStr= to_string(count);                      
    cpuStr= inpt;
    diffrce= cpuStr.length() - numStr.length();
    
    for(int i= cpuStr.length()-1; i>= diffrce; i--){
        cpuStr[i]= numStr[i-diffrce];             
    }
    return cpuStr;
}
void inptChk(string cpuInpt,string clrSeq,int seqLnth,int row,char **board,
    fstream &out,int *correct,int *wrong,int *sums){
    int crp=0,cwp=0;    
    int sum;           
    string ansrKey;    
    char *temp;        
    vector<int> uNmIdx; 
    vector<int> sNmIdx; 
    
    temp= new char[seqLnth*2];      

    ansrKey= seqLnth==4 ? "    ":
             seqLnth==6 ? "      ":
             seqLnth==8 ? "        ": "    ";
    
    rgtInpt(temp,clrSeq,cpuInpt,ansrKey,crp,uNmIdx,sNmIdx);
    if(crp==seqLnth){
        for(int idx=seqLnth; idx<(seqLnth*2); idx++){ 
            temp[idx]= ansrKey[idx-seqLnth];          
        }
    }else{
        
        wrgInpt(clrSeq,cpuInpt,ansrKey,cwp,uNmIdx,sNmIdx);
        
        for(int l=0;l<seqLnth;l++){if(ansrKey[l]==' ') ansrKey[l]='-';}
        for(int idx=seqLnth; idx<(seqLnth*2); idx++){ 
            temp[idx]= ansrKey[idx-seqLnth];         
        }
    }
        
    for(int z=0;z<seqLnth*2;z++){board[row][z]= temp[z];}
    
    sum = crp+cwp;
    correct[row]= crp;
    wrong[row]= cwp;
    sums[row]= sum;
            
    sNmIdx.clear();
    uNmIdx.clear();
    delete []temp; 
}
void rgtInpt(char *temp,string clrSeq,string cpuInpt,string &ansrKey,int &crp,
    vector<int> &uNmIdx,vector<int> &sNmIdx){
    for(int i=0;i<clrSeq.length();i++){
        temp[i]= cpuInpt[i];        
        if(clrSeq[i]==cpuInpt[i]){  
            crp++;
            ansrKey[i]='o';
        }else{                      
            uNmIdx.push_back(i);
            sNmIdx.push_back(i);
        }
    }
}
void wrgInpt(string clrSeq,string cpuInpt,string &ansrKey,int &cwp,
    vector<int> &uNmIdx,vector<int> &sNmIdx){
    vector<int>::iterator itr;             
    for(int j=0;j<uNmIdx.size();j++){      
        itr= sNmIdx.begin();               
        for(int k=0;k<sNmIdx.size();k++){  
            if((clrSeq[sNmIdx[k]]==cpuInpt[uNmIdx[j]])&&ansrKey[uNmIdx[j]]==' '){;
                cwp++;
                ansrKey[uNmIdx[j]]='x';    
                sNmIdx.erase(itr);         
            }else ++itr;                  
        }
    }
}
void outBrd(char** gameBrd,string code,int row,int seqLnth,fstream &out,
            int *right,int *wrong,int *sums){
    cout<<"Code\t Guess    Feedback\t #right\t #right-wrong\t sum\n"<<endl;
    out<<"Code\t Guess    Feedback\t #right\t #right-wrong\t sum\n"<<endl;
    for(int y=0;y<row;y++){
        cout<<code<<"\t";  
        out<<code<<"\t";   
        for(int z=0;z<seqLnth*2;z++){
            if(z==seqLnth){
                cout<<"   "<<gameBrd[y][z]<<" ";            
                out<<"   "<<gameBrd[y][z]<<" ";             
            }else{
                cout<<gameBrd[y][z]<<" ";
                out<<gameBrd[y][z]<<" ";
            }
        }
        //Output rest of data
        cout<<"\t    "<<right[y]<<"\t     "<<wrong[y]<<"\t\t  "<<sums[y]<<endl;
        out<<"\t    "<<right[y]<<"\t     "<<wrong[y]<<"\t\t  "<<sums[y]<<endl;
    }
}
void totals(int size,int *right,int *wrong,int *sums,fstream &out){
    int r4,r3,r2,r1,r0;    
    int w4,w3,w2,w1,w0;     
    int sum4,sum3,sum2,sum1,sum0; 
    r4=r3=r2=r1=r0=w4=w3=w2=w1=w0=sum4=sum3=sum2=sum1=sum0= 0; 
    
    for(int i=0;i<size;i++){
        right[i] == 4 ? ++r4 :          
        right[i] == 2 ? ++r2 :
        right[i] == 1 ? ++r1 : ++r0;
        
        wrong[i] == 4 ? ++w4 :          
        wrong[i] == 3 ? ++w3 :
        wrong[i] == 2 ? ++w2 :
        wrong[i] == 1 ? ++w1 : ++w0;
        
        sums[i] == 4 ? ++sum4 :          
        sums[i] == 3 ? ++sum3 :
        sums[i] == 2 ? ++sum2 :
        sums[i] == 1 ? ++sum1 : ++sum0;
    }
    cout<<"\n\nTotals\n============\n"
           "4 Right Spots= "<<r4<<"\t4 Wrong Spots= "<<w4<<"\t4 as a Sum   = "<<sum4<<"\n"
           "3 Right Spots= "<<r3<<"\t3 Wrong Spots= "<<w3<<"\t3 as a Sum   = "<<sum3<<"\n"
           "2 Right Spots= "<<r2<<"\t2 Wrong Spots= "<<w2<<"\t2 as a Sum   = "<<sum2<<"\n"
           "1 Right Spots= "<<r1<<"\t1 Wrong Spots= "<<w1<<"\t1 as a Sum   = "<<sum1<<"\n"
           "0 Right Spots= "<<r0<<"\t0 Wrong Spots= "<<w0<<"\t0 as a Sum   = "<<sum0<<endl;
  
    out<<"\n\nTotals\n============\n"
           "4 Right Spots= "<<r4<<"\t4 Wrong Spots= "<<w4<<"\t4 as a Sum   = "<<sum4<<"\n"
           "3 Right Spots= "<<r3<<"\t3 Wrong Spots= "<<w3<<"\t3 as a Sum   = "<<sum3<<"\n"
           "2 Right Spots= "<<r2<<"\t2 Wrong Spots= "<<w2<<"\t2 as a Sum   = "<<sum2<<"\n"
           "1 Right Spots= "<<r1<<"\t1 Wrong Spots= "<<w1<<"\t1 as a Sum   = "<<sum1<<"\n"
           "0 Right Spots= "<<r0<<"\t0 Wrong Spots= "<<w0<<"\t0 as a Sum   = "<<sum0<<endl;
}
char **initBrd(int row,int col){
    char **board= new char *[row];
    for(int i=0;i<row;i++){
        board[i]= new char[col];
    }
    for (int i=0; i<row;i++){
        for(int j=0;j<col;j++){
            board[i][j]= '*';
        }
    }
    return board;
}
void dstroy(char **a,int row){
    for(int i=0;i<row;i++){
        delete []a[i];
    }
    delete []a;
}
