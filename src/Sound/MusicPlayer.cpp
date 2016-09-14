#include "Sound/MusicPlayer.hpp"

MusicPlayer::MusicPlayer()
: m_music{ }
, m_fileNames{ }
, m_volume{ 100.f }
{
    m_fileNames[Musics::GameTheme01] =  "sounds/themes/Juhani_Junkala_-_Epic_Boss_Battle.ogg";
}
