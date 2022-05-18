/* 
 * File:   main.cpp
 * Author: Attila Koksal
 * Created on May 17, 2022, 5:35 PM
 * Purpose:  Bloom Filter Demonstration
 */

//System Level Libraries
#include <iostream>
#include <string>
#include <bitset>

#include "GeneralHashFunctions.h"
#include "BloomFilter.h"

using namespace std;

int main(int argc, char* argv[]) {
    
   // Seed random
    srand(time(0));
    
    // Run the problems
    problemOne();
    problemsTwoAndThree();
    return 0;
   
}