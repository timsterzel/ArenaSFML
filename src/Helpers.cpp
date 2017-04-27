#include "Helpers.hpp"
#include <random>
#include <iostream>

std::string Helpers::getRandomAlphaNumString(int length)
{
    std::string legalChars
        { "0123456789ABCDEFGHIJKLMNOPQRSTUVQXYZabcdefghijklmnopqrstuvwxyz" };
    
    std::random_device randDev;
    std::mt19937 mt(randDev());
    // Random int num between 1 (inclusive) and 6 (inclusive)
    std::uniform_int_distribution<int> dist(0, 62);
    std::string randStr{ "" };
    legalChars[600];
    for (int i = 0; i != length; i++)
    {
        int randNum{ dist(mt) };
        randStr += legalChars[randNum];
    }
    return randStr;
}

