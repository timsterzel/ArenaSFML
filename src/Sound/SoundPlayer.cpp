#include "Sound/SoundPlayer.hpp"
#include <iostream>

SoundPlayer::SoundPlayer()
: m_soundHolder{ }
, m_sounds{ }
, m_volume{ 100.f }
{

}

void SoundPlayer::load(const std::string &id, const std::string file)
{
    m_soundHolder.load(id, file);
}

void SoundPlayer::play(const std::string &id)
{
    m_sounds.push_back(sf::Sound(m_soundHolder.get(id)));
    m_sounds.back().setVolume(m_volume);
    m_sounds.back().play();
}

void SoundPlayer::removeStoppedSounds()
{
    m_sounds.remove_if([] (const sf::Sound &s)
    {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

void SoundPlayer::setVolume(float volume)
{
    m_volume = volume;
    for (sf::Sound &sound : m_sounds) {
        sound.setVolume(volume);
    }
}
