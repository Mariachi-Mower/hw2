#include <iostream>
#include <deque>
#include <fstream>
#include <iomanip>
#include "product.h"
#include "user.h"
#include "auser.h"

AUser::AUser(std::string name, double balance, int type) : 
    User(name, balance, type)
{

}

AUser::~AUser()
{

}

void AUser::dump(std::ostream& os){
    os << getName() << " " << std::setprecision(2) << std::fixed << getBalance() << "\n";
    std::deque<Product*>::iterator it = cart.begin();
    os << "Cart Items: " << "\n";
    int lineNo = 1;
    if(cart.size() == 0){
        os<< "Cart Empty" << "\n" << "\n";
    }
    for(; it != cart.end(); it++){
        os << lineNo << ". " << (*it)->getName() << " " << "\n" << "\n";
        lineNo++;
    }
}

std::deque<Product*>& AUser::getCart(){
    return cart;
}