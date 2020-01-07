#pragma once

#include "stdafx.h"
#include <iostream>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map //unreal engine syntax

FBullCowGame::FBullCowGame() { Reset(); }

//Get methods
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyIsogram.length(); }

FString FBullCowGame::GetHiddenWordBasedOnLevel(FString level) //generates isogram based on level
{
	TMap<FString, FString> HiddenWordBasedOnLevel{ {"1", "sox"} ,{"2","dice"} ,{"3","plane"} ,{"4","carlos"} };
	MyIsogram = HiddenWordBasedOnLevel[level];
	return HiddenWordBasedOnLevel[level];
}

bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	//realtionship between word length and max tries
	TMap<int32, int32> HiddenWordToMaxTries{ {3,4} , {4,7} , {5,10} , {6,16} }; 
	return HiddenWordToMaxTries[MyIsogram.length()]; 
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameWon = false;
	
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	//if the guess is not an insogram
	if (!IsIsogram(guess)) { return EGuessStatus::Not_Isogram; }

	//not lowercase
	else if (!IsLowerCase(guess)) { return EGuessStatus::Not_Lowercase; }

	//length of hidden word and guess does not match
	else if (GetHiddenWordLength() != guess.length()) { return EGuessStatus::Wrong_Length; }

	//guess is accepted 
	else { return EGuessStatus::OK; }
}

//accepts valid guess, increments try and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount; 
	int32 wordLength = MyIsogram.length(); //assuiming word length matches between guess and isogram

	//loop through all letters in the guess
	for (int32 CharIsogram = 0; CharIsogram < wordLength; CharIsogram++)
	{
		//compare letters against the isogram
		for (int32 CharGuess = 0; CharGuess < wordLength; CharGuess++)
		{
			if (MyIsogram[CharIsogram] == guess[CharGuess]) //if the letters match
			{
				if (CharIsogram == CharGuess) { BullCowCount.Bull++; } //increment bull if the same place

				else { BullCowCount.Cow++; } //increment cow if not same place
			}

			else { } //do nothing if no matching 
		}
	}

	if (BullCowCount.Bull == wordLength) { bGameWon = true; }
	else { bGameWon = false; }; //remains false

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString word) const
{
	//consider 0 and 1 letter word as isograms
	if (word.length() < 2) { return true; }

	//setup map to check if letters repeat
	TMap<char, bool> LetterSeen;

	for (auto letter : word) //for all letters in word
	{
		letter = tolower(letter); 

		if (LetterSeen[letter]) { return false; } //if letter repeats, do not add it to map
		else { LetterSeen[letter] = true; } //if letter is not repeating, add it to map 
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString word) const
{
	for (auto letter : word) { if (!islower(letter)) { return false; } } //if letter is uppercase
	return true; //if all letters are lowercase
}


