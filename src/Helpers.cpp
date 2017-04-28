#include "Helpers.hpp"
#include <random>
#include <iostream>
#include <set>
#include <cmath>

std::string Helpers::getRandomAlphaNumString(int length)
{
    std::string legalChars
        { "0123456789ABCDEFGHIJKLMNOPQRSTUVQXYZabcdefghijklmnopqrstuvwxyz" };
    
    std::random_device randDev;
    std::mt19937 mt(randDev());
    // Random int num between 1 (inclusive) and 6 (inclusive)
    std::uniform_int_distribution<int> dist(0, 62);
    std::string randStr{ "" };
    for (int i = 0; i != length; i++)
    {
        int randNum{ dist(mt) };
        randStr += legalChars[randNum];
    }
    return randStr;
}


std::string Helpers::createUniqueID(int length)
{
    // Store all created ids here so we can check if the created id is unique
    static std::set<std::string> createdIDs;
    std::string id{ "" };
    long rounds = 0;
    // Try to create unique id until we have find a unique one or the maximal
    // possible combination for the given length was rechaed
    do 
    {
        id = getRandomAlphaNumString(length);
        rounds++;
    } while(createdIDs.find(id) != createdIDs.end() && rounds < std::pow(26, length));
    createdIDs.insert(id);
    return id;
}
