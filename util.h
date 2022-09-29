#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  typename std::set<T> done;
  //creates a new empty set;
  for(typename std::set<T>::iterator i = s1.begin(); i != s1.end(); ++i){
    //iterates through first set;
    if(s2.find(*i) != s2.end()){
      //if the current value in s1 is in s2
      //inserts into new set.
      done.insert(*i);
    }
    //else does nothing.
  }
  //final list only has items that triggered if
  //so final list only has items in both sets.
  return done;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  typename std::set<T> done = s1;
  //creates a new set containing all values in set 1
  for(typename std::set<T>::iterator i = s2.begin(); i != s2.end(); ++i){
    //iterates through every value in set 2;
    if(done.find(*i) != done.end()){
      //if the current value is in set 2
      //continues the loop and nothing is added to final set.
      continue;
    }
    //if the current value was not in the first set,
    //then value is inserted.
    done.insert(*i);
  }
  //the final set contains all the items of the original set
  //plus all the items of the second set that weren't in the 
  //first. So it contains all unique elements from both sets.
  return done;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string rawWords);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
