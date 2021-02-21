//
// Created by daniel.brown1 on 9/3/18.
//


#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#ifndef EX2_PRODUCT_H
/**strings of categories**/
#define ITEM "Item:"
#define NAME "Name:"
#define QUANTITY "Quantity:"
#define PRICE "Price:"
#define WEIGHT "Weight:"
#define CALORIES "Calories:"
#define DIMENSIONS "Dimensions:"
#define MATERIAL "Material:"
#define COLOR "Color:"
#define CAPACITY "Capacity:"
#define AUTHOR "Author:"
#define YEAR "Year of publication:"
#define LENGTH "Length:"
#define DELIMITER "-----\r"
/**indices of the categories**/
#define ID_INDEX 0
#define NAME_INDEX 1
#define QUANTITY_INDEX 2
#define PRICE_INDEX 3
#define WEIGHT_INDEX 4
#define CALORIES_INDEX 4
#define DIM_INDEX 4
#define MATERIAL_INDEX 5
#define CAPACITY_INDEX 5
#define COLOR_INDEX 6
#define AUTHOR_INDEX 4
#define YEAR_INDEX 5
#define LENGTH_INDEX 6
/**error messages**/
#define ERR_NAME "Error: wrong product name format.\n"
/**amount of minimal args**/
#define MINIMAL_ARGS 4
/**dot char**/
#define DOT '.'

using namespace std;

/**
 * this class represents a general product, all other classes inherit from it.
 */
class Product
{

protected:
    int _id;
    string _name;
    double _price;
    double _quantity;
    bool _isContinuous;

public:
    /*friend classes */
    friend class ikea;

    /**
     * default constructor;
     */
    Product() : _id(0), _name(""), _price(0), _quantity(0)
    {
        _isContinuous = false;
    };

    /**
     * checks validity of args of all different products.
     * @param lines- the lines of the product.
     * @param args- the product's right args.
     * @return- true iff the lines match the right args.
     */
    static bool allArgsCheck(vector<string> &lines, vector<string> args)
    {
        string category, line;
        for (size_t i = 1; i < args.size(); i++)
        {
            category = args[i];
            line = lines[i];
            size_t find = line.find(category, 0);
            if (find == string::npos)
            {
                return false;
            }
            if (!categoryCheck(line, category))
            {
                return false;
            }
        }
        return true;
    }

    /**
     * by calling allArgsCheck, checks validity of general product's input
     * @param lines- the lines of the genereal product.
     * @return- true iff lines match to product's args.
     */
    static bool argsCheck(vector<string> &lines)
    {
        vector<string> fieldsName = {ITEM, NAME, QUANTITY, PRICE};
        return allArgsCheck(lines, fieldsName);
    }

    /**
     * checks the validity of each categories argument.
     * @param line- the line to check
     * @param fieldName- the field decalared in the line.
     * @return- truee iff the line is a valid declaration of fieldName
     */
    static bool categoryCheck(string line, string fieldName);

    /**
     * print a single general product
     */
    virtual void printProduct()
    {};

    /**
     * prints a single continuous product.
     */
    virtual void printContinuousProduct();

    /**
    * prints a single continuous product.
    */
    virtual void printNonContinuousProduct();

    /**
     * assignes the arguments accepted to the right fields.
     * @param lines- the product's lines.
     * @return- true iff all went well.
     */
    virtual bool assignFields(vector<string> &lines)
    {
        return assignDefaultFields(lines);
    };

    /**
     * assignes all 4 default fields.
     * @return- true iff all went well.
     */
    bool assignDefaultFields(vector<string> &lines);

    /**
     * returns the calsses continuity.
     * @return- true iff the class's product is continuous.
     */
    bool getContinuity()
    {
        return _isContinuous;
    }

    /**
     * checks if a string is a floating point number
     * @param number- the string
     * @return- true iff number is a string of a float. else otherwise (is it's an int or if it
     * has non-digit chars)
     */
    static bool isFloat(string &number)
    {
        bool pointFlag = false;
        for (char c : number)
        {
            pointFlag = (!isdigit(c)) ? (c == DOT) : false;
            if (!pointFlag)
            {
                break;
            }
        }
        return pointFlag;
    }

};

/**
 * this class represents a fabric product.
 */
class Fabric : public Product
{
private:
    double _weight;
    bool _isContinuous;

public:
    friend class Product;

    /**
     * default constructor.
     */
    Fabric() : Product(), _weight(0)
    {
        Fabric::_isContinuous = true;
    };

    /**
     * prints a fabric product.
     */
    void printProduct() override
    {
        Product::printContinuousProduct();
        cout << WEIGHT << " " << _weight << "\n" << setprecision(0) << DELIMITER << "\n";
    }

