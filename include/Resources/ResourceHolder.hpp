#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <cassert>

template <typename Resource>
class ResourceHolder
{
    private:
        std::map<std::string, std::unique_ptr<Resource>> m_resourceMap;

    public:
        void load(const std::string &id, const std::string &fileName);

        template <typename Parameter>
        void load(const std::string &id, const std::string &fileName, 
                const Parameter &secondParam);

        Resource& get(const std::string &id);
        Resource& get(const std::string &id) const;
};

#include "Resources/ResourceHolder.inl"

#endif // TEXTUREHOLDER_HPP
