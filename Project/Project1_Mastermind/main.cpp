/* 
 * File:   main.cpp
 * Author: Attila Koksal
 * Created on April 14, 2022, 2:38 PM
 * Purpose:  Project 1 Mastermind
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

bool validGuess (string guess){//determines if a player's guess is even
    if(guess.length() != 8){//if player inputs a four character long guess, then don't accept it
        return false;
    }
    for(int i = 0; i < 8; i++){//if guess has four letters, then go through the input and check if each letter is either a w, W, b, or B
        if(toupper(guess[i]) != 'W' && toupper(guess[i]) != 'B'){
            return false;//if input is wrong at all, then invalid guess
        }
    }

    return true;//if true still, then valid guess from player
	
}

string capitalize(string s){//used to make every letter uppercase in an input string
    for(int i = 0; i < s.length(); i++){
            s[i] = toupper(s[i]);
    }

    return s;
}
///////////////////////////////////////////////////////i am here
bool hintGenerator(string guess, char* answer, int numW, int numB){//hintGenerator both creates the hints that the codebreaker will recieve, and also checks to see if the codebreaker has guessed the code
    bool exactlyAlike = true;//assume the guess is in fact correct until proven otherwise
    int rightColorAndPlacement = 0;//and also keep running totals of the number of pegs that are right color/right spot, and those that are right color/wrong spot, for use in the hints
    int rightColorWrongSpot = 0;

    int wrongWhiteGuessed = 0;
    int wrongBlackGuessed = 0;//these counter variables will track the number of incorrectly-placed pegs that are white and black, for use in the second hint
    for(int i = 0; i < 8; i++){//for every letter of the guess
            if(guess[i] == answer[i]){//check to see if it matches with the corresponding peg in the code. If it does
                    rightColorAndPlacement++;//increment the number of perfectly right pegs by one
                    if(guess[i] == 'W'){//We also need to keep track of if the perfectly correct peg is white or black. This comes into play to provide the second hint
                            numW--;
                    }
                    else if(guess[i]== 'B'){
                            numB--;
                    }
            }
            else{//if the peg in the guess and the corresponding peg in the code are not the same
                    exactlyAlike = false;//then we have found a contradiction to the two codes being the same, and change exactlyAlike to reflect that
                    if(guess[i] == 'W' ){//then, we record that we have an incorrect peg that is either white or black in our two counter variables
                            wrongWhiteGuessed++;
                    }
                    else if(guess[i]== 'B' ){
                            wrongBlackGuessed++;
                    }
            }


    }
	
    if (wrongWhiteGuessed >= numW) {
            rightColorWrongSpot += numW;
    }
    else {
            rightColorWrongSpot += wrongWhiteGuessed;
    }

    if (wrongBlackGuessed >= numB) {
            rightColorWrongSpot += numB;
    }
    else {
            rightColorWrongSpot += wrongBlackGuessed;
    }

    cout << "You have " << rightColorAndPlacement << " pegs of the correct color and position." << endl;
    cout << "You have " << rightColorWrongSpot << " pegs that are the right color, but in the wrong position." << endl << endl;
//////////////////////here to below is done
    return exactlyAlike;//returns if player guess is eact answer
}


int main(int argc, char** argv){
    string choice = "";

    cout << "Welcome to Mastermind." << endl;

    cout << "Please select a difficulty level:" << endl;
    cout << "1 = Easy. 2 = Medium. 3 = Hard." << endl;//Select a difficulty
    cin >> choice;

    while (choice != "1" && choice != "2" && choice != "3"){//ask again if choice isn't valid
            cout << "Invalid choice. Please enter a 1, 2, or 3: ";
            cin >> choice;
    }

    int guesses;
    if (choice == "1"){
            guesses = 12;
            cout << "Easy selected!" << endl;
    }
    else if (choice == "2"){
            guesses = 10;
            cout << "Medium selected!" << endl;
    }
    else{
            guesses = 8;
            cout << "Hard selected!" << endl;
    }//the difficulty level decides how many guesses the player gets

    char answer [8];//initialize a character array of length 4
    bool repeat = true;//determine how long player wants to play the game
    do{
        int numBlack = 0;//# of black pegs
        int numWhite = 0;//# of white pegs
        srand(time(0));//set up a time using srand()

        for (int i = 0; i < 8; i++){//for each character
            if(rand() % 2 == 0){//generate a random number and then determine if value is odd or even
                answer[i] = 'W';//randomly assign every peg to be white or black
                numWhite++;
            }
            else{
                answer[i] = 'B';
                numBlack++;
            }
        }

        string guess;
        bool correct = false;
        int z = 0;
        while (z < guesses && !correct){//game code
            cout << "Enter a guess: ";//ask for a guess from the user
            cin >> guess;
            while (!validGuess(guess)){//Once a guess is made, validate it and if it's not valid, keep asking until one that qualifies is received
                cout << "Invalid input. Please enter a four-character input consisting solely of B and W" << endl;
                cout << "Enter a guess: ";
                cin >> guess;
            }

            correct = hintGenerator(capitalize(guess), answer, numWhite, numBlack);//create hints for the given guess and determine if guessed correctly

            if(correct){//if user is correct, they win the game
                cout << "Congratulations, you win!" << endl;
            }
            else{//if user is wrong, notify user of many guesses they have left
                cout << "Incorrect! You have " << guesses-z << " guesses left!" << endl;
            }

            z++;//increment z
        }
        
        if(!correct){//if number of guesses is exceeded, the player loses
            cout << "You're all out of guesses! I win!" << endl;
            cout << "The code was ";
            for (int q = 0; q < 8; q++){//print the actual answer to the game
                    cout << answer[q];
            }
            cout << "!" << endl;
        }

        cout << "Play again? (y/n) "; //ask the user if they want to play again after the game has concluded
        string repeatagain = "";
        cin >> repeatagain;

        while(repeatagain != "y" && repeatagain != "Y" && repeatagain != "n" && repeatagain != "N"){//validate the user's given input
            cout << "Invalid input. Enter either 'y' or 'n': ";
            cin >> repeatagain;
        }

        if(repeatagain == "n" || repeatagain == "N"){
            repeat = false;
        }//if user doesn't want to play again, the do-while loop breaks and if user does want to play again, just let the loop continue as it is

    }while(repeat);
}