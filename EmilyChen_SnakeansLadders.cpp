// ConsoleApplication5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Title: Assignment-1
Author: EmilyChen
Objective: Roll to advance in the game, the first player to reach 20 will be the winner. If you land on a snake you have to go back to the snake's destination.  
Design Description: 
	Data modules: struct Player, struct Snake, Player gamePlayer[] (array), Snake gameSnakes[] (also and array)
	Code modules: rollNumber, landOnSnake, playerTurn, higgestPosition, printSnake, determineWinner, gameStateFinal, printPlayers, initializeSnake, gameLoop
	The most complicated function is gameLoop, where the function loops through all the players and makes them roll as long as none of the players have reached position 20 yet, 
	as soon as that happensm the loop breaks and the game ends.  
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Player {
	int playerNumber;
	int playerPos;
	;
};

struct Snake {
	int snakePos;
	int snakeDestination;
	;
};

int rollNumber() {
	int rollNum; 
	rollNum = rand() % 6 + 1;
	return rollNum; 
}


void landOnSnake(Snake gameSnake[], int numberOfSnakes, Player gamePlayer[], int playerNumber) {
	int playerPosition = gamePlayer[playerNumber].playerPos;
	for (int i = 0; i < numberOfSnakes; i++) {
		if (playerPosition == gameSnake[i].snakePos) {
			gamePlayer[playerNumber].playerPos = gameSnake[i].snakeDestination;
			std::cout << "Player " << playerNumber+1 << " stepped in a snake and is now at: " << gamePlayer[playerNumber].playerPos << "\n";
		}
	}
}


void printPlayers(int numOfPlayers, Player gamePlayer[]) {
	for (int i = 0; i < numOfPlayers; i++) {
		std::cout << "Player " << gamePlayer[i].playerNumber << " is at position: " << gamePlayer[i].playerPos << "\n";
	}
}

void playerTurn(Player gamePlayer[], int numOfPlayers, Snake gameSnake[], int numberOfSnakes) {
	int numRoll;
	numRoll = rollNumber();
	std::cout << "Player " << gamePlayer[numOfPlayers].playerNumber << " has rolled a " << numRoll << "!\n";
	gamePlayer[numOfPlayers].playerPos+=numRoll;
	std::cout << "Player " << gamePlayer[numOfPlayers].playerNumber << " is at: " << gamePlayer[numOfPlayers].playerPos << "\n";
	landOnSnake( gameSnake, numberOfSnakes, gamePlayer, numOfPlayers);

}

int higgestPosition(Player gamePlayer[], int numOfPlayers) {
	int largestNum = gamePlayer[0].playerPos;
	for (int i = 1; i < numOfPlayers; i++) {
		if (largestNum < gamePlayer[i].playerPos) {
			largestNum = gamePlayer[i].playerPos;
		}
	}
	return largestNum;
}

int lowestPosition(Player gamePlayer[], int numOfPlayers) {
	int lowestNum = gamePlayer[0].playerPos;
	for (int i = 1; i < numOfPlayers; i++) {
		if (lowestNum > gamePlayer[i].playerPos) {
			lowestNum = gamePlayer[i].playerPos;
		}
	}
	return lowestNum;
}

void printSnake(Snake gameSnake[], int numberOfSnakes, Player gamePlayer[], int numOfPlayers) {
	std::cout << "\n";
	std::cout << "There are: 5 snakes \n";

	for (int i = 0; i < numberOfSnakes; i++) {

	std::cout << "Snake #"<< i+ 1 << " is at "<< gameSnake[i].snakePos << " and leads to "<< gameSnake[i].snakeDestination <<"\n";
	}
}

int determineWinner(Player gamePlayer[], int numOfPlayers) {
	int number = 0;
	int higestPosition = higgestPosition(gamePlayer, numOfPlayers);
	for (int i = 0; i < numOfPlayers; i++) {
		if (higestPosition == gamePlayer[i].playerPos) {
			number = i;
		}
	}
	return number; 
}

void gameStateFinal(Player gamePlayer[], int numOfPlayers) {
	int playerWinner;
	playerWinner = determineWinner(gamePlayer, numOfPlayers);
	std::cout << "PLAYER " << playerWinner + 1 << " IS THE WINNER!" << "!\n";
	std::cout << "\n";
	std::cout << "Final Results of game!\n";
	printPlayers(numOfPlayers, gamePlayer);
}



void gameLoop(Player gamePlayer[], Snake gameSnakes[], int numOfPlayers, int numOfSnakes) {
	int numTheEnd=0; 
	char rollInput;
	while (numTheEnd<=20) {
		printSnake(gameSnakes, numOfSnakes, gamePlayer, numOfSnakes); //print the snakes before each round 

		for (int i = 0; i < numOfPlayers; i++) {
			std::cout << "\n";
			std::cout << "Enter any letter to roll\n";
			std::cin >> rollInput;
			playerTurn(gamePlayer, i, gameSnakes, numOfSnakes);
			numTheEnd = higgestPosition(gamePlayer, numOfPlayers);
			if (numTheEnd>=20) {
				break; //end the loop if anyone wins 
			}
		}
	}
	gameStateFinal(gamePlayer, numOfPlayers); //game has ended
}

void initializeSnake(Snake gameSnakes[], int numSnakes, int snakePos, int snakeDes) {
	gameSnakes[numSnakes].snakePos = snakePos;
	gameSnakes[numSnakes].snakeDestination = snakeDes; 
}

int main()
{

	srand(time(NULL));	//not nessassary, but it makes the rolls more random 

	int numOfPlayers=0;

    std::cout << "How many players are playing?\n";
	std::cin >> numOfPlayers;
	std::cout << numOfPlayers<< "\n";

	//ensure the input is not a letter of the alphabet 
	while (!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "It must be a number!\n";
		std::cin >> numOfPlayers;
	}
	//ensure the input is between 2 and 3  
	while ((numOfPlayers<2) || (numOfPlayers>3)) {
		std::cout << "It must be an interger between 2 and 3 \n";
		std::cin >> numOfPlayers;
	}

	std::cout <<"There are "<< numOfPlayers <<" Players\n";

	struct Player gamePlayer[3];
	struct Snake gameSnakes[5];
	int numOfSnakes = 5;

	//make the snake objects
	initializeSnake(gameSnakes, 0, 2, 0);
	initializeSnake(gameSnakes, 1, 5, 3);
	initializeSnake(gameSnakes, 2, 8, 4);
	initializeSnake(gameSnakes, 3, 13, 10);
	initializeSnake(gameSnakes, 4, 15, 12);

	//give the player objects player numbers and a starting position of 0 
	for (int i = 0; i < numOfPlayers; i++) {
		gamePlayer[i].playerNumber = i+1; 
		gamePlayer[i].playerPos = 0;
	}

	//print the starting positons 
	printPlayers(numOfPlayers, gamePlayer);

	//start the game loop
	gameLoop(gamePlayer, gameSnakes, numOfPlayers, numOfSnakes);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
