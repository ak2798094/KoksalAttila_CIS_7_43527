/* 
 * File:   main.cpp
 * Author: Attila Koksal
 * Created on March 2, 2022, 11:28 PM
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Universal Constants 

//Function Prototypes
void prntTF(bool);

//Program Begins Here
int main(int argc, char** argv) {
    bool p[]={true, true, false, false};
    bool q[]={true, false, true, false};
    
    cout<<"p q ~p ~q p&&q p||q p^q p^q^q p^q^p !(p&&q) !p||!q !(p||q) !p^!q"<<endl;
    for(int i=0;i<4;i++) {
        prntTF(p[i]);
        prntTF(q[i]);               cout<<" ";
        prntTF(!p[i]);              cout<<" ";
        prntTF(!q[i]);              cout<<" ";
        prntTF(p[i]&&q[i]);         cout<<"   ";
        prntTF(p[i]||q[i]);         cout<<"   ";
        prntTF(p[i]^q[i]);          cout<<"   ";
        prntTF(p[i]^q[i]^q[i]);     cout<<"    ";
        prntTF(p[i]^q[i]^p[i]);     cout<<"     ";
        prntTF( !(p[i]&&q[i]) );    cout<<"      ";
        prntTF( !p[i]||!q[i] );     cout<<"     ";
        prntTF( !(p[i]||q[i]) );    cout<<"     ";
        prntTF( !p[i]^!q[i] );
        cout<<endl;
    }
    return 0;
}

//Function Prints True(T) or False(F) depending on the statement given 
void prntTF(bool statement) {
    if(statement==true) {
        cout <<"T ";
    } else {
        cout<<"F ";
    }
}