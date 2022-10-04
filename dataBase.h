#ifndef DATABASE_H
#define DATABASE_H
#include <set>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <map>
#include <fstream>
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "auser.h"


class DataBase : public DataStore
{
public:
    DataBase();
    ~DataBase();

    //For each of a product's keywords, finds all prods that contain it.
    //if the word is new makes a new set and maps them together.
    //if the word exists adds the product to that existing map's set.
    void addProduct(Product* P);

    //given a user*, creates a deque cart for their products and
    //adds them to the map of user*.
    void addUser(User* u);

    //given a username, finds that user and prints its cart to terminal.
    std::vector<Product*> viewCart(std::string username);

    //given the terms the user wants, performs an AND/OR search. returns the set containing appropriate terms.
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    //iterates through map of product* and performs their dump functions.
    //iterates through map of user* and perfoms their dump functions.
    void dump(std::ostream& ofile);

    //given an username and int index from hits vector,
    //adds that product* to the User's cart queue.
    void addToCart(std::string username, int index, std::vector<Product*>& hits);

    //given a username,iterates through a cart in FIFO order.
    //if enough money and in stock, removes item from cart, deducts stock by 1 for each item purchased.
    //does nothing when not in stock of not enough money to purchase.
    void buyCart(std::string username);

private:

    std::set<User*> Us;
    //map of users and their names.
    std::map<std::string, AUser*> names_;

    //set of users.
    std::set<AUser*> users_;

    //map of products and their keywords.
    std::map<Product*, std::set<std::string>> products_;//map of prods and their keywords.
    
    //map of keywords and their products.
    std::map<std::string, std::set<Product*>> words_;//map of keywords and their prods.
};
#endif