//
// Created by daniel.brown1 on 9/3/18.
//

#include <iostream>
#include <iomanip>
#include "Product.h"


using namespace std;


void Product::printContinuousProduct()
{
    cout << fixed;
    cout << setprecision(2) << ITEM << " " << _id << "\n" << NAME << " " << _name << "\n" <<
         QUANTITY << " " << _quantity << "\n" << PRICE << " " << _price << "\n";
}

void Product::printNonContinuousProduct()
{
    cout << setprecision(0);
    cout << ITEM << " " << _id << "\n";
    cout << NAME << " " << _name << "\n";
    cout << QUANTITY << " " << _quantity << "\n";
    cout << fixed;
    cout << setprecision(2) << PRICE << " " << _price << "\n";
}

bool Product::assignDefaultFields(vector<string> &lines)
{
    bool successFlag = true;
    for (int index = 0; index < MINIMAL_ARGS; index++)
    {
        string line = lines[index];
        if (!successFlag)
        {
            return successFlag;
        }
        switch (index)
        {
            case ID_INDEX:
            {
                int id;
                stringstream ss(line.substr(sizeof(ITEM), line.size()));
                ss >> id;
                this->_id = id;
                break;
            }
            case NAME_INDEX:
            {
                size_t found = line.find(NAME, 0);
                if (found != string::npos)
                {
                    string name = line.substr(sizeof(NAME), (line.size() - sizeof(NAME)));
                    if (!name.empty())
                    {
                        if (name[name.length() - 1] == '\r')
                        {
                            name = name.substr(0, name.length() - 1);
                        }
                        this->_name = name;
                        break;
                    }
                }
                cerr << ERR_NAME << endl;
                successFlag = false;
                break;
            }
            case QUANTITY_INDEX:
            {
                double quantity;
                stringstream ss(line.substr(sizeof(QUANTITY), line.size()));
                ss >> quantity;
                this->_quantity = quantity;
                break;
            }
            case PRICE_INDEX:
            {
                double price;
                stringstream ss;
                ss << setprecision(15) << line.substr(sizeof(PRICE), line.size());
                ss >> price;
                this->_price = price;
                break;
            }
            default:
                successFlag = false;
                break;
        }
    }
    return successFlag;
}

bool Product::categoryCheck(string line, string fieldName)
{
    //validity of quantity
    if (fieldName == QUANTITY)
    {
        double quantity;
        stringstream ss(line.substr(sizeof(QUANTITY), line.size()));
        ss >> quantity;
        string stringQuantity = to_string(quantity);
        for (char digit : stringQuantity)
        {
            if ((!isdigit(digit)) && (isspace(digit)))
            {
                return false;
            }
        }
        return true;
    }
    else if ((fieldName == PRICE) || (fieldName == WEIGHT) || (fieldName == YEAR) || (fieldName == \
                LENGTH) || (fieldName == CAPACITY) || (fieldName == CALORIES))
    {
        double numerous;
        stringstream ss(line.substr(sizeof(PRICE), line.size()));
        ss >> numerous;
        string stringQuantity = to_string(numerous);
        for (char c : stringQuantity)
        {
            if ((!isdigit(c)) && (isspace(c)))
            {
                return false;
            }
        }
        return true;
    }
    else if (fieldName == DIMENSIONS)
    {
        double x, y, z;
        stringstream ss(line.substr(sizeof(DIMENSIONS), line.size()));
        ss >> x >> y >> z;
        string _x = to_string(x), _y = to_string(y), _z = to_string(z);
        bool xFlag = (!isFloat(_x)), yFlag = (!isFloat(_y)), zFlag = (!isFloat(_z));
        //flags are true if the double is not a float- either an int or a non-number
        xFlag = (xFlag) ? (x >= 0) : true;
        yFlag = (yFlag) ? (y >= 0) : true;
        zFlag = (zFlag) ? (z >= 0) : true;
        return ((xFlag) && (yFlag) && (zFlag));
    }
    else if ((fieldName == AUTHOR) || (fieldName == COLOR) || (fieldName == MATERIAL) ||
             (fieldName == NAME))
    {
        return true;
    }
    return false;
}
