#include <iomanip>
#include <set>
#include <algorithm>
#include <vector>
#include <iomanip>
#include "movie.h"
#include "util.h"

movie::movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

movie::~movie(){
}

std::set<std::string> movie::keywords() const{
    //gets the set containing every key word's products;
    //merges the sets together with set union.
    std::set<std::string> final;
    //final.insert(convToLower(genre_));
    std::set<std::string> temp = parseStringToWords(name_);
    final = setUnion(final, temp);
    temp = parseStringToWords(category_);
    final = setUnion(final, temp);
    temp = parseStringToWords(genre_);
    final = setUnion(final, temp);
    //temp = parseStringToWords(rating_);
    //final = setUnion(final, temp);
    return final;
}

std::string movie::displayString() const{
    std::string final = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return final;
}

void movie::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << std::setprecision(2) << std::fixed << price_ << "\n" << std::to_string(qty_) << "\n" << genre_ << "\n" << rating_ << "\n";
}

bool movie::isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}