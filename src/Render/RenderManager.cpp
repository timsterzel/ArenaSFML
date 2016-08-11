#include "Render/RenderManager.hpp"
#include "Components/SceneNode.hpp"
#include "Render/EnumRenderLayers.hpp"
#include <iostream>

RenderManager::RenderManager(SceneNode *sceneGraph)
: m_sceneGraph{ sceneGraph }
{

}

void RenderManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (std::size_t i = { 0 }; i < RenderLayers::COUNT; i++)
    {
        m_sceneGraph->draw(target, states);
    }


}

