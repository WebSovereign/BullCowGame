/* The game logic (no view code or direct user interaction)
   The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>
#include <iostream>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	// Constructors should also be public
	FBullCowGame();


	// Functions should be public
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	int32 GetLetterNumber() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset();
	void PrintGameSummary();
	void SetLetterNumber(int32);
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	int32 LetterNumber = 3;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};