#ifndef SOUNDPLAYER_HPP
#define SOUNDPLAYER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <string>
#include "Resources/ResourceHolder.hpp"

class SoundPlayer : private sf::NonCopyable
{
    private:
        ResourceHolder<sf::SoundBuffer> m_soundHolder;
        std::list<sf::Sound> m_sounds;
        float m_volume;

    public:
        SoundPlayer();
        
        void load(const std::string &id, const std::string file);
        void play(const std::string &id);
        void removeStoppedSounds();
        void setVolume(float volume);
        float getVolume() const;
};

#endif // SOUNDPLAYER_HPP
