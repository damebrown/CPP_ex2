//
// Created by daniel.brown1 on 9/3/18.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "ikea.h"

/**menu messages**/
#define MENU_MSG_1 "1. Input stock from file"
#define MENU_MSG_2 "2. Find item by catalog number"
#define MENU_MSG_3 "3. Find item by name"
#define MENU_MSG_4 "4. Print stock by catalog number"
#define MENU_MSG_5 "5. Print stock by name"
#define MENU_MSG_6 "6. Sell item"
#define MENU_MSG_7 "7. Exit"
/**error messages**/
#define ERR_MISSING_ITEM_MSG "Item not found\n"
#define ERR_DELIMITER_MSG "Error: wrong delimiter format in input file.\n"
#define ERR_PRODUCT_FORMAT_MSG "Error: wrong product format in input file.\n"
#define ERR_FILE "Error: something is wrong with the file input.\n"
#define ERR_INVALID_QUANTITY "Error: wrong quantity format.\n"
/**user interface messages**/
#define SELL_DISCRETE "Please enter number of items:\n"
#define SELL_CONTINUOUS "Please enter desired quantity:\n"
#define OUT_OF_STOCK "Not enough stock to sell\n"
#define PATH_REQUEST "please enter file path: "
#define ID_REQUEST "please enter catalog id: "
#define NAME_REQUEST "please enter product name: "
/**max number of allowed delimiters**/
#define MAX_DELIMITERS 1

using namespace std;

bool ikea::compareByID(Product *a, Product *b)
{
    return (a->_id < b->_id);
}

bool ikea::compareByName(Product *a, Product *b)
{
    int i = 0;
    char charA = a->_name[i], charB = b->_name[i];
    while (charA == charB)
    {
        i++;
        charA = a->_name[i], charB = b->_name[i];
    }
    return (charA < charB);
}

void ikea::sortByName()
{
    sort(_existingProducts.begin(), _existingProducts.end(), compareByName);
}

void ikea::sortByID()
{
    sort(_existingProducts.begin(), _existingProducts.end(), compareByID);
}

bool ikea::nameCheck(Product &oldProduct, string nameLine)
{
    size_t found = nameLine.find(NAME, 0);
    if (found == string::npos)
    {
        return false;
    }
    string name = nameLine.substr(sizeof(NAME), (nameLine.size() - sizeof(NAME)));
    if (name[name.length() - 1] == '\r')
    {
        name = name.substr(0, name.length() - 1);
    }
    if (name.empty())
    {
        cerr << ERR_NAME << endl;
        return false;
    }
    return (oldProduct._name == name);
}

/**
 * checks that integers are indeed inputed as integers and not doubles.
 * @param doubleID- the input as a double.
 * @return- true iff doubleID == (int)doubleID
 */
bool intValidityCheck(double doubleID)
{
    auto intId = (int) doubleID;
    return (intId == doubleID);
}

bool ikea::existingSupplyValidtyCheck(Product &existingProduct, vector<string> &lines)
{
    string idLine = lines[ID_INDEX], nameLine = lines[NAME_INDEX], quantityLine = \
                    lines[QUANTITY_INDEX];
    double id = 0;
    stringstream id_ss(idLine.substr(sizeof(ITEM), idLine.size()));
    id_ss >> id;
    if ((nameCheck(existingProduct, nameLine)) && (existingProduct._id == id))
    {
        size_t found = quantityLine.find(QUANTITY, 0);
        if (found == string::npos)
        {
            return false;
        }
        double quantity;
        stringstream q_ss(quantityLine.substr(sizeof(QUANTITY), quantityLine.size()));
        q_ss >> quantity;
        string stringQuantity = to_string(quantity);
        if ((!existingProduct._isContinuous) && (Product::isFloat(stringQuantity)))
        {
            cerr << ERR_INVALID_QUANTITY << endl;
            return false;
        }
        existingProduct._quantity += quantity;
        return true;
    }
    return false;
}

void ikea::duplicateCheck(string &newName)
{
    int counter = 0;
    for (Product *product : _existingProducts)
    {
        if (product->_name == newName)
        {
            counter++;
            (counter < 2) ? _sameNameFlag : (_sameNameFlag = (counter >= 2));
            if (_sameNameFlag)
            {
                break;
            }
        }
    }
}

