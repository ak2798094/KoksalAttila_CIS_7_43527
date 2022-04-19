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
bool hintGenerator(string guess, char* solution, int numW, int numB){//hintGenerator both creates the hints that the codebreaker will recieve, and also checks to see if the codebreaker has guessed the code
    bool exactlyAlike = true;//assume the guess is in fact correct until proven otherwise
    int rightColorAndPlacement = 0;//and also keep running totals of the number of pegs that are right color/right spot, and those that are right color/wrong spot, for use in the hints
    int rightColorWrongSpot = 0;

    int wrongWhiteGuessed = 0;
    int wrongBlackGuessed = 0;//these counter variables will track the number of incorrectly-placed pegs that are white and black, for use in the second hint
    for(int i = 0; i < 8; i++){//for every letter of the guess
            if(guess[i] == solution[i]){//check to see if it matches with the corresponding peg in the code. If it does
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

    cout << "You have " << rightColorAndPlacement << " pegs of the correct color and position." << endl;//Then we produce our two hints for the player
    cout << "You have " << rightColorWrongSpot << " pegs that are the right color, but in the wrong position." << endl << endl;

    return exactlyAlike;//and return whether or not their guess was spot-on
}


int main(int argc, char** argv){
    string choice = "";

    cout << "Welcome to Mastermind." << endl;

    cout << "Please select a difficulty level:" << endl;
    cout << "1 = Easy. 2 = Medium. 3 = Hard." << endl;//We greet the player, then prompt them to select a difficulty
    cin >> choice;

    while (choice != "1" && choice != "2" && choice != "3"){//if the choice that they select isn't a valid one, then we slap them on the wrist and ask again
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
    }//The difficulty chosen determines the number of guesses the codebreaker has. We also acknowledge what difficulty option the player selected

    char solution [8];//Now we're hitting the game itself. First we initialize a solution character array of length 4
    bool repeat = true;//we also set up repeat, which will determine for how long players want to keep playing the game
    do{	//I'm using a do-while loop here to contain the game, since I know players will want to play at least once.
        int numBlack = 0;
        int numWhite = 0;//Set up counter variables to hold the number of black pegs and white pegs in the solution.
        srand(time(0));//Also, seed our random number generator using the time.

        for (int i = 0; i < 8; i++){//for every character in our code
            if(rand() % 2 == 0){//generate a random number, then determine if it's odd or even
                    solution[i] = 'W';//using that data, we randomly assign every peg in the solution array to be white or black
                    numWhite++;//we also adjust our counter variables accordingly
            }
            else{
                    solution[i] = 'B';
                    numBlack++;
            }
        }

        string guess;
        bool correct = false;
        int k = 0;
        //Now that the code has been generated by our codemaker, time to let the player have at it
        while (k < guesses && !correct){//this while loop is basically a for loop that players can break out of early if they guess the code
            cout << "Enter a guess: ";//Prompt the user for a guess
            cin >> guess;
            while (!validGuess(guess)){//Once we have a guess, we validate it using the validGuess function. If it's not valid, we keep prompting until we get one that is
                cout << "Invalid input. Please enter a four-character input consisting solely of B and W" << endl;
                cout << "Enter a guess: ";
                cin >> guess;
            }

            correct = hintGenerator(upperCaseifier(guess), solution, numWhite, numBlack);//now, take an all-uppercase version of the guess, the codemaker's code, and the total white and black pegs in the code
            //and run them through hintGenerator to create the hints, and also to determine if the codebreaker has successfully broken the code

            if(correct){//If they're right, then go ahead and tell them they one
                cout << "That's exactly it, you win!" << endl;
            }
            else{//If they're not right, let them know, and tell them how many guesses they have left
                cout << "That's not it, sadly! You have " << guesses-k << " guesses left!" << endl;
            }

            k++;//increment the iterator for our weird, janky for-loop
        }

        if(!correct){//if we ended up breaking out of the while loop due to running out of guesses, instead of by guessing correctly, print the loss statement
            cout << "You're all out of guesses! I win!" << endl;
            cout << "My code was ";
            for (int q = 0; q < 8; q++){//Also, we print out the code, to give users the catharsis of at least seeing the right code
                    cout << solution[q];
            }
            cout << "!" << endl;
        }

        cout << "Play again? (y/n) "; //Now that the game is complete, prompt the user to see if they want to play again
        string repeatchoice = "";
        cin >> repeatchoice;

        while(repeatchoice != "y" && repeatchoice != "Y" && repeatchoice != "n" && repeatchoice != "N"){//like all other user input, let's go ahead and validate this too
            cout << "Invalid input. Enter either 'y' or 'n': ";
            cin >> repeatchoice;
        }

        if(repeatchoice == "n" || repeatchoice == "N"){
            repeat = false;
        }//if our player says they don't wanna play anymore, we reverse repeat so we can break our do-while loop. If they do wanna continue, we do nothing, and let the loop...well, loop.

    }while(repeat);
}