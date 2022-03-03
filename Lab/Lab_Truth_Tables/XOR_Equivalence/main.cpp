/* 
 * File:   main.cpp
 * Author: Attila Koksal
 * Created on March 2, 2022, 11:30 PM
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Universal Constants

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    
    bool p[] = {true, true, false, false};
    bool q[] = {true, false, true, false};
    
    cout<<"p  q   (p&&q)||~(p||q)   !(p^q)   (p||q)&&~(p&&q)   p^q"<<endl;
    for(int i=0;i<4;i++) {
        cout<<(p[i]?'T':'F')<<"  "<<(q[i]?'T':'F')<<"          "<<
                ( ( p[i]&&q[i]||!(p[i]||q[i]) ) ?'T':'F')<<"            "<<
                ( !(p[i]^q[i])?'T':'F')<<"             "<<
                ( (p[i]||q[i])&&!(p[i]&&q[i]) ?'T':'F')<<"           "<<
                ( p[i]^q[i]? 'T':'F')<<endl;
                
    }
    return 0;
}

