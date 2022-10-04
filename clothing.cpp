#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <iomanip>
#include "clothing.h"
#include "product.h"
#include "util.h"


clothing::clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

clothing::~clothing(){
    
}

std::set<std::string> clothing::keywords() const{
    //gets the set containing every key word's products;
    //merges the sets together with set union.
    std::set<std::string> final;
    std::set<std::string> temp = parseStringToWords(name_);
    final = setUnion(final, temp);
    temp = parseStringToWords(brand_);
    final = setUnion(final, temp);
    temp = parseStringToWords(category_);
    final = setUnion(final, temp);
    return final;
}

std::string clothing::displayString() const{
    std::string final = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return final;
}


void clothing::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << std::setprecision(2) << std::fixed << price_ << "\n" << std::to_string(qty_) << "\n" << size_ << "\n" << brand_ << "\n";
}

bool clothing::isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}