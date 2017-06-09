/*
template <typename T,typename ... Types>
void ScreenStack::registerScreen(ScreenID screenID, Types... args)
{
    m_factories[screenID] = [this, args...] ()
    {
        return std::make_unique<T>(this, m_context, args...);
    };
}
*/
template <typename T>
void ScreenStack::registerScreen(ScreenID screenID)
{
    m_factories[screenID] = [this] ()
    {
        return std::make_unique<T>(this, m_context);
    };
}

template <typename T, typename S>
void ScreenStack::registerScreen(ScreenID screenID, const S &second)
{
    m_factories[screenID] = [this, &second] ()
    {
        return std::make_unique<T>(this, m_context, second);
    };
}

template <typename T, typename S, typename R>
void ScreenStack::registerScreen(ScreenID screenID, const S &second, 
        R third)
{
    m_factories[screenID] = [this, &second, &third] ()
    {
        return std::make_unique<T>(this, m_context, second, third);
    };
}

template <typename T, typename S, typename R, typename Q>
void ScreenStack::registerScreen(ScreenID screenID, const S &second, 
        R third, Q fourth)
{
    m_factories[screenID] = [this, &second, &third, fourth] ()
    {
        return std::make_unique<T>(this, m_context, second, third, fourth);
    };
}
