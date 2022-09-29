#include <iomanip>
#include <set>
#include <algorithm>
#include <vector>
#include "movie.h"
#include "util.h"


movie::movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

std::set<std::string> movie::keywords() const{
    std::set<std::string> final;
    std::set<std::string> temp = parseStringToWords(name_);
    final = setUnion(final, temp);
    temp = parseStringToWords(category_);
    final = setUnion(final, temp);
    final.insert(convToLower(genre_));
    return final;
}

std::string movie::displayString() const{
    std::string final = name_ + " Genre: " + genre_ + " Rating: " + rating_ + " " + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return final;
}

void movie::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << std::to_string(price_) << "\n" << std::to_string(qty_) << "\n" << genre_ << "\n" << rating_ << "\n";
}