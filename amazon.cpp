#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "dataBase.h"

using namespace std;

struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};

void displayProducts(vector<Product*>& hits);

void displayCart(std::vector<Product*>& cart);//function to display the contents of a user's cart.



int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    DataBase ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else if( cmd == "ADD"){
                std::string username;
                int index;
                if((ss >> username >> index)){
                    if(index <= 0 || index > (int)hits.size()){
                        cout << "invalid request" << endl;
                        continue;
                    }
                    else if(ds.getNames_().find(username) == ds.getNames_().end()){
                        cout << "invalid request" << endl;
                        continue;
                    }
                    ds.addToCart(username, index, hits);
                }
                else{
                    cout << "Invalid request" << endl;
                    //return 3;
                }
            }
            else if( cmd == "VIEWCART"){
                string username;
                if((ss >> username)){
                    std::vector<Product*> cart_ = ds.viewCart(username);
                    displayCart(cart_);
                }
                else{
                    cout << "Invalid request" << endl;
                }
            }
            else if( cmd == "BUYCART"){
                string username;
                if((ss >> username)){
                    //ds.buyCart(username);
                    std::vector<Product*> cart_ = ds.viewCart(username);
										if(*cart_.begin() == NULL){
											cout << "Invalid username" << endl;
											continue;
										}
										ds.buyCart(username);
                    //displayCart(cart_);
                }
                else{
                    cout << "Invalid request" << endl;
                }
            }
            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
        //iterates through vector of Products that fit the terms.
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        //prints out each result.
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
} 


void displayCart(std::vector<Product*>& cart){
    //this function takes the vector produced by buyCart
    if(cart.begin() == cart.end()){
      //if no products matched the search, prints out "cart empty"
        cout << "Cart Empty" << endl;
        return;
    }
    else if(*cart.begin() == NULL){
        cout << "Invalid username" << endl;
        return;
    }
    vector<Product*>::iterator it = cart.begin();
    int x = 1;
    for(; it != cart.end(); it++){
      //otherwise iterates through vector and displays string for each product.
        cout << "Item " << x << ":   " << endl;
        cout << (*it)->displayString() << endl << endl;
        x++;
    }
}