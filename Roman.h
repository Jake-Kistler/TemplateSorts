// Jake Kistler
// Advanced cpp
// OCCC Fall 2023
// Roman numbers done as a class

#ifndef ROMAN
#define ROMAN

#include <string>
#include <stdexcept>
#include <iostream>
#include <cctype>

using namespace std;

class InvalidRomanNumberException : public runtime_error
{
public:
    InvalidRomanNumberException(const string message) : runtime_error(message)
    {
    }
};

class Roman
{
private:
    int theValue;
    static const int maxValue = 4999;

    bool isValidRomanNumber(const string &roman)
    {

        string validSymbols = "IVXLCDM";

        for (char ch : roman)
        {
            if (validSymbols.find(toupper(ch)) == string::npos)
                return false;
        }

        return true;
    }

    bool isValidDecimalNumber(string num)
    {
        // Loop across the string and test aginst isDigit

        for (int i = 0; i < num.length(); i++)
        {
            if (!isdigit(num[i]))
            {
                return false;
            }
        }

        return true;

    } // END OF FUNCTION

    int convertRomanToDecimal(const string &roman)
    {
        string upper;
        for (char ch : roman)
        {
            upper += toupper(ch);
        }

        string result = ""; // the result

        string symbol[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        int numericalValue[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

        /*
        Set the accumulator to zero.
        • Parse from left to right. (done with the loop)
        1) If the symbol you see is followed by a symbol of equal or lesser value (handles with the string and int declarations)
            o Consume that symbol and add that value to the accumulator
        2) If the symbol you see is followed by a symbol of greater value
            o Consume both symbols and add their difference to the accumulator
        • Continue until the string has been consumed.
        */

        int accumulator = 0;
        int sightedSymbol = 0;

        while (sightedSymbol < upper.length())
        {
            for (int i = 0; i < 13; i++)
            {
                if (upper.substr(sightedSymbol, symbol[i].length()) == symbol[i])
                {
                    accumulator += numericalValue[i];
                    sightedSymbol += symbol[i].length();
                    break;
                }
            } // END FOR
        }     // END WHILE

        return accumulator;
    }

public:
    // default constructor
    Roman()
    {
        theValue = 1;
    }

    // int constructor
    Roman(int value)
    {
        if (value <= 0 || value > maxValue)
        {
            throw InvalidRomanNumberException("Invalid value");
        }

        theValue = value;
    }

    Roman(double value)
    {
        int x = static_cast<int>(value);

        if (x <= 0 || x > maxValue)
        {
            throw InvalidRomanNumberException("Invalid Value");
        }

        theValue = x;
    }

    // string constructor
    Roman(const string &str)
    {
        if (isValidRomanNumber(str))
        {
            theValue = convertRomanToDecimal(str);
        }
        else
        {
            try
            {
                theValue = stoi(str); // Convert the string to an int
                if (theValue <= 0 || theValue > maxValue)
                {
                    throw InvalidRomanNumberException("Value out of range");
                }
            }
            catch (invalid_argument &e)
            {
                // The string is not a valid Roman numeral or a valid decimal number
                throw InvalidRomanNumberException("Invalid Roman numeral or decimal number");
            }
        }
    }

    // coppy constrcutor
    Roman(const Roman &ro)
    {
        theValue = ro.theValue;
    }

    string toString() const
    {
        static const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        static const char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        string result;
        int number = theValue;

        for (int i = 0; i < sizeof(values) / sizeof(int); i++)
        {
            while (number >= values[i])
            {
                result += symbols[i];
                number -= values[i];
            }
        }

        return result;
    }

    // type casts
    operator int() const
    {
        return theValue;
    }

    operator double() const
    {
        return static_cast<double>(theValue);
    }

    operator string() const
    {
        return toString();
    }

    friend ostream &operator<<(ostream &os, const Roman &roman)
    {
        os << roman.toString();
        return os;
    }

    bool operator>(const Roman &other) const
    {
        return this->theValue > other.theValue;
    }

    // Overload the less than operator
    bool operator<(const Roman &other) const
    {
        return this->theValue < other.theValue;
    }
};

#endif