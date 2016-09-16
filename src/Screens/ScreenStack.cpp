#include "Screens/ScreenStack.hpp"


ScreenStack::ScreenStack(Screen::Context context)
: m_stack()
, m_pendingList()
, m_context{ context }
, m_factories()
{

}

ScreenStack::~ScreenStack()
{

}

void ScreenStack::handleInput(Input input, float dt)
{
    // Iterate from end to the beginning so inputs are only handled by the next screen when
    // the higher screen return false
    for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); itr++)
    {
        if (!(*itr)->handleInput(input, dt))
        {
            break;
        }
    }
    applyPendingChanges();
}

void ScreenStack::update(float dt)
{
    for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); itr++)
    {
        //(*itr)->update(dt);
        if (!(*itr)->update(dt))
        {
            break;
        }

    }
    applyPendingChanges();
}

void ScreenStack::render()
{
    //for (Screen::Ptr screen : m_stack)
    for (std::unique_ptr<Screen> &screen : m_stack)
    {
        screen->render();
    }
}

void ScreenStack::pushScreen(ScreenID screenID)
{
    m_pendingList.push_back(PendingChange(Action::PUSH, screenID));
}

void ScreenStack::popScreen()
{
    m_pendingList.push_back(PendingChange(Action::POP, ScreenID::NONE));
}

void ScreenStack::clearScreens()
{
    m_pendingList.push_back(PendingChange(Action::CLEAR, ScreenID::NONE));
}

bool ScreenStack::isEmpty() const
{
    return m_stack.empty();
}

Screen::Ptr ScreenStack::createScreen(ScreenID screenID)
{
    auto found = m_factories.find(screenID);
    assert(found != m_factories.end());

    return found->second();
}

void ScreenStack::applyPendingChanges()
{
    for (PendingChange change : m_pendingList)
    {
        switch(change.action)
        {
            case Action::PUSH:
                m_stack.push_back(createScreen(change.screenID));
                break;
            case Action::POP:
                m_stack.pop_back();
                break;
            case Action::CLEAR:
                m_stack.clear();
                break;
        }
    }
    m_pendingList.clear();
}

ScreenStack::PendingChange::PendingChange(Action action, ScreenID screenID)
: action{ action }
, screenID{ screenID }
{

}
