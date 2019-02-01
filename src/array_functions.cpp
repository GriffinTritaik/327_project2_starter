/*
 * functionstocomplete.cpp
 *
 *  Created on: 1/30/19
 *      Author: Griffin Triatik
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
//    stuff you will need
//============================================================================
//zero out array that tracks words and their occurrences

struct entry
{
    std::string word;
    int number_occurence;
};

//array made with max size and a pointer with size value
entry list[constants::MAX_WORDS];
int listSize = 0;

//resets the values of the each spot in the array to empty string with occurrence of 0 times
void clearArray(){
    listSize = 0;
    for (int i = 0; i < constants::MAX_WORDS; i++){
        list[i].word = "";
        list[i].number_occurence = 0;
    }
}

//how many unique words are in array
int getArraySize(){
    return listSize;
}

//get data at a particular location
std::string getArrayWordAt(int i){
    return list[i].word;
}

int getArrayWord_NumbOccur_At(int i){
    return list[i].number_occurence;
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream){
    if(!myfstream.is_open()){
        return false;
    }
    std::string line;
    while (!myfstream.eof()) {
            getline(myfstream, line);
            processLine(line);
    }
    myfstream.close();
    return true;
}

/*take 1 line and extract all the tokens from it
feed each token to processToken for recording*/
void processLine(std::string &myString){
    std::stringstream ss(myString);
    std::string token;

    while(getline(ss,token,constants::CHAR_TO_SEARCH_FOR)){
        processToken(token);
    }
}

/*Keep track of how many times each token seen*/
void processToken(std::string &token){
    strip_unwanted_chars(token);
    if (token == ""){
        return;
    }
    for (int i = 0; i < constants::MAX_WORDS; i++){
        std::string tempToken = token;
        std::string tempWord = list[i].word;
        toUpper(tempToken);
        toUpper(tempWord);
        if (tempToken == tempWord){
            list[i].number_occurence++;
            return;
        }
    }
    list[listSize].number_occurence = 1;
    list[listSize].word = token;
    listSize++;
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
}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 *             FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 *             SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename){
    if (listSize == 0){
        return constants::FAIL_NO_ARRAY_DATA;
    }
    std::ofstream file;
    file.open(outputfilename.c_str());
    if (!file.is_open()){
    	file.close();
        return constants::FAIL_FILE_DID_NOT_OPEN;
    }
    for (int i = 0; i < listSize; i++){
    	file << list[i].word + " " + std::to_string(list[i].number_occurence) + "\n";
    }
    file.close();
    return constants::SUCCESS;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so){
    switch (so){
        case constants::ASCENDING:
            for (int i = 0; i < listSize; i++){
                for (int j = i + 1; j < listSize; j++){
                    std::string first = list[i].word;
                    std::string second = list[j].word;
                    toUpper(first);
                    toUpper(second);
                    if (first > second){
                        std::string temp = list[i].word;
                        int tempInt = list[i].number_occurence;
                        list[i].word = list[j].word;
                        list[i].number_occurence = list[j].number_occurence;
                        list[j].word = temp;
                        list[j].number_occurence = tempInt;
                    }
                }
            }
            break;
        case constants::DESCENDING:
            for (int i = 0; i < listSize; i++){
                for (int j = i + 1; j < listSize; j++){
                    std::string first = list[i].word;
                    std::string second = list[j].word;
                    toUpper(first);
                    toUpper(second);
                    if (first < second){
                        std::string temp = list[i].word;
                        int tempInt = list[i].number_occurence;
                        list[i].word = list[j].word;
                        list[i].number_occurence = list[j].number_occurence;
                        list[j].word = temp;
                        list[j].number_occurence = tempInt;
                    }
                }
            }
            break;
        case constants::NUMBER_OCCURRENCES:
            for (int i = 0; i < listSize; i++){
                for (int j = i + 1; j < listSize; j++){
                    int first = list[i].number_occurence;
                    int second = list[j].number_occurence;
                    if (first < second){
                        int tempInt = first;
                        std::string tempSting = list[i].word;
                        list[i].word = list[j].word;
                        list[i].number_occurence = list[j].number_occurence;
                        list[j].word = tempSting;
                        list[j].number_occurence = tempInt;
                    }
                }
            }
            break;
        case constants::NONE:
            break;
    }
}
