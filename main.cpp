// io manipulation
#include <iostream>
#include <stdio.h>
// containers
#include <vector>
#include <string>
//
#include <bitset>

using namespace std;

string hashing(string data)
{
    string hashingText = data;
    string hashedText;
    string padding = "a1b2c3d4e5f6g7h8i9j0k1l2m3n4o5p6r7s8t9q0v1w2x3y4z5a1b2c3d4e5f6g7";

    bool notPadded = false;

    int stringSize = hashingText.size();

    while (stringSize > 64 && !notPadded)
    {
        if (stringSize < 128)
        {
            for (int i = 0; i != 128 - stringSize; i++)
            {
                hashingText.push_back(padding[i]);
                notPadded = !notPadded;
            }
            stringSize = 128;
        }
        string newLine = "";
        for (int i = 0; i < 64; i++)
        {
            // if 0+0=0; if 0+1=1; if 1+0=1; if 1+1=0
            bitset<8> temp = bitset<8>(hashingText[stringSize - i]);
            bitset<8> temp2 = bitset<8>(hashingText[stringSize - i - 64]);
            string tempConvert = "";
            int asciiValue = 0;
            for (int j = 0; j != 8; j++)
            {
                if (temp[j] = temp2[j])
                {
                    tempConvert += "0";
                }
                else
                {
                    tempConvert += "1";
                }
            }
            int base = 1;
            for (int k = 7; k >= 0; k--)
            {
                if (tempConvert[k] == '1')
                {
                    asciiValue += base;
                }
                base = base * 2;
            }
            while (asciiValue < 48)
            {
                asciiValue += 10;
            }
            if (asciiValue > 57 && asciiValue < 65)
            {
                asciiValue += 7;
            }
            if (asciiValue >= 91 && asciiValue < 97)
            {
                asciiValue += 6;
            }
            while (asciiValue > 122)
            {
                asciiValue -= 10;
            }
            newLine += char(asciiValue);
        }
        hashingText.resize(stringSize - 128);
        hashingText += newLine;
        stringSize -= 64;
    }
    return hashingText;
}

int main(int argc, char *argv[])
{
    // variables
    vector<string> fileNames;
    string inputText = "";
    string hashedText;

    // chech if command line arguments exist
    FILE *file;
    int count = 0;
    for (int i = 1; i != argc; i++)
    {
        if (file = fopen(argv[i], "r"))
        {
            fclose(file);
            fileNames.push_back(argv[i]);
            count++;
        }
    }

    if (count < 1)
    {
        cout << "Iveskite, koki teksta norite paversti i hasha:" << endl;
        cin >> inputText;
        cout << "Hashinamas tekstas..." << endl;
        hashedText = hashing(inputText);
    }
    else
    {
        int c;
        for (int i = 0; i != fileNames.size(); i++)
        {
            file = fopen(fileNames[i].c_str(), "r");
            while ((c = getc(file)) != EOF)
                inputText += c;
            fclose(file);
            hashedText = hashing(inputText);
            cout << hashedText << endl;
        }
    }
    return 0;
}
