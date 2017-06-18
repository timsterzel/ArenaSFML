#include "Sound/MusicPlayer.hpp"
#include <iostream>

MusicPlayer::MusicPlayer()
: m_music{ }
, m_fileNames{ }
, m_volume{ 100.f }
{

}

void MusicPlayer::play(const std::string &id)
{
    std::string fileName = m_fileNames[id];

    if (!m_music.openFromFile(fileName))
    {
        throw std::runtime_error("Music " + fileName + " could not be loaded.");
    }

    m_music.setVolume(m_volume);
    m_music.setLoop(true);
    m_music.play();
    m_currentPlayed = id;
}

void MusicPlayer::stop()
{
    m_music.stop();
    m_currentPlayed = "";
}

std::string MusicPlayer::getCurrentId() const
{
    return m_currentPlayed;
}

void MusicPlayer::setPaused(bool paused)
{
    if (paused)
    {
        m_music.pause();
    }
    else
    {
        m_music.play();
    }
}

void MusicPlayer::setVolume(float volume)
{
    m_volume = volume;
    m_music.setVolume(volume);
}

void MusicPlayer::add(const std::string &id, const std::string &fileName)
{
    m_fileNames[id] = fileName;
}
