#include <set>
#include <vector>
#include <sstream>
#include "book.h"
#include "util.h"


book::book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author) : 
    Product(category, name, price,qty),
    ISBN_(ISBN),
    author_(author)
{

}

std::set<std::string> book::keywords() const{
    std::set<std::string> final;
    final.insert(ISBN_);
    std::set<std::string> temp = parseStringToWords(author_);
    final = setUnion(final, temp);
    temp = parseStringToWords(name_);
    final = setUnion(final, temp);
    temp = parseStringToWords(category_);
    final = setUnion(final, temp);
    return final;
}


std::string book::displayString() const{
    std::string final = name_ + " " + "Author: " + author_ + " ISBN: " + ISBN_ + " ";
    final = final + " " + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return final;
}

void book::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << std::to_string(price_) << "\n" << std::to_string(qty_) << "\n" << ISBN_ << "\n" << author_ << "\n";
}