bool ikea::productFactory(vector<string> &lines)
{
    Product *newProduct = nullptr;
    bool validityFlag = false;
    switch (lines.size())
    {
        default:
            validityFlag = (lines.size() == MINIMAL_ARGS);
            if (validityFlag)
            {
                newProduct = new Product;
            }
            break;
        case 5:
        {
            if (Fabric::argsCheck(lines))
            {
                newProduct = new Fabric;
            }
            else if (Candy::argsCheck(lines))
            {
                newProduct = new Candy;
            }
            else if (Furniture::argsCheck(lines))
            {
                newProduct = new Furniture;
            }
            validityFlag = (newProduct != nullptr);
            break;
        }
        case 6:
        {
            if (KitchenWare::argsCheck(lines))
            {
                newProduct = new KitchenWare;
            }
            validityFlag = (newProduct != nullptr);
            break;
        }
        case 7:
        {
            if (TablesAndChairs::argsCheck(lines))
            {
                newProduct = new TablesAndChairs;
            }
            else if (CultureProduct::argsCheck(lines))
            {
                newProduct = new CultureProduct;
            }
            validityFlag = (newProduct != nullptr);
            break;
        }
    }
    if (!validityFlag)
    {
        delete newProduct;
        return validityFlag;
    }
    if (!_sameNameFlag)
    {
        this->duplicateCheck(newProduct->_name);
    }
    _existingProducts.push_back(newProduct);
}

bool ikea::legalType(vector<string> &lines)
{
    bool validityFlag = false;
    switch (lines.size())
    {
        default:
            validityFlag = (lines.size() == MINIMAL_ARGS);
            validityFlag = (validityFlag) ? Product::argsCheck(lines) : false;
            break;
        case 5:
        {
            validityFlag = (Fabric::argsCheck(lines));
            validityFlag = (validityFlag) ? true : (Candy::argsCheck(lines));
            validityFlag = (validityFlag) ? true : (Furniture::argsCheck(lines));
            break;
        }
        case 6:
        {
            validityFlag = (KitchenWare::argsCheck(lines));
            break;
        }
        case 7:
        {
            validityFlag = (TablesAndChairs::argsCheck(lines));
            validityFlag = (validityFlag) ? true : (CultureProduct::argsCheck(lines));
            break;
        }
    }
    return validityFlag;
}

bool ikea::newSupplyValidtyCheck(vector<string> &lines)
{
    if (!legalType(lines))
    {
        return false;
    }
    bool test1 = productFactory(lines);
    if (test1)
    {
        bool test2 = _existingProducts.back()->assignFields(lines);
        return test2;
    }
    return test1;
}

/**
 * checks validity of the delimiter in the file.
 * @param line- the line of the delimiter.
 * @param inputFile- the input file.
 * @return- true iff the delimiter's amount and content is valid, false otherwise.
 */
bool delimiterValidity(string &line, istream &inputFile)
{
    int counter = 0;
    while ((getline(inputFile, line)) && ((line == DELIMITER) || (line.empty())))
    {
        (line == DELIMITER) ? counter++ : counter;
    }
    return (counter > MAX_DELIMITERS) ? (counter <= MAX_DELIMITERS) : true;
}

/**
 * extracts the id out of the line.
 * @param line- line of id
 * @return- the id number
 */
int getID(string &line)
{
    size_t found = line.find(ITEM, 0);
    if (found == string::npos)
    {
        cerr << ERR_PRODUCT_FORMAT_MSG;
        return false;
    }
    double doubleID = 0;
    stringstream ss(line.substr(sizeof(ITEM), line.size()));
    ss >> doubleID;
    if (!intValidityCheck(doubleID))
    {
        cerr << ERR_PRODUCT_FORMAT_MSG;
        return false;
    }
    auto intID = (int) doubleID;
    return intID;
}

