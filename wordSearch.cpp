/*
 * Created by Griffin Davis on 9/4/2019.
 * CS2337-002 D. Vogel
 *
 * wordSearch.cpp
 * This program will take in a grid of scrambled letters and words for searching
 * in two files. The program then finds the given words in the grid of letters.
 * It will output the given puzzle and the status of the searched words.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>

using namespace std;

// Defines directions via which words will be found
enum direction {LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP};

// Defines the maximum puzzle size (50x50)
const int MAX = 50;

// Stores the puzzle and relevant information
struct wordGame {
	int version; // Dictates version of the puzzle
	int numberRows;
	int numberColumns;
	char puzzle[MAX][MAX]; // 2D array to store the puzzle
};

// Stores the status of each word to be searched
struct wordFind {
	string word;
	bool found;
	int row;
	int column;
	direction where;
	int foundCount;
};

// Reverses the given string
string reverseString(string input) {
	string output = "";
	for (int i=(signed)input.size()-1; i >= 0; i--) {
		output += input.at(i);
	}

	return output;
}

// Find the word that is part of the wordFind structure inside the wordGame structure.
// If the word is found the wordFind structure will be updated.
void findWord(wordGame &game, wordFind &theFind) {
	string word = theFind.word;
	int rows = game.numberRows;
	int columns = game.numberColumns;

	// Handle LEFT_RIGHT and RIGHT_LEFT
	for (int r=0; r < rows; r++) {
		string rowLetters = "";
		for (int c=0; c < columns; c++) {
			rowLetters += game.puzzle[r][c];
		}

		// Look for word in given row, LEFT_RIGHT
		if (rowLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = r+1;
			theFind.column = (signed)rowLetters.find(word)+1;
			theFind.where = LEFT_RIGHT;
			theFind.foundCount++;
			break;
		}

		// Lookk for word in given row, RIGHT_LEFT
		rowLetters = reverseString(rowLetters);
		if (rowLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = r+1;
			theFind.column = columns-(signed)rowLetters.find(word);
			theFind.where = RIGHT_LEFT;
			theFind.foundCount++;
			break;
		}
	}

	// Handle DOWN and UP
	for (int c=0; c < columns; c++) {
		string columnLetters = "";
		for (int r=0; r < rows; r++) {
			columnLetters += game.puzzle[r][c];
		}

		// Look for word in given column, DOWN
		if (columnLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = (signed)columnLetters.find(word)+1;
			theFind.column = c+1;
			theFind.where = DOWN;
			theFind.foundCount++;
		}

		// Look for word in given column, UP
		columnLetters = reverseString(columnLetters);
		if (columnLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = rows-(signed)columnLetters.find(word);
			theFind.column = c+1;
			theFind.where = UP;
			theFind.foundCount++;
		}
	}

	// Handle RIGHT_DOWN and LEFT_UP across top
	for (int i=0; i < columns; i++) {
		string diagLetters = "";
		for (int r=0, c=i; r < rows && c < columns; r++, c++) {
			diagLetters += game.puzzle[r][c];
		}

		//Look for word in given diagonal, RIGHT_DOWN
		if (diagLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = (signed)diagLetters.find(word)+1;
			theFind.column = i+(signed)diagLetters.find(word)+1;
			theFind.where = RIGHT_DOWN;
			theFind.foundCount++;
		}

		//Look for word in given diagonal, LEFT_UP
		diagLetters = reverseString(diagLetters);
		if (diagLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = (signed)diagLetters.size()-(signed)diagLetters.find(word);
			theFind.column = columns-(signed)diagLetters.find(word);
			theFind.where = LEFT_UP;
			theFind.foundCount++;
		}
	}

	// Continue RIGHT_DOWN and LEFT_UP down left side
	for (int i=1; i < rows; i++) {
		string diagLetters = "";
		for (int r=i, c=0; r < rows && c < columns; r++, c++) {
			diagLetters += game.puzzle[r][c];
		}

		//Look for word in given diagonal, RIGHT_DOWN
		if (diagLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = i+(signed)diagLetters.find(word)+1;
			theFind.column = (signed)diagLetters.find(word)+1;
			theFind.where = RIGHT_DOWN;
			theFind.foundCount++;
		}

		//Look for word in given diagonal, LEFT_UP
		diagLetters = reverseString(diagLetters);
		if (diagLetters.find(word) != string::npos) {
			if (word == "BREAK") {
				cout << "sekfjgjrrf: " << rows << endl;
			}
			theFind.found = true;
			theFind.row = rows-(signed)diagLetters.find(word);
			theFind.column = (signed)diagLetters.size()-(signed)diagLetters.find(word);
			theFind.where = LEFT_UP;
			theFind.foundCount++;
		}
	}

	// Handle RIGHT_UP and LEFT_DOWN across bottom
	for (int i=0; i < columns; i++) {
		string diagLetters = "";
		for (int r=rows-1, c=i; r >= 0 && c < columns; r--, c++) {
			diagLetters += game.puzzle[r][c];
		}

		//Look for word in given diagonal, RIGHT_UP
		if (diagLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = rows-(signed)diagLetters.find(word);
			theFind.column = i+(signed)diagLetters.find(word)+1;
			theFind.where = RIGHT_UP;
			theFind.foundCount++;
		}

		//Look for word in given diagonal, LEFT_DOWN
		diagLetters = reverseString(diagLetters);
		if (diagLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = rows-(signed)diagLetters.size()+(signed)diagLetters.find(word)+1;
			theFind.column = columns-(signed)diagLetters.find(word);
			theFind.where = LEFT_DOWN;
			theFind.foundCount++;
		}
	}

	// Continue RIGHT_UP and LEFT_DOWN up left
	for (int i=rows-2; i >= 0; i--) {
		string diagLetters = "";
		for (int r=i, c=0; r >= 0 && c < columns; r--, c++) {
			diagLetters += game.puzzle[r][c];
		}

		//Look for word in given diagonal, RIGHT_UP
		if (diagLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = i-(signed)diagLetters.find(word)+1;
			theFind.column = (signed)diagLetters.find(word)+1;
			theFind.where = RIGHT_UP;
			theFind.foundCount++;
		}

		//Look for word in given diagonal, LEFT_DOWN
		diagLetters = reverseString(diagLetters);
		if (diagLetters.find(word) != string::npos) {
			theFind.found = true;
			theFind.row = (signed)diagLetters.find(word)+1;
			theFind.column = (signed)diagLetters.size()-(signed)diagLetters.find(word);
			theFind.where = LEFT_DOWN;
			theFind.foundCount++;
		}
	}
}

// Read the puzzle from the input file and update the wordGame structure.
bool readPuzzle(wordGame &game, string inputFileName) {
	game.version = 2;

	ifstream puzzleFile;
	puzzleFile.open(inputFileName);
	if (!puzzleFile) { // File not able to open
		return false;
	}

	// Opened successfully
	int rows;
	int columns;
	puzzleFile >> rows;
	puzzleFile >> columns;

	// Populate the wordGame structure
	game.numberRows = rows;
	game.numberColumns = columns;

	// Populate 2D puzzle array in the wordGame structure
	string word;
	puzzleFile >> word;

	// Validate row & column information
	if ((signed)word.size() != columns) {
		return false;
	}
	if (rows == 0) {
		return false;
	}
	int i = 0; // Iterator for 2D array
	while (puzzleFile) { // Runs until the file ends
		if (i < rows) {
			// Split letters of string
			for (int j = 0; j < columns; j++) {
				transform(word.begin(), word.end(), word.begin(), ::toupper);
				game.puzzle[i][j] = word.at(j);
			}
			i++; // Go to next row
		}
		puzzleFile >> word;
	}
	if (i != rows) { // Incorrect row information
		return false;
	}

	puzzleFile.close();
	return true;
}

// Display the contents of the puzzle
void displayPuzzle(wordGame &game) {
	int rows = game.numberRows;
	int columns = game.numberColumns;

	// Loop through rows and columns to print
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
				cout << game.puzzle[i][j];
		}
		cout << endl;
	}
}

int main() {
	string puzzleFileName;
	cin >> puzzleFileName;

	wordGame game;
	if (readPuzzle(game, puzzleFileName)) {
		cout << "The puzzle from file \"" << puzzleFileName << "\"" << endl;
		displayPuzzle(game);

		string wordFileName;
		cin >> wordFileName;

		ifstream wordFile;
		wordFile.open(wordFileName);

		if (!wordFile) {
			cout << "The puzzle file \"" << wordFileName << "\" could not be opened or is invalid" << endl;
			return 0;
		}

		string word;
		wordFile >> word;
		while (wordFile) { // Runs until the file ends
			wordFind find; // Declare wordFind struct
			transform(word.begin(), word.end(), word.begin(), ::toupper);
			find.word = word; // Give it the word from input
			find.found = false; // Initialize found boolean
			find.foundCount = 0; // Give it a default value
			findWord(game, find);

			// Handle output after looking for word
			if (find.found) {
				string directionOutput;
				// Convert from enum values to print values
				switch (find.where) {
					case 0:
						directionOutput = "right";
						break;
					case 1:
						directionOutput = "left";
						break;
					case 2:
						directionOutput = "down";
						break;
					case 3:
						directionOutput = "up";
						break;
					case 4:
						directionOutput = "right/down";
						break;
					case 5:
						directionOutput = "right/up";
						break;
					case 6:
						directionOutput = "left/down";
						break;
					case 7:
						directionOutput = "left/up";
						break;
					default:
						directionOutput = "translation failed";
				}

				// Print depending on foundCount
				if (find.foundCount == 1) {
					cout << "The word " << word << " was found at (" << find.row << ", " << find.column << ") - " << directionOutput << endl;
				} else {
					cout << "The word " << word << " was found " << find.foundCount << " times" << endl;
				}
			} else {
				cout << "The word " << word << " was not found" << endl;
			}

			wordFile >> word;
		}
		wordFile.close();
	} else {
		cout << "The puzzle file \"" << puzzleFileName << "\" could not be opened or is invalid" << endl;
	}

	return 0;
}
