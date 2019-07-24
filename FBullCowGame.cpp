#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map 
using Ftext = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,3}, {4,5}, {5,7}, {6,9}, {7, 11}, {8, 13}, {9, 15}, {10, 17} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return this->MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return this->MyHiddenWord.length();
}

int32 FBullCowGame::GetLetterNumber() const
{
	return this->LetterNumber;
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		// if not a lowercase letter
		if (!islower(Letter))
			return false;
	}
	return true;
}

void FBullCowGame::SetLetterNumber(int32 number)
{
	this->LetterNumber = number;
}


void FBullCowGame::Reset()
{
	TMap<int32, FString> WordSelector{ {3, "car"}, {4, "edge"}, {5, "train"}, {6, "napkin"}, {7, "banquet"}, {8, "watchdog"},
										{9, "oligarchy"}, {10, "discourage"} };
	const FString HIDDEN_WORD = WordSelector[this->LetterNumber];
	this->MyHiddenWord = HIDDEN_WORD;

	this->MyCurrentTry = 1;
	this->bGameIsWon = false;
}


// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	this->MyCurrentTry++;

	FBullCowCount BullCowCount;
	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == this->MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++; // increment bulls
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	// if the guess isn't an isogram
	if (!IsIsogram(guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (this->GetHiddenWordLength() != guess.length()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwisse
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
		return true;

	TMap<char, bool> LetterSeen; // setup the map

	// loop through all the letters of the word
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handle both capital and lowercase letters
		// if the letter is in the map
		if (LetterSeen[Letter])
		{
			return false; // we do NOT have an isogram
		}
		// otherwise
		else
		{
			// add the letter to the map as seen
			LetterSeen[Letter] = true;
		}
	}


	return true; // for example in cases where /0 is entered
}

void FBullCowGame::PrintGameSummary()
{
	if (bGameIsWon)
		std::cout << "WELL DONE - YOU WIN!\n";
	else
		std::cout << "Better Luck Next Time!\n";
}