    /**
     * assignes a fabric product's fields.
     * @return- true iff all went well.
     */
    bool assignFields(vector<string> &lines) override
    {
        bool test = Product::assignDefaultFields(lines);
        if (test)
        {
            string w_line = lines[WEIGHT_INDEX];
            double weight = 0;
            stringstream ss(w_line.substr(sizeof(WEIGHT), w_line.size()));
            ss >> weight;
            _weight = weight;
        }
        return test;
    }

    /**
     * checking if the file's arguments identity to the fabric args.
     * @param lines- the product's file lines
     * @return- true iff the args structure is valid
     */
    static bool argsCheck(vector<string> &lines)
    {
        vector<string> fieldsName = {ITEM, NAME, QUANTITY, PRICE, WEIGHT};
        return Product::allArgsCheck(lines, fieldsName);
    }
};

/**
 * this class represents a candy product.
 */
class Candy : public Product
{
private:
    double _calories;
    bool _isContinuous;

public:
    friend class Product;

    /**
     * default constructor
     */
    Candy() : Product(), _calories(0)
    {
        Candy::_isContinuous = true;
    };

    /**
     * prints a single candy product, overrides the general product's function.
     */
    void printProduct() override
    {
        Product::printContinuousProduct();
        cout << CALORIES << " " << _calories << "\n" << DELIMITER << "\n";
    }

    /**
     * assignes a candy product's fields.
     * @return- true iff all went well.
     */
    bool assignFields(vector<string> &lines) override
    {
        bool test = Product::assignDefaultFields(lines);
        if (test)
        {
            string c_line = lines[CALORIES_INDEX];
            double cal = 0;
            stringstream ss(c_line.substr(sizeof(CALORIES), c_line.size()));
            ss >> cal;
            _calories = cal;
        }
        return test;
    }

    /**
     * checking if the file's arguments identity to the fabric args.
     * @param lines- the product's file lines
     * @return- true iff the args structure is valid
     */
    static bool argsCheck(vector<string> &lines)
    {
        vector<string> fieldsName = {ITEM, NAME, QUANTITY, PRICE, CALORIES};
        return Product::allArgsCheck(lines, fieldsName);
    }
};

/**
 * this class represents a furniture product.
 */
class Furniture : public Product
{
protected:
    bool _isContinuous;
    double _x, _y, _z;

public:
    friend class Product;

    /**
     * default constructor.
     */
    Furniture() : Product(), _x(0), _y(0), _z(0)
    {
        Furniture::_isContinuous = false;
        Furniture::_quantity = (int) _quantity;
    };

    /**
     * prints this class's product product.
     */
    void printProduct() override
    {
        Product::printNonContinuousProduct();
        cout << DIMENSIONS << " " << _x << " " << _y << " " << _z << "\n" << DELIMITER << "\n";
    }

    /**
     * assignes the product's fields.
     * @return- true iff all went well.
     */
    bool assignFields(vector<string> &lines) override
    {
        bool test = Product::assignDefaultFields(lines);
        if (test)
        {
            string d_line = lines[DIM_INDEX];
            double x = 0, y = 0, z = 0;
            stringstream ss(d_line.substr(sizeof(DIMENSIONS), d_line.size()));
            ss >> x >> y >> z;
            _x = x, _y = y, _z = z;
        }
        return test;
    }

    /**
     * checking if the file's arguments identity to the class's args.
     * @param lines- the product's file lines
     * @return- true iff the args structure is valid
     */
    static bool argsCheck(vector<string> &lines)
    {
        vector<string> fieldsName = {ITEM, NAME, QUANTITY, PRICE, DIMENSIONS};
        return Product::allArgsCheck(lines, fieldsName);
    }
};

/**
 * this class represents a table or a chair.
 */
class TablesAndChairs : public Furniture
{
private:
    string _color;
    string _material;

public:
    friend class Product;

    /**
     * default constructor
     */
    TablesAndChairs() : Furniture(), _color(""), _material("")
    {
        TablesAndChairs::_isContinuous = false;
        TablesAndChairs::_quantity = (int) _quantity;
    };

    /**
     * prints this class's product product.
     */
    void printProduct() override
    {
        Product::printNonContinuousProduct();
        cout << DIMENSIONS << " " << _x << " " << _y << " " << _z << "\n" << MATERIAL
             << " " << _material << "\n" << COLOR << " " << _color << "\n" << DELIMITER << "\n";
    }

