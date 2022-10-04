#include <queue>
#include <set>
#include <vector>
#include <fstream>
#include <map>
#include "product.h"
#include "user.h"
#include "dataBase.h"
#include "util.h"
#include "auser.h"


DataBase::DataBase(){
    //constructor for database
}

DataBase::~DataBase(){
    std::set<User*>::iterator it = Us.begin();
    for(;it != Us.end(); it++){
        delete *it;
    }
    std::set<AUser*>::iterator at = users_.begin();
    for(;at != users_.end(); at++){
        delete *at;
    }
    std::map<Product*, std::set<std::string>>::iterator pt = products_.begin();
    for(;pt != products_.end(); pt++){
        delete pt->first;
    }
    //destructor for database
}

void DataBase::addProduct(Product* P){
    std::set<std::string> final = P->keywords();//iterates through a product's keywords.
    products_.insert({P, final});//adds the product to the map of products and their keywords.
    std::set<std::string>::iterator it = final.begin();
    for(;it != final.end(); it++){
        std::map<std::string, std::set<Product*>>::iterator m = words_.find(*it);
        if(m != words_.end()){//if the word already exists, add P to its set of products
            m->second.insert(P);
        }
        else{//if the word is new, then create a new pair and insert it into the map of words to products.
            //create a an empty set.
            //add the product star to that set.
            //insert pair into words map.
            std::set<Product*> dummy;
            dummy.insert(P);
            words_.insert(std::make_pair(*it, dummy));
        }
    }
}


void DataBase::addUser(User* u){
    //this function takes a User* and makes a new Amazon user (AUser)
    Us.insert(u);
    AUser* temp = new AUser(u->getName(), u->getBalance(), 1);
    users_.insert(temp);
    names_.insert(std::make_pair(temp->getName(), temp));
}


std::vector<Product*> DataBase::search(std::vector<std::string>& terms, int type){
    std::vector<std::string>::iterator it = terms.begin();
    std::map<std::string, std::set<Product*>>::iterator m = words_.begin();
    std::set<Product*> mid;
    m = words_.find(*it);
    mid = m->second;
    it++;
    for(; it != terms.end(); it++){//for each term in the terms vector.

        m = words_.find(*it);//searches the map of keywords to find that keyword's products. Assuming the word exists.
        //m is the set of products for that keyword.

        if(type == 1){//if the user wanted an OR search.
            //the loop will union all sets containing a keyword in the vector.
            //the last set will provide all products that contained any of the words.
            mid = setUnion(mid, m->second);
        }
        else if(type == 0){//if the user wanted an AND search
            //the loop will perform an intersection on all sets containing a vector keyword.
            //the last set will provide all products that contained all the keywords.
            mid = setIntersection(mid, m->second);
        }
    }
    std::vector<Product*> final;
    std::set<Product*>::iterator x = mid.begin();
    for(; x != mid.end(); x++){
        //this loop pushes the values in the set searched to a vector
        //to match the return type.
        final.push_back(*x);
    }
    return final;
}


void DataBase::dump(std::ostream& ofile){
    ofile << "<Products>" << "\n";
    std::map<Product*, std::set<std::string>>::iterator it = products_.begin();
    //This function iterates through the map of products_ and key
    for(; it != products_.end(); it++){
        it->first->dump(ofile);
    }
    //iterates through every product int the products array and then outputs each of their individual dumps.
    ofile << "</Products>"  << "\n" << "<Users>" << "\n";
    std::set<AUser*>::iterator at = users_.begin();
    for(; at != users_.end(); at++){
        (*at)->dump(ofile);
    }
    //same for every user.
    ofile << "</Users> " << "\n";
}


void DataBase::addToCart(std::string username, int index, std::vector<Product*>& hits){
    //given the username an which index they chose
    std::map<std::string, AUser*>::iterator u = names_.find(username);//given a user's name finds a pointer to that user.
    std::vector<Product*>::iterator it = hits.begin();
    it += index -1;//finds the string at the index given in the vector.
    u->second->getCart().push_back(*it);
    //pushes back to that cart.
}


std::vector<Product*> DataBase::viewCart(std::string username){
    std::map<std::string, AUser*>::iterator name = names_.find(username);//finds the AUser from the name provided.
    std::deque<Product*>::iterator it = name->second->getCart().begin();
    std::vector<Product*> final;
    for(; it != name->second->getCart().end(); it++){//iterates through the AUser's cart
        final.push_back(*it);//pushes every value into a vector maintaining the cart's order.
    }
    return final;//returns the vector copy of the cart for the user to print/view in the terminal.
}


void DataBase::buyCart(std::string username){
    std::map<std::string, AUser*>::iterator name = names_.find(username);//finds the AUser from the name provided.
    std::deque<Product*>::iterator it = name->second->getCart().begin();
    while(it != name->second->getCart().end()){//iterates through the AUser's cart.
        it = name->second->getCart().begin();//at the start of every iteration gets an iterator to the start of the deque.
        if((name->second->getBalance() >= (*it)->getPrice()) && (*it)->getQty() > 0){
            //if the user has enough money AND the product is in stock.
            (*it)->subtractQty(1);//reduces stock by one.
            name->second->deductAmount((*it)->getPrice());//subtracts the price from the AUser's balance.
            name->second->getCart().pop_front();//removes the product* from the deque.
        }
        it++;
        //if statement that will end when 
    }
}