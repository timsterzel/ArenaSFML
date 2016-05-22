template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &fileName)
{
    std::unique_ptr<Resource> resource(new Resource);
    if (!resource->loadFromFile(fileName))
    {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + fileName);
    }
    auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
    // Stop execute in debug mode when there was an error by inserting the resource(e.g try to add the same id twice)
    // Trying to load the same resource twice with the same id is a logical error so the progtam should stop immediately in debug mode
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &fileName, const Parameter &secondParam)
{
    std::unique_ptr<Resource> resource(new Resource);
    if (!resource->loadFromFile(fileName, secondParam))
    {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + fileName);
    }
    auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
    // Stop execute in debug mode when there was an error by inserting the resource(e.g try to add the same id twice)
    // Trying to load the same resource twice with the same id is a logical error so the progtam should stop immediately in debug mode
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = m_resourceMap.find(id);
    // Stop programm in debug mode, when trying to get a resource which is not loaded
    assert(found != m_resourceMap.end());
    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = m_resourceMap.find(id);
    // Stop programm in debug mode, when trying to get a resource which is not loaded
    assert(found != m_resourceMap.end());
    return *found->second;
}
