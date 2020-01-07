/* The game's logic lies here. Check guess validity, returning number of cows and bulls
and monitor whenever game is won or not. Also resets the game if desired by user */

#pragma once

#include <string>

//format in unreal engine for string and int manipulation
using FString = std::string; 
using int32 = int;

struct FBullCowCount
{
	int32 Bull = 0;
	int32 Cow = 0;
};

enum class EGuessStatus
{
	Not_Initialized,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame {

public:
	FBullCowGame(); //constructor 

	int32 GetMaxTries() const ;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWordBasedOnLevel(FString);

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

private:
	//see constructor for initialization
	int32 MyCurrentTry; 
	FString MyIsogram; 
	bool bGameWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};