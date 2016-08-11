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
    for (int i = { 0 }; i < static_cast<int>(RenderLayers::COUNT); i++)
    {
        m_sceneGraph->draw(static_cast<RenderLayers>(i), target, states);
    }
}

