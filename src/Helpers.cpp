#include "Helpers.hpp"
#include <random>
#include <iostream>
#include <set>
#include <cmath>
#include <utility>
#include <algorithm>
#include <sstream>

std::string Helpers::getRandomAlphaNumString(int length)
{
    std::string legalChars
        { "0123456789ABCDEFGHIJKLMNOPQRSTUVQXYZabcdefghijklmnopqrstuvwxyz" };
    
    std::random_device randDev;
    std::mt19937 mt(randDev());
    // Random int num between 0 (inclusive) and 62 (inclusive)
    std::uniform_int_distribution<int> dist(0, 62);
    std::string randStr{ "" };
    for (int i = 0; i != length; i++)
    {
        int randNum{ dist(mt) };
        randStr += legalChars[randNum];
    }
    return randStr;
}

int Helpers::getRandomNum(int a, int b)
{
    std::random_device randDev;
    std::mt19937 mt(randDev());
    std::uniform_int_distribution<int> dist(a, b);
    return dist(mt);
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

std::string Helpers::toUpper(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}


std::vector<std::string> Helpers::splitString(const std::string &str, 
                char delimiter)
{
    std::vector<std::string> splittedStr;
    std::stringstream ss(str);
    std::string tmp;
    while(getline(ss, tmp, delimiter))
    {
        splittedStr.push_back(tmp);
    }
    return splittedStr;
}

bool Helpers::stringToBool(const std::string &str)
{
    std::string strUpper{ toUpper(str) };
    if (strUpper == "TRUE" || strUpper =="1")
    {
        return true;
    }
    return false;
}


sf::Color Helpers::lerbRGBColor(sf::Color a, sf::Color b, float t)
{
	return sf::Color(
		(int) (a.r + (b.r - a.r) * t),
		(int) (a.g + (b.g - a.g) * t),
		(int) (a.b + (b.b - a.b) * t),
		(int) (a.a + (b.a - a.a) * t)
	);
}
