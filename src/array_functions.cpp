/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"

//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
//zero out array that tracks words and their occurrences

struct entry
{
	std::string word;
	int number_occurence;
};

entry array[constants::MAX_WORDS];

void clearArray(){

}

//how many unique words are in array
int getArraySize(){
	return 0;//array_functions
}

//get data at a particular location
std::string getArrayWordAt(int i){
	return "";
}

int getArrayWord_NumbOccur_At(int i){
	return 0;
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream){
	return false;
}

/*take 1 line and extract all the tokens from it
feed each token to processToken for recording*/
void processLine(std::string &myString){

}

/*Keep track of how many times each token seen*/
void processToken(std::string &token){

}

/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName, std::ios_base::openmode mode){
	myfile.open(myFileName.c_str(), mode);
	return true;
}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile){
	myfile.close();
}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename){
	return constants::SUCCESS;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so){

}
