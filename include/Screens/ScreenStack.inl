template <typename T>
void ScreenStack::registerScreen(ScreenID screenID)
{
    m_factories[screenID] = [this] ()
    {
        return std::make_unique<T>(this, m_context);
    };
}
