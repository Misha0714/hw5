#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


//word is way to construct the valid word 
//results is a set to keep track of all the valid words found 
void findWord(const std::string& in, std::string& floating, const std::set<std::string>& dict, 
std::string& word, std::set<std::string>& result, int nextDash) {
  
    //base case 
    //if there is more floating characters then spaces left to fill, return 
    if (word.size() - nextDash  < floating.size()){
      return;
    }
    if (nextDash==word.size()){
        if(word.size() == in.size()) {
          //if it is a valid word 
          if (floating.size() == 0 && dict.find(word) != dict.end() ) {
              //then insert the word in results 
              result.insert(word);
              return;
          }
      }
      return;
    }
    if (word[nextDash] != '-'){
      findWord(in, floating, dict, word, result, nextDash + 1);
      return;
    }
    
    
    //cerr <<nextDash << " ";

    //go through all the floating characters 
    for (int i=0; i < floating.size(); i++){
        //start to contruct a new word 
        //in the newWord's first index where there is a dash place a floating letter 
        word[nextDash] = floating[i];
        string oldfloating = floating;
        //place this partial word in the recursive function so it can start to go through and finish off the word 
				floating = floating.substr(0, i) + floating.substr(i + 1); 
        //cerr << afterLetter << endl;
				
        findWord(in, floating, dict, word, result, nextDash + 1);
        floating = oldfloating;
        //merge the results 


    }
    for (char letter = 'a'; letter <= 'z'; ++letter) {
        // Skip characters that are already in the word
				//if it is a floating letter then skip it 
				
        if (floating.find(letter) != std::string::npos) {
            continue;
        }
        // Replace the blank with each lowercase English letter
        word[nextDash] = letter;
        // Recursively call the function with the updated word and merge the results
        findWord(in, floating, dict, word, result, nextDash + 1);
    }

		  
    // Return the result set here (after both loops have finished)
		word[nextDash] = '-'; 

}

// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> result;
    std::string word = in; // Initialize word with blanks

    // Generate words recursively
    string newFloating = floating;
    findWord(in, newFloating, dict, word, result, 0);

    return result;

}

// Define any helper functions here
