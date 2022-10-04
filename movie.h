#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include "product.h"
#include <fstream>


//movie derived from the product class containing a genre and rating.
class movie: public Product
{
    public:
    movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
    ~movie();

    std::set<std::string> keywords() const;

    std::string displayString() const;

    void dump(std::ostream& os) const;

    bool isMatch(std::vector<std::string>& searchTerms) const;
    private:
        std::string genre_;
        std::string rating_;
};
#endif