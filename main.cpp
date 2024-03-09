// Jake Kistler
// Template Sorting of ints, doubles, strings, complex numbers, roman numerals, and big ints

#include <iostream>
#include <string>
#include <fstream>

#include "ComplexNumber.h"
#include "Roman.h"
#include "BigInteger.h"

using namespace std;

template <typename T>
void exchangeSort(T *theArray, int size);

template <typename T>
void displayArrayToFile(T theArray[], int size, const string &type, ostream &fout);

template <typename T>
void displayArrayToConsole(T theArray[], int size, const string &type);

int main()
{
    string fileName;
    cout << "Welcome to the template sorter!\n";
    cout << "Please enter the filename: ";
    getline(cin, fileName);

    size_t lastDot = fileName.find_last_of("."); // looking for the . that starts the file extension
    string baseName = (lastDot == string::npos) ? "" : fileName.substr(0, lastDot); // if found create a new string with the characters from index 0 to prior to the dot, the string contains only the file name
    string outputFileName = baseName + "_OUT.txt"; // append the new ending of the name to the new string

    ifstream fin(fileName);
    ofstream fout(outputFileName);

    if (!fin)
    {
        cout << "Error: Could not open file " << fileName << endl;
        return 1;
    }

    if(!fout)
    {
        cout << "Error: Could not create file " << outputFileName << endl;
        return 1;
    }

    

    int integerArr[10];
    double dubArr[10];

    string strArr[10];
    ComplexNumber complexArr[10];

    Roman romArr[10];
    BigInteger bigArr[10];

    for (int i = 0; i < 10; ++i)
    {
        fin >> integerArr[i];
    }

    //displayArrayToConsole(integerArr, 10, "int");
    displayArrayToFile(integerArr, 10, "int", fout);

    exchangeSort(integerArr, 10);

    //displayArrayToConsole(integerArr, 10, "int");
    displayArrayToFile(integerArr, 10, "int", fout);

    for (int i = 0; i < 10; ++i)
    {
        fin >> dubArr[i];
    }

    //displayArrayToConsole(dubArr, 10, "double");
    displayArrayToFile(dubArr, 10, "double", fout);

    exchangeSort(dubArr, 10);

    //displayArrayToConsole(dubArr, 10, "double");
    displayArrayToFile(dubArr, 10, "double", fout);

    fin.get(); // moves the reading point past the new line character that separates the doubles and strings

    for (int i = 0; i < 10; ++i)
    {
        getline(fin, strArr[i]);
    }

    //displayArrayToConsole(strArr, 10, "string");
    displayArrayToFile(strArr, 10, "string", fout);

    exchangeSort(strArr, 10);

    //displayArrayToConsole(strArr, 10, "string");
    displayArrayToFile(strArr, 10, "string", fout);

    for (int i = 0; i < 10; ++i)
    {
        double real, imag;
        fin >> real >> imag;
        complexArr[i] = ComplexNumber(real, imag);
    }

    //displayArrayToConsole(complexArr, 10, "complex");
    displayArrayToFile(complexArr, 10, "complex", fout);

    exchangeSort(complexArr, 10);

    //displayArrayToConsole(complexArr, 10, "complex");
    displayArrayToFile(complexArr, 10, "complex", fout);

    for(int i = 0; i < 10; i++)
    {
        string value;
        fin >> value;
        romArr[i] = Roman(value);
    }

   //displayArrayToConsole(romArr, 10, "Roman");
    displayArrayToFile(romArr, 10, "Roman", fout);

    exchangeSort(romArr, 10);

    //displayArrayToConsole(romArr, 10, "Roman");
    displayArrayToFile(romArr, 10, "Roman", fout);

    fin.get();

    for(int i = 0;  i< 10; i++)
    {
       int num;
       fin >> num;
       bigArr[i] = BigInteger(num);
    }

    //displayArrayToConsole(bigArr, 10, "Big Int");
    displayArrayToFile(bigArr, 10, "Big Int", fout);

    exchangeSort(bigArr, 10);

    //displayArrayToConsole(bigArr, 10, "Big Int");
    displayArrayToFile(bigArr, 10, "Big Int", fout);

    fin.close();
    fout.close();

    cout << "See " << outputFileName << " for output " << endl << endl;


    cout << "*********************************************************************************************************\n";
    cout << "For screen shot purposes the output was also written to the console, it will be committed out when submitted!\n";
    cout << "*********************************************************************************************************\n";

    displayArrayToConsole(integerArr, 10, "Integer");
    displayArrayToConsole(dubArr, 10, "Double");

    displayArrayToConsole(strArr, 10, "String");
    displayArrayToConsole(complexArr, 10, "Complex");
    
    displayArrayToConsole(romArr, 10, "Roman");
    displayArrayToConsole(bigArr, 10, "BigInt");

    return 0;
}

template <typename T>
void exchangeSort(T *theArray, int size)
{
    T buffer;
    for (int k = 1; k < size; k++)
    {
        for (int i = 0; i < size - k; i++)
        {
            if (theArray[i] > theArray[i + 1])
            {
                buffer = theArray[i];
                theArray[i] = theArray[i + 1];
                theArray[i + 1] = buffer;
            }
        }
    }
}

template <typename T>
void displayArrayToFile(T theArray[], int size, const string &type, ostream &fout)
{
    //cout << "Displaying the " << type << " array:" << endl;
    for (int i = 0; i < size; i++)
    {
        fout << theArray[i] << endl;
    }
    fout << endl;
}

template <typename T>
void displayArrayToConsole(T theArray[], int size, const string &type)
{
    cout << "Displaying the " << type << " array:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << theArray[i] << endl;
    }
    cout << endl << endl << endl;
}
