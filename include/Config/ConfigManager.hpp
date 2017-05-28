#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP
#include <map>

class ConfigManager
{
    private:
        std::map<std::string, std::string> m_configs;       
    public:
        explicit ConfigManager(const std::string &fileName);

        bool isKeyExisting(const std::string &key) const;
        std::string getString(const std::string &key, 
                const std::string &defaultVal) const;
        bool getBool(const std::string &key, bool defaultVal) const;
        int getInt(const std::string &key, int defaultVal) const;
        
        // Print out all keys and values stored in the config managers
        void printConfig() const;

    private:
        bool loadConfig(const std::string &fileName);
};

#endif // !CONFIGMANAGER_HPP
