// Stefani Bekker - cssc0424
// CS530, Spring 2019
// Assignment 3 Parser
// main.cpp

#include "Header.h"

using namespace std;
// Function to parse each line in the file
void parseLine(string lineBuffer){
    string currChar;
    string lastChar;
    string lastLastChar;
    bool openPar = false;
    bool assignment = false;
    bool semiColon = false;
    bool op = false;
    
    int lineLength = lineBuffer.length();
    
    // check if the first character is valid (letter)
    if(lineBuffer[0] < 65){
        if(lineBuffer[0] == 0){
            // fail if line is empty
            cout << "Fail -- new line\n";
            return;
        }
        // fails if starting character is anything other than a letter
        cout << "Fail -- invalid starting character: " << lineBuffer << "\n";
        return;
    } else if (lineBuffer[0] > 90 && lineBuffer[0] < 97){
        cout << "Fail -- invalid starting character: " << lineBuffer << "\n";
        return;
    } else {
        // goes through the rest of characters in the line to check for errors
        for(int i = 1; i < lineLength; i++){
            // classifies each character
            if(lineBuffer[i] >64 && lineBuffer[i] < 91){
                if (lastChar == "space"){
                    if (lastLastChar == "char" || lastLastChar == "digit"){
                        cout << "Fail: format must be 'id op id': " << lineBuffer << "\n";
                        return;
                    }
                }
                currChar = "char";
            } else if (lineBuffer[i] > 96 && lineBuffer[i] < 123){
                if (lastChar == "space"){
                    if (lastLastChar == "char" || lastLastChar == "digit"){
                        cout << "Fail -- format must be 'id op id': " << lineBuffer << "\n";
                        return;
                    }
                }
                currChar = "char";
            } else if (lineBuffer[i] > 47 && lineBuffer[i] < 58){
                currChar = "digit";
            } else if (lineBuffer[i] == 42 ||lineBuffer[i] == 43 || lineBuffer[i] == 45 || lineBuffer[i] == 47 || lineBuffer[i] == 37){
                op = true;
                currChar = "op";
                
                if ( lastChar == "op" || lastLastChar == "op"){
                    cout << "Fail -- two operators in a row not allowed: " << lineBuffer << "\n";
                    return;
                }
                
            } else if (lineBuffer[i] == 32){
                currChar = "space";
            } else if (lineBuffer[i] == 61){
                // equal signs not allowed after other operators
                if(op == true){
                    cout << "Fail -- no assignment allowed after operator: " << lineBuffer << "\n";
                    return;
                }
                if(assignment == true){
                    cout << "Fail -- two assignemt operators not allowed: " << lineBuffer << "\n";
                    return;
                }
                assignment = true;
                currChar = "equal";
            } else if (lineBuffer[i] == 40){
                // checks for parentheses errors, no two open parentheses in a row
                if(openPar == true){
                    cout << "Fail -- missing closing parentheses: " << lineBuffer << "\n";
                    return;
                }
                openPar = true;
                // makes sure there is an op before an open parentheses
                currChar = "openPar";
                if( lastChar == "id" || lastChar == "digit" || lastLastChar == "id" || lastLastChar == "digit"){
                    cout << "Fail -- must have an op before parentheses: " << lineBuffer << "\n";
                    return;
                }
                if (lineBuffer[i+1] == 32){
                    if (lineBuffer[i+2] < 65 || lineBuffer[i+2] > 122){
                        cout << "Fail -- must have an id after open parentheses: " << lineBuffer << "\n";
                        return;
                    }
                } else {
                    if (lineBuffer[i+1] < 65 || lineBuffer[i+1] > 122){
                        cout << "Fail -- must have an id after open parentheses: " << lineBuffer << "\n";
                        return;
                    }
                }
                
            } else if (lineBuffer[i] == 41){
                currChar = "closePar";
                if(openPar == true){
                    openPar = false;
                    
                    // checks if the last character was an op
                    if(lastChar == "op" || lastLastChar == "op"){
                        cout << "Fail -- must have form 'id op id' inside of parentheses: " << lineBuffer << "\n";
                        return;
                    }
                    
                } else {
                    // checks for parentheses errors, closing parentheses without open parentheses
                    cout << "Fail -- closing parentheses without open parentheses: " << lineBuffer << "\n";
                    return;
                }
            } else if(lineBuffer[i] == 59){
                semiColon = true;
                currChar = "semi-colon";
                // makes sure there is an id after op
                if(lastLastChar != "closedPar" && lastLastChar != "space" && lastLastChar != "char" && lastLastChar != "digit" && lastChar != "space"){
                    cout << "Fail -- must have identifier after assignment operator: " << lineBuffer << "\n";
                    return;
                }
                // semi colon not allowed for expression without assignment operator
                if(assignment == false){
                    cout << "Fail -- no semi-colon allowed if no assignment operator: " << lineBuffer << "\n";
                    return;
                }
                if(lineBuffer[i+1] != ' ' && lineBuffer[i+1] != '\0'){
                    // makes sure there is nothing other than a space typed after the semi-colon
                    cout << "Fail -- semi colon must be final character: " << lineBuffer << "\n";
                    return;
                }
                if(i+2 < lineLength){
                    // makes sure there is nothing other than a space typed after the semi-colon
                    cout << "Fail -- semi colon must be final character: " << lineBuffer << "\n";
                    return;
                    
                }
            } else {
                // fails if there is any unknown character that isnt valid in the grammar
                cout << "Fail -- unknown character '" << lineBuffer[i] << "': " << lineBuffer << "\n";
                return;
            }
            
            if(lastChar == "space"){
                if (currChar == "digit"){
                    // fails if there is a digit starting an id rather than a letter
                    cout << "Fail -- no digit starting identifier: " << lineBuffer << "\n";
                    return;
                }
            }
            if(lastChar == "op"){
                // fail if no space after operator
                if(currChar != "space" ){
                    cout << "Fail -- no space after operator: " << lineBuffer << "\n";
                    return;
                }
            }
            
            if(lineBuffer[i+1] == 0 && assignment == true){
                if(semiColon == false){
                    // makes sure there is a semi colon at the end if it is an assignment
                    cout << "Fail -- missing semi-colon for assignment: " << lineBuffer << "\n";
                    return;
                }
            }
            // tracks the characters
            lastLastChar = lastChar;
            lastChar = currChar;
        }
    }
    // checks to make sure there is a closing parentheses to the open parentheses
    if(openPar == true){
        cout << "Fail -- no closing parentheses: " << lineBuffer;
        return;
    }
    // otherwise it passes
    cout << "Pass: " << lineBuffer << "\n";
}

int main(){
    ifstream inFile("ex.txt") ; // open this file for input
    string lineBuffer ;
    
    if(!inFile.is_open()){
        cout << "Could not open file \n";
    } else {
        // for each line read from the file
        while(getline(inFile, lineBuffer)){
            parseLine(lineBuffer);
        }
    }
    return 0;
}

