//
// Created by daniel.brown1 on 9/3/18.
//

#ifndef EX2_IKEA_H
#define EX2_IKEA_H

#include <string>
#include <vector>
#include "Product.h"


using namespace std;

/**
 * ikea class. this class represents an ikea catalogue.
 */
class ikea
{
private:
    /**a vector of all existing products*/
    vector<Product *> _existingProducts;

    /**true iff there are two items with the same name (using for soring purposes)*/
    bool _sameNameFlag = false;

public:
    /**
     * default constructor.
     */
    ikea()
    {
        vector<Product> _existingProducts[1];
    }

    /**
     * this function gets the 1-7 input from the user and calls the appropriate functions
     * accordingly.
     * @param input- the input from the user, an int from 1 to 7.
     * @return- true iff the input is 7, false otherwise.
     */
    bool getInput(int input);

    /**
     * processes the supply input file.
     */
    void receiveSupply();

    /**
     * this function checks validity of existing supply appearing in the input file, and updates
     * the quantity accordingly.
     * @param existingProduct- the existing product shown on the file.
     * @param lines- a strings vector of the product's section lines.
     * @return- true  iff the input is valid and quantity updating done right.
     */
    bool existingSupplyValidtyCheck(Product &existingProduct, vector<string> &lines);

    /**
     * this function checks validity of existing supply appearing in the input file, and updates
     * the catalogue accordingly.
     * @param lines- a string vector of the lines of the new product in the file.
     * @return- true iff the input is valid and the new product was added successfuly.
     */
    bool newSupplyValidtyCheck(vector<string> &lines);

    /**
     * prints the menu to the console.
     */
    static void printMenu();

    /**
     * checks for two products with the same name. sets the _sameNameFlag accordingly.
     * @param newName- the new name to be added.
     */
    void duplicateCheck(string &newName);

    /**
     * sorting the existingProducts vector by name.
     */
    void sortByName();

    /**
     * prints all the products in the catalogue.
     */
    void printCatalogue();

    /**
     * sorting the existingProducts vector by id.
     */
    void sortByID();

    /**
     * printing a single item with the given name (if exists).
     * @param name- the name of the product to print.
     */
    void printItem(string name);

    /**
     * print a single product with the given id.
     * @param id- the id input gotten from the user.
     */
    void printItem(int id);

    /**
     * this function checks the identity of the name of a product in the input file and a product
     * with the same id.
     * @param oldProduct- the existing product with the same id as the new one.
     * @param nameLine- the line in which the name appears in the file.
     * @return- true iff the names are equal.
     */
    bool nameCheck(Product &oldProduct, string nameLine);

    /**
     * checks for validity of the type of the new product according to the fields appearing in
     * the input file.
     * @param lines- a vector of the lines of the new product's declaration.
     * @return- true iff the type is valid (meaning there exists a kind of product with the same
     * fields).
     */
    bool legalType(vector<string> &lines);

    /**
     * this function sells an item according to the user's input.
     */
    void sellItem();

    /**
     * a comparison by name function for std::sort algorithm
     * @param a- reference to product a
     * @param b- reference to product b
     * @return- returns true iff a < b, false otherwise
     */
    static bool compareByName(Product *a, Product *b);

    /**
     * a comparison by id function for std::sort algorithm
     * @param a- reference to product a
     * @param b- reference to product b
     * @return- returns true iff a < b, false otherwise
     */
    static bool compareByID(Product *a, Product *b);

    /**
     * this function creates a new product according to the demand, only if all of the details of
     * the pruducts are correct.
     * @param lines- a string vector of the product's lines.
     * @return- true iff the instanciation went well.
     */
    bool productFactory(vector<string> &lines);
};


#endif //EX2_IKEA_H
