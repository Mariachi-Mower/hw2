#include <sstream>
#include <cctype>
#include <algorithm>
#include <set>
#include <string>
#include "util.h"


std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(std::string rawWords)
{
    std::set<std::string> bleh;
    int lCount = 0;
    std::string temp = "";
    for(int i = 0; i < (int) rawWords.size(); i++){
        //loops through every character in rawWords
        
        if(rawWords[i] >= 'A' && rawWords[i] <= 'Z'){
            rawWords[i] += 32;    
        }//if the char is a capital letter, converts to lowercase.


        //adds every character it finds to a temp string;
        if(rawWords[i] > 'z' || rawWords[i] < 'a'){
            // once it hits punctuation or a space
            // adds string to the set.
            if(lCount >= 2){
                //if punctuation reached
                //AND at least two letters, it adds to set.
                bleh.insert(temp);
            }
            lCount = 0;
            temp = "";
            continue;
        }
        lCount ++;
        temp += rawWords[i];
        //if it is a valid char and not a punctuation mark
        //it adds it to the temp string.
    }
    if(lCount >= 2){
        bleh.insert(temp);
    }
    return bleh;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}