#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <cassert>
#include "ResourceIdentifiers.hpp"

template <typename Resource, typename Identifier>
class ResourceHolder
{
    private:
        std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;

    public:
        void load(Identifier id, const std::string &fileName);
        Resource& get(Identifier id);
        const Resource& get(Identifier id) const;


};

#include "ResourceHolder.inl"

#endif // TEXTUREHOLDER_HPP
