/* This is the console executable that makes use of the BullCow class
   This acts as the view in a MVC pattern, and is responsible for all
   user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include "FBullCowGame.h"

// to make syntax Unreal friendly
using Ftext = std::string;
using int32 = int;
using std::cout;


using std::cin;
using std::endl;
using std::string;
using std::getline;

// function prototypes
void PrintIntro();
void PlayGame();
Ftext GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

// the entry point for the application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0; // exit the application
}


// introduce the game
void PrintIntro()
{
	cout << "Welcome to Bulls and Cows, a fun word game.\n";

	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	int32 LetterNumber = 3;
	cout << "Please enter the number of letters you would like the isogram to have. Must be between (3-10 letters). ";
	cin >> LetterNumber;
	BCGame.SetLetterNumber(LetterNumber);
	cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext guess = GetValidGuess();

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
		// Print number of bulls and cows
		cout << "Bulls = " << BullCowCount.Bulls;
		cout << ". Cows = " << BullCowCount.Cows << endl << endl;
	}

	BCGame.PrintGameSummary();

	return;
}


Ftext GetValidGuess() // loop continuously until given a valid guess
{
	Ftext Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		getline(cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		// Check the Status
		switch (Status)
		{
		case EGuessStatus::OK:
			return Guess;
			break;
		case EGuessStatus::Not_Isogram:
			cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			cout << "Please enter all lowercase letters.\n";
			break;
		default:
			cout << "Default Message.\n";
		}
		cout << endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	cout << "\nDo you want to play again with the same hidden word? Enter yes or no.";
	Ftext Response = "";
	getline(cin, Response);
	cout << endl;
	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}