void ikea::receiveSupply()
{
    string _fileName, line;
    cout << PATH_REQUEST << endl;
    cin >> _fileName;
    bool newProductFlag = true;
    ifstream inputFile;
    inputFile.open(_fileName);
    if (!inputFile.is_open())
    {
        cerr << ERR_FILE;
        return;
    }
    while (getline(inputFile, line))
    {
        //new product section in the input file
        vector<string> linesVec;
        if (line == DELIMITER)
        {
            if (!delimiterValidity(line, inputFile))
            {
                cerr << ERR_DELIMITER_MSG;
            }
            getline(inputFile, line);
        }
        linesVec.insert(linesVec.begin(), line);
        int id = getID(line);
        if (!id)
        {
            return;
        }
        for (Product *product : _existingProducts)
        {
            if (product->_id == id)
            {
                newProductFlag = false;
                while (line[0] != '-')
                {
                    getline(inputFile, line);
                    if (line[0] != '-')
                    {
                        linesVec.insert(linesVec.end(), line);
                    }
                }
                if (!(existingSupplyValidtyCheck(*product, linesVec)))
                {
                    cerr << ERR_PRODUCT_FORMAT_MSG;
                    return;
                }
                break;
            }
        }
        if (!newProductFlag)
        {
            break;
        }
        while (line[0] != '-')
        {
            getline(inputFile, line);
            if ((!line.empty()) && (line[0] != '-'))
            {
                linesVec.insert(linesVec.end(), line);
            }
        }
        if (!(newSupplyValidtyCheck(linesVec)))
        {
            cerr << ERR_PRODUCT_FORMAT_MSG;
            return;
        }
    }
    inputFile.close();
}

void ikea::printCatalogue()
{
    for (Product *product: _existingProducts)
    {
        product->printProduct();
    }
    cout << "\n";
}

void ikea::printItem(string name)
{
    for (Product *product: _existingProducts)
    {
        if (product->_name == name)
        {
            product->printProduct();
            return;
        }
    }
    cerr << ERR_MISSING_ITEM_MSG;
}

void ikea::printItem(int id)
{
    for (Product *product: _existingProducts)
    {
        if (product->_id == id)
        {
            product->printProduct();
            return;
        }
    }
    cerr << ERR_MISSING_ITEM_MSG;
}

void ikea::sellItem()
{
    int id;
    cin >> id;
    bool found = false;
    for (Product *product: _existingProducts)
    {
        if (product->_id == id)
        {
            found = true;
            (product->getContinuity()) ? cout << SELL_CONTINUOUS : cout << SELL_DISCRETE;
            double amount;
            cin >> amount;
            if (product->_quantity >= amount)
            {
                product->_quantity -= amount;
                product->printContinuousProduct();
                return;
            }
            cerr << OUT_OF_STOCK;
        }
    }
    if (!found)
    {
        cerr << ERR_MISSING_ITEM_MSG;
    }
}

bool ikea::getInput(int input)
{
    switch (input)
    {
        case 1:
            receiveSupply();
            return false;
        case 2:
        {
            cout << ID_REQUEST;
            int _idNumber;
            cin >> _idNumber;
            printItem(_idNumber);
            return false;
        }
        case 3:
        {
            cout << NAME_REQUEST << endl;
            string _productName;
            getline(cin, _productName);
            printItem(_productName);
            return false;
        }
        case 4:
        {
            sortByID();
            printCatalogue();
            return false;
        }
        case 5:
        {
            sortByName();
            printCatalogue();
            return false;
        }
        case 6:
        {
            sellItem();
            return false;
        }
        case 7:
            cout << "\n";
            return true;
        default:
            return false;
    }
}

void ikea::printMenu()
{
    cout << MENU_MSG_1 << endl <<
         MENU_MSG_2 << endl <<
         MENU_MSG_3 << endl <<
         MENU_MSG_4 << endl <<
         MENU_MSG_5 << endl <<
         MENU_MSG_6 << endl <<
         MENU_MSG_7 << endl;
}

int main()
{
    bool exitFlag = false;
    ikea catalogue;
    while (!exitFlag)
    {
        ikea::printMenu();
        int input = 0;
        cin >> input;
        cin.ignore();
        exitFlag = catalogue.getInput(input);
    }
    return 0;
}

