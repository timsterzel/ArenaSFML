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