    /**
     * assignes the product's fields.
     * @return- true iff all went well.
     */
    bool assignFields(vector<string> &lines) override
    {
        bool test = Furniture::assignFields(lines);
        if (test)
        {
            string c_line = lines[COLOR_INDEX], m_line = lines[MATERIAL_INDEX], color, material;
            stringstream color_ss(c_line.substr(sizeof(COLOR), c_line.size()));
            stringstream material_ss(m_line.substr(sizeof(MATERIAL), m_line.size()));;
            color_ss >> color;
            material_ss >> material;
            _material = material, _color = color;
        }
        return test;
    }

    /**
     * checking if the file's arguments identity to the class's args.
     * @param lines- the product's file lines
     * @return- true iff the args structure is valid
     */
    static bool argsCheck(vector<string> &lines)
    {
        vector<string> fieldsName = {ITEM, NAME, QUANTITY, PRICE, DIMENSIONS, MATERIAL, COLOR};
        return Product::allArgsCheck(lines, fieldsName);
    }
};

/**
 * this class represents a kitchenware product.
 */
class KitchenWare : public Product
{
private:
    double _x, _y, _z, _capacity;

public:

    /**
     * default constructor
     */
    KitchenWare() : Product(), _x(0), _y(0), _z(0), _capacity(0)
    {
        _isContinuous = false;
        _quantity = (int) _quantity;
    };

    /**
     * prints this class's product product.
     */
    void printProduct() override
    {
        Product::printNonContinuousProduct();
        cout << DIMENSIONS << " " << _x << " " << _y << " " << _z << "\n" << CAPACITY << " "
             << _capacity << "\n"
             << DELIMITER << "\n";
    }

    /**
     * assignes the product's fields.
     * @return- true iff all went well.
     */
    bool assignFields(vector<string> &lines) override
    {
        bool test = Product::assignDefaultFields(lines);
        if (test)
        {
            string d_line = lines[DIM_INDEX];
            double x = 0, y = 0, z = 0, capacity = 0;
            stringstream ss(d_line.substr(sizeof(DIMENSIONS), d_line.size()));
            ss >> x >> y >> z;
            _x = x, _y = y, _z = z;
            string cap_line = lines[CAPACITY_INDEX];
            stringstream cap_ss(cap_line.substr(sizeof(CAPACITY), cap_line.size()));
            cap_ss >> capacity;
            _capacity = capacity;
        }
        return test;
    }

    /**
     * checking if the file's arguments identity to the class's args.
     * @param lines- the product's file lines
     * @return- true iff the args structure is valid
     */
    static bool argsCheck(vector<string> &lines)
    {
        vector<string> fieldsName = {ITEM, NAME, QUANTITY, PRICE, DIMENSIONS, CAPACITY};
        return Product::allArgsCheck(lines, fieldsName);
    }
};

/**
 * this class represents a book or a movie product.
 */
class CultureProduct : public Product
{
private:
    string _author;
    int _publicationYear;
    int _length;

public:

    /**
     * default constructor
     */
    CultureProduct() : Product(), _author(""), _publicationYear(0), _length(0)
    {
        CultureProduct::_isContinuous = false;
        CultureProduct::_quantity = (int) _quantity;
    };

    /**
     * prints this class's product product.
     */
    void printProduct() override
    {
        Product::printNonContinuousProduct();
        cout << AUTHOR << " " << _author << "\n" << YEAR << " " << _publicationYear << "\n"
             << LENGTH
             << " " << _length << "\n" << DELIMITER << "\n";
    }

    /**
     * assignes the product's fields.
     * @return- true iff all went well.
     */
    bool assignFields(vector<string> &lines) override
    {
        bool test = Product::assignDefaultFields(lines);
        if (test)
        {
            string auth_line = lines[AUTHOR_INDEX], year_line = lines[YEAR_INDEX];
            string length_line = lines[LENGTH_INDEX], authorFirst, authorLast;
            int year = 0, length = 0;
            stringstream author_ss(auth_line.substr(sizeof(AUTHOR), auth_line.size()));
            stringstream year_ss(year_line.substr(sizeof(YEAR), year_line.size()));
            stringstream length_ss(length_line.substr(sizeof(LENGTH), length_line.size()));
            author_ss >> authorFirst;
            author_ss >> authorLast;
            year_ss >> year;
            length_ss >> length;
            _publicationYear = year, _author = authorFirst + " " + authorLast + " ";
            _length = length;
        }
        return test;
    }

    /**
     * checking if the file's arguments identity to the class's args.
     * @param lines- the product's file lines
     * @return- true iff the args structure is valid
     */
    static bool argsCheck(vector<string> &lines)
    {
        vector<string> fieldsName = {ITEM, NAME, QUANTITY, PRICE, AUTHOR, YEAR, LENGTH};
        return Product::allArgsCheck(lines, fieldsName);
    }
};

#endif //EX2_PRODUCT_H