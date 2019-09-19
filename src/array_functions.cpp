/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 19, 2019
 *  Author: Griffin Tritaik
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"

using namespace std;
using namespace constants;

//struct to hold all the information
struct entry
{
	string word;
	int num;
};

//
entry word_list[MAX_WORDS];
int size = 0;

//zero out array that tracks words and their occurrences
void clearArray(){
	size = 0;
	for (int i = 0; i < MAX_WORDS; i++){
		word_list[i].num = 0;
		word_list[i].word = "";
	}
}

//how many unique words are in array
int getArraySize(){
	return size;
}

//get data at a particular location
std::string getArrayWordAt(int i){
	return word_list[i].word;
}

int getArrayWord_NumbOccur_At(int i){
	return word_list[i].num;
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream){
	if(!myfstream.is_open()){
		return false;
	}
	string my_line;
	while (!myfstream.eof()){
		getline(myfstream,my_line);
		processLine(my_line);
	}
	myfstream.close();
	return true;
}

/*take 1 line and extract all the tokens from it
feed each token to processToken for recording*/
void processLine(std::string &myString){
	stringstream stream(myString);
	string my_token;
    while(getline(stream,my_token,CHAR_TO_SEARCH_FOR)){
        processToken(my_token);
    }
}

/*Keep track of how many times each token seen*/
void processToken(std::string &token){
    strip_unwanted_chars(token);
    if (token == ""){
    	return;
    }
    for (int i = 0; i < MAX_WORDS; i++){
    	string tempT = token;
    	string tempW = word_list[i].word;
    	toUpper(tempT);
    	toUpper(tempW);
    	if (tempT == tempW){
    		word_list[i].num++;
    		return;
    	}
    }
    word_list[size].word = token;
    word_list[size].num = 1;
    size++;
}

/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode){
    myfile.open(myFileName, mode);
    if (!myfile.is_open()){
        return false;
    }
    return true;
}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile){
	if (!myfile.is_open()){
		return;
	}
	myfile.close();
	return;
}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename){
    if (size == 0){
        return constants::FAIL_NO_ARRAY_DATA;
    }
    std::ofstream file;
    file.open(outputfilename.c_str());
    if (!file.is_open()){
    	file.close();
        return FAIL_FILE_DID_NOT_OPEN;
    }
    for (int i = 0; i < size; i++){
    	file << word_list[i].word + " " + to_string(word_list[i].num) + "\n";
    }
    file.close();
    return SUCCESS;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so){
	switch (so){
	case ASCENDING:
		for (int i = 0; i < size; i++){
            for (int j = i + 1; j < size; j++){
                std::string first = word_list[i].word;
                std::string second = word_list[j].word;
                toUpper(first);
                toUpper(second);
                if (first > second){
                	std::string temp = word_list[i].word;
		            int tempInt = word_list[i].num;
		            word_list[i].num = word_list[j].num;
		            word_list[i].word = word_list[j].word;
		            word_list[j].num = tempInt;
		            word_list[j].word = temp;
		            }
		        }
		    }
		break;
	case DESCENDING:
		break;
	case NUMBER_OCCURRENCES:
		break;
	case NONE:
		break;
	}
}
