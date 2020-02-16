/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "constants.h"
#include "utilities.h"
//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
using namespace constants;
using namespace std;
struct word {
	std::string word = "";
	std::string upper = "";
	int count = 0;
};
//TODO add a global array of entry structs (global to this file)
word words[MAX_WORDS];
//TODO add variable to keep track of next available slot in array
int available = 0;
//TODO define all functions in header file
void clearArray() {
	for (int i = 0; i <= available; i++) {
		words[i].word = "";
		words[i].count = 0;
		words[i].upper = "";
	}
	available = 0;
}

std::string getArrayWordAt(int i) {

	return words[i].word;
}

int getArraySize() {
	return available;
}

int getArrayWord_NumbOccur_At(int i) {

	return words[i].count;
}
void processToken(std::string &token) {
	strip_unwanted_chars(token);
	string temp = token;
	if (!(token == "")) {
		toUpper(temp);
		for (int i = 0; i < MAX_WORDS; i++) {
			if (words[i].upper == temp) {
				words[i].count++;
				break;
			} else if (getArrayWordAt(i) == "") {
				words[i].word = token;
				words[i].count++;
				words[i].upper = temp;
				available++;
				break;
			}
		}
	}
}
void processLine(std::string &myString) {
	stringstream ss(myString);
	string tempToken;
	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}

}
void closeFile(std::fstream &myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
}
int writeArraytoFile(const std::string &outputfilename) {
	ofstream outputFile;
	outputFile.open(outputfilename.c_str());
	if (!outputFile.is_open()) {
		return FAIL_FILE_DID_NOT_OPEN;
	} else if (getArraySize() == 0) {
		return FAIL_NO_ARRAY_DATA;
	}
	for (int i = 0; i < available; i++) {
		outputFile << getArrayWordAt(i) + " ";
		outputFile << getArrayWord_NumbOccur_At(i);
		outputFile << endl;
	}
	outputFile.close();
	return SUCCESS;
}
void sortArray(constants::sortOrder so) {
	switch (so) {
	case NONE:
		break;

	case ASCENDING:
		for (int i = 0; i < available; i++) {
			string max = words[i].upper;
			int position = i;
			for (int j = i; j < available; j++) {
				if (words[j].upper < max) {
					max = words[j].upper;
					position = j;
				}
			}
			word temp = words[i];
			words[i] = words[position];
			words[position] = temp;

		}
		break;

	case DESCENDING:
		for (int i = 0; i < available; i++) {
			string min = words[i].upper;
			int position = i;
			for (int j = i; j < available; j++) {
				if (words[j].upper > min) {
					min = words[j].upper;
					position = j;
				}
			}
			word temp = words[i];
			words[i] = words[position];
			words[position] = temp;
		}
		break;

	case NUMBER_OCCURRENCES:
		for (int i = 0; i < available; i++) {
			int maxOccur = getArrayWord_NumbOccur_At(i);
			int position = i;
			for (int j = i; j < available; j++) {
				if (getArrayWord_NumbOccur_At(j) > maxOccur) {
					maxOccur = getArrayWord_NumbOccur_At(j);
					position = j;
				}
			}
			word temp = words[i];
			words[i] = words[position];
			words[position] = temp;
		}
		break;

	default:
		break;
	}

}
bool processFile(std::fstream &myfstream) {
	std::string line = "";
	while (!myfstream.eof()) {
		getline(myfstream, line);
		processLine(line);
	}
	return true;
}

bool openFile(std::fstream &myfile, const std::string &myFileName,
		std::ios_base::openmode mode = std::ios_base::in) {
	myfile.open(myFileName.c_str());
	if (!myfile.is_open()) {
		return false;
	}
	return true;
}

//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!

