#ifndef HELPERS_HPP
#define HELPERS_HPP
#include <SFML/Graphics.hpp>

namespace Helpers
{
    // Get a random string of the given length with normal alphabet chars and numbers
    std::string getRandomAlphaNumString(int length);

    // Creates a random unique id with the given length. When it is not possible
    // to create a unique id return an empty string
    std::string createUniqueID(int lenth);
    
    std::string toUpper(std::string str);
    std::vector<std::string> splitString(const std::string &str, char delimiter);
    // Retruns true if the string is "true"( Upper and Lower cases are ignored)
    // or "1". Else the function return false
    bool stringToBool(const std::string &str);
};


#endif // HELPERS_HPP
