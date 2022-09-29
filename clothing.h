#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include "product.h"

class clothing : public Product
{
    public:
    clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
    ~clothing();
        //constructor and destructor.

    std::set<std::string> keywords() const;

    std::string displayString() const;

    void dump(std::ostream& os) const;

    private:
        std::string size_;
        std::string brand_;
};
#endif