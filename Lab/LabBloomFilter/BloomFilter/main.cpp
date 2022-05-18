#include "BloomFilter.h"

void displayProblem(int problem) {
    
    switch(problem) {
        case 1:
            cout << "1) Using the 2 of the 9 hash functions you have, duplicate the "
                    "process found in the example." << endl;
            break;
        case 2:
            cout << "2) Next create a file with random inputs and use all 9 hashes "
                    "this time." << endl;
            break;
        case 3:
            cout << "3) Choose several spots in the table with 9 hashes and confirm "
                        "results with your program." << endl;
            break;
    }
    
}

void problemOne() {
    
    displayProblem(1);
    
    bool done = false; // For looping until done entering numbers
    string entry; // User input
    string bits = "000000000000000"; // 15 bit vector analogue
    
    cout << "Please enter an item to add: ";
    while (!done) {
        // Get user input, stopping if the user wants to
        getline(cin, entry);
        if (entry == "-1") {
            done = true;
            break;
        }
        
        // Hash the input and store in vector if not already filled
        if (bits[FNVHash(entry)%15] == '0') {
            bits[FNVHash(entry)%15] = '1';
        }
        if (bits[BPHash(entry)%15] == '0') {
            bits[BPHash(entry)%15] = '1';
        }
        
        // Display resulting location from hash and updated vector
        cout << "FNVHash: " << FNVHash(entry)%15 << endl;
        cout << "BPHash: " << BPHash(entry)%15 << endl;
        cout << bits << endl;
        
        // Prompt user to enter more or quit
        cout << endl << "Enter another item or enter \"-1\" to finish "
                "entering: " ;
    }
    
    cout << endl;
    
    done = false; // Reset loop
    
    // Prompt user to enter first item to check and receive, quitting as needed
    cout << "Please enter an item to check: ";
    while (!done) {
        getline(cin, entry);
        if (entry == "-1") done = true;
        
        // Display resulting location from hash
        cout << "FNVHash: " << FNVHash(entry)%15 << endl;
        cout << "BPHash: " << BPHash(entry)%15 << endl;
        
        // Check if item is in bloom filter
        if ((bits[FNVHash(entry)%15] == '1') && 
                (bits[BPHash(entry)%15] == '1')) {
            cout << "\"" << entry << "\" MAY be in the list." << endl;
        }
        else {
            cout << "\"" << entry << "\" is NOT in the list." << endl;
        }
        
        // Display vector
        cout << bits << endl << endl;
        
        // Prompt user to enter more or quit
        if (!done) cout << "Enter another item or enter \"-1\" to finish "
                "entering: ";
    }
    
}

void problemsTwoAndThree() {
    
    displayProblem(2);
    displayProblem(3);
    
    bool checking = true; // For looping until done checking numbers
    
    while (checking) {
        
        string entry = ""; // User input
    
        int numHashes = 9;

        // Ask how many bits the user wants in their "vector" then create it
        cout << "Please enter number of bits (size of vector): ";
        int vectorSize; 
        cin >> vectorSize;
            string bits = "";
        for (int i = 0; i < vectorSize; i++) {
            bits += "0";
        }
            
        // Ask how many random numbers the user wants to generate
        cout << "Please enter number of numbers to generate and store: ";
        int numRands;
        cin >> numRands;

        // Populate bloom filter with numRands number of random numbers
        for (int i = 0; i < numRands; i++) {
            std::string random = std::to_string(rand()%999);
            
            if (bits[RSHash(random)%vectorSize] == '0') bits[RSHash(random)%vectorSize] = '1';
            if (bits[JSHash(random)%vectorSize] == '0') bits[JSHash(random)%vectorSize] = '1';
            if (bits[PJWHash(random)%vectorSize] == '0') bits[PJWHash(random)%vectorSize] = '1';
            if (bits[ELFHash(random)%vectorSize] == '0') bits[ELFHash(random)%vectorSize] = '1';
            if (bits[DJBHash(random)%vectorSize] == '0') bits[DJBHash(random)%vectorSize] = '1';
            if (bits[DEKHash(random)%vectorSize] == '0') bits[DEKHash(random)%vectorSize] = '1';
            if (bits[BPHash(random)%vectorSize] == '0') bits[BPHash(random)%vectorSize] = '1';
            if (bits[FNVHash(random)%vectorSize] == '0') bits[FNVHash(random)%vectorSize] = '1';
            if (bits[APHash(random)%vectorSize] == '0') bits[APHash(random)%vectorSize] = '1';
        }
        
        // Calculate false positive probability, display, repeat as desired
        double k = numHashes;
        double m = vectorSize;
        double n = numRands;
        double eRaised = pow( (exp(1.0)), (-k * (n/m)) );
        double falsePositives = pow( (1 - eRaised), (k) );

        cout << "False positive chance: " << falsePositives << endl;
        cout << "m/n: " << m/n << endl;
        cout << "k: " << k << endl;
        cout << "See chart to confirm. Enter \"-1\" to quit or anything else to "
                "check more numbers: ";
        
        cin >> entry;
        if (entry == "-1") {
            checking = false;
            break;
        }
    }
    
}