// Jake Kistler
// Advacnced cpp
// OCCC Fall 2023
// Big interger done as a class, as it should be
#ifndef BIGINTERGER
#define BIGINTERGER
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class BigInteger
{
private:
    string value;
    bool sign;

    bool isValidBigInteger(const string &str, int base)
    {
        if (str.empty())
        {
            return false;
        }

        size_t startIndex = 0;
        // Check for a negative sign and skip it if present

        if (str[0] == '-')
        {
            if (str.length() == 1)
            {
                // String contains only '-'
                return false;
            }
            startIndex = 1;
        }

        // Validate the rest of the string
        for (size_t i = startIndex; i < str.length(); ++i)
        {
            char ch = str[i];
            if (base <= 10)
            {
                if (ch < '0' || ch >= '0' + base)
                {
                    return false;
                }
            }
            else
            {
                if (!((ch >= '0' && ch <= '9') ||
                      (ch >= 'A' && ch < 'A' + base - 10) ||
                      (ch >= 'a' && ch < 'a' + base - 10)))
                {
                    return false;
                }
            }
        }

        return true;
    }

    vector<int> addleadingZeros(vector<int> bigInt, int amount)
    {
        for (int i = 0; i < amount; i++)
        {
            bigInt.insert(bigInt.begin(), 0);
        }

        return bigInt;
    }

    vector<int> normalize(vector<int> bigInt, int base)
    {
        vector<int> result = bigInt;
        result = addleadingZeros(result, 1);
        int carry = 0;

        for (int i = result.size() - 1; i >= 0; i--)
        {
            result[i] = result[i] + carry;
            carry = result[i] / base;
            result[i] = result[i] % base;
        }
        return result;
    }

    vector<int> stringToVector(const string &str)
    {
        vector<int> digits;
        for (char ch : str)
        {
            if (isdigit(ch))
            {
                digits.push_back(ch - '0');
            }
        }
        return digits;
    }

    string vectorToString(const vector<int> &digits)
    {
        string str;
        for (int digit : digits)
        {
            str += to_string(digit);
        }
        return str;
    }

    vector<int> addition(const vector<int> &bigInt1, const vector<int> &bigInt2, int base = 10)
    {
        vector<int> result;
        int carryDigit = 0;

        int i = bigInt1.size() - 1;
        int j = bigInt2.size() - 1;

        while (i >= 0 || j >= 0)
        {
            int sum = carryDigit;
            if (i >= 0)
            {
                sum = sum + bigInt1[i];
                i--;
            }
            if (j >= 0)
            {
                sum = sum + bigInt2[j];
                j--;
            }

            carryDigit = sum / 10;
            sum = sum % 10;

            result.insert(result.begin(), sum);
        }

        return result;
    }


public:
    // constructors
    BigInteger()
    {
        value = "0";
        sign = true;
    }

    BigInteger(int number)
    {
        if (number < 0)
        {
            sign = false;
            number = -number;
        }
        else
        {
            sign = true;
        }

        value = to_string(number);
    }

    BigInteger(string val, int base = 10)
    {
        if (isValidBigInteger(val, base))
        {
            // Check and set the sign
            if (val[0] == '-')
            {
                sign = false;
                value = val.substr(1); // Remove the negative sign from the value
            }
            else
            {
                sign = true;
                value = val;
            }
        }
        else
        {
            cout << "String was invalid, building a Big Integer with value of 0" << endl;
            value = "0";
            sign = true;
        }
    }

    BigInteger(const BigInteger &other)
    {
        value = other.value;
        sign = other.sign;
    }

    // destructor, added to cover my bases if necessary
    ~BigInteger()
    {
    }

    // opp overloads

    //BigInteger &operator=(const BigInteger &);

    // Comparison opps

    // Addition
    BigInteger operator+=(const BigInteger &rhs)
    {
        vector<int> thisDigits = stringToVector(this->value);
        vector<int> rhsDigits = stringToVector(rhs.value);

        // call the additon function from the orginal big int code
        vector<int> resultDigits = addition(thisDigits, rhsDigits);

        // convert back to a string
        this->value = vectorToString(resultDigits);

        // handle the sign issue

        return *this;
    }

    BigInteger operator+(const BigInteger &rhs) const
    {
        BigInteger temp = *this;
        temp += rhs;
        return temp;
    }



    // type cast toString
    operator string() const
    {
        return sign ? value : "-" + value;
    }

    string toString() const
    {
        return sign ? value : "-" + value;
    }

    // I/O functions

    friend ostream &operator<<(ostream &out, const BigInteger &big)
    {
        out << big.toString();
        return out;
    }

    friend istream &operator>>(istream &in, BigInteger &big)
    {
        string input;
        in >> input;

        BigInteger temp(input);
        big = temp;

        return in;
    }

    bool operator>(const BigInteger &other) const
    {

        // First, compare the signs
        if (this->sign && !other.sign)
        {
            return true; // positive is greater than negative
        }
        else if (!this->sign && other.sign)
        {
            return false; // negative is not greater than positive
        }

        // If both are negative, reverse the logic
        bool reverseLogic = !this->sign && !other.sign;

        // Then, compare the lengths of the value strings
        if (this->value.length() != other.value.length())
        {
            return reverseLogic ? this->value.length() < other.value.length() : this->value.length() > other.value.length();
        }

        // If lengths are equal, compare digit by digit
        for (size_t i = 0; i < this->value.length(); ++i)
        {
            if (this->value[i] != other.value[i])
            {
                return reverseLogic ? this->value[i] < other.value[i] : this->value[i] > other.value[i];
            }
        }

        // If all digits are equal, then the numbers are not greater or less than each other
        return false;
    }
};

#endif
