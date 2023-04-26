#ifndef HASH_H
#define HASH_H
 
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(!debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        int index = k.size() - 1;
        HASH_INDEX_T result = 0;
        int loop_index = 4;
        for(  ; loop_index >= 0; loop_index--)
        {
            HASH_INDEX_T vale = 0;
            for(int j = index; j >= 0 && j >= index - 5; j--)
            {
                vale += pow(36, index - j)*letterDigitToNumber( k[j] );
            }
            result = result + ( vale * rValues[loop_index] );
            index = index - 6;

            // If we have reached the end of the string, break
            if (index < 0)
            {
                break;
            }
        }
        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
         // Code to convert a-z,0-9 to an integral value 0-35 using ASCII values
        if (letter >= 'a' && letter <= 'z')
        {
            return letter - 'a';
        }
        else if (letter >= '0' && letter <= '9')
        {
            return letter - '0' + 26;
        }
        else if (letter >= 'A' && letter <= 'Z')
        {
            return letter - 'A';
        }
        else
        {
            return 0;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
