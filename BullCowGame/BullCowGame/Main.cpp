/* BullCowGame.cpp : Defines the entry point for the console application
For game logic see FBullCowGame class */

#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//format in unreal engine for string and int manipulation
using FText = std::string; 
using int32 = int; 

void PrintIntro(); 
void PlayGame(); 
FText GetValidGuess(); 
bool AskToPlayAgain();
void PrintGameSummary();
void PrintEndGameMessage();

FBullCowGame BCGame; //instance of a new game

//Start application
int main()
{
	do 
	{
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	}

	while (AskToPlayAgain() == true);
	PrintEndGameMessage();

    return 0; //end application
}


void PrintIntro()
{
	//Welcome message to the user
	std::cout << "-----------------------------------------------\n";
	std::cout << "\tWelcome to Bulls and Cows.\n\n"; 
	std::cout << " ,/         \\,                   ,           ," << std::endl;
	std::cout << "((__,-'''-,__))                 /             \\  " << std::endl;
	std::cout << " `--)~   ~(--`                 ((__-^^-,-^^-__))" << std::endl;
	std::cout << ".-'(       )`-,                 `-_---' `---_-'" << std::endl;
	std::cout << "`~~`d\\   /b`~~`                  <__|o` 'o|__>" << std::endl;
	std::cout << "    |     |                         \\  `  /" << std::endl;
	std::cout << "    (6___6)                          ): :(" << std::endl;
	std::cout << "     `---`                           :o_o:" << std::endl;
	std::cout << "                                      '-'" << std::endl;
	std::cout << std::endl;
	std::cout << "    - COW -                         - BULL -" << std::endl;
	std::cout << std::endl;

	std::cout << "Bulls and Cows is a game that consists of guessing the hidden isogram word.\n " << 
				"An isogram is a word with no repeating letters in it. When trying to guess the isogram\n " <<
				"the game will ask you to enter a guess. Then it will display the number of 'Bulls' and 'Cows'\n " <<
				"based on your guess. The number of 'Bulls' represents that letter(s) is/are in the\n " << 
				"correct place to guess the isogram. On the other hand, the number of 'Cows' represents that the\n " <<
				"letter(s) is/are within the isogram but in the wrong place. Let's go ahead and play!\n" << std::endl;
		
	std::cout << std::endl;
	return; 
}


void PlayGame()
{
	FString level; //stores level desired by user
	std::cout << "Please select a level of difficulty (1, 2, 3, or 4): ";
	std::cin >> level;

	std::cout << std::endl;

	BCGame.GetHiddenWordBasedOnLevel(level); 

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?\n\n";

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	//loop asking for guesses while game is not won and still tries remaining 
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText guess = GetValidGuess(); 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
		std::cout << "Number of Bull(s) = " << BullCowCount.Bull;
		std::cout << " | Number of Cow(s) = " << BullCowCount.Cow 
			<< "\n\n-----------------------------------------------\n";
	}

	return;
}


FText GetValidGuess() 
{
	FString guess = "";
	EGuessStatus Status = EGuessStatus::Not_Initialized;//it does not have an 'status' as for now
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries(); 
		std::cout << " <> Please enter your guess: ";
		std::cin >> guess;

		Status = BCGame.CheckGuessValidity(guess);//initializing a status 

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an Isogram word (letters cannot repeat).\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter isogram.\n\n";
			break;
		default:
			//assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);

	return guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (yes/no): ";
	FString response = "";
	std::cin >> response;
	std::cout << std::endl;

	return (response[0] == 'y' || response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { std::cout << "\tCongratulations, you won!\n\n"; }
	else { std::cout << "\tI am so sorry, you ran out of tries. But try again!\n\n"; }
}

void PrintEndGameMessage()
{
	std::cout << "Thanks for playing Bulls and Cows, come back soon!\n\n";
	return;
}

