#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include "product.h"

class book : public Product
{
  public:

  book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author);
  ~book();
  //constructor and destructor.


    //acts like a getter for both private data members.
    //(ISBN number and author).
    std::set<std::string> keywords() const;

        /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    void dump(std::ostream& os) const;

    bool isMatch(std::vector<std::string>& searchTerms) const;

  private:
    std::string ISBN_;
    std::string author_;
};
#endif