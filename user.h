#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>


class User {
public:
    User();
    User(std::string name, double balance, int type);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);
    int getType() const;
    //implement getType in either the auser or user cpp file. 

private:
    std::string name_;
    double balance_;
    int type_;
};
#endif