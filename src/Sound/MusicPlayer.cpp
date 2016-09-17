#include "Sound/MusicPlayer.hpp"

MusicPlayer::MusicPlayer()
: m_music{ }
, m_fileNames{ }
, m_volume{ 100.f }
{
    m_fileNames[Musics::GAMETHEME01] =  "assets/sounds/themes/Juhani_Junkala_-_Epic_Boss_Battle.ogg";
}

void MusicPlayer::play(Musics id)
{
    std::string fileName = m_fileNames[id];

    if (!m_music.openFromFile(fileName))
    {
        throw std::runtime_error("Music " + fileName + " could not be loaded.");
    }

    m_music.setVolume(m_volume);
    m_music.setLoop(true);
    m_music.play();
}

void MusicPlayer::stop()
{
    m_music.stop();
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
