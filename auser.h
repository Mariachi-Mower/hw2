#ifndef AUSER_H
#define AUSER_H
#include <iostream>
#include <deque>
#include <string>
#include "user.h"
#include "product.h"


//a derived class of User with a deque (cart) containing the items in their cart.
class AUser : public User
{
public:
    AUser(std::string name, double balance, int type);
    ~AUser();
    void dump(std::ostream& os);
    std::deque<Product*>& getCart();//getter for cart
private:
    std::deque<Product*> cart;//deque containing a user's items
};
#endif