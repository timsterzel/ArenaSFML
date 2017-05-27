#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class MusicPlayer : private sf::NonCopyable
{
    private:
        sf::Music m_music;
        // Identifer, filename
        std::map<std::string, std::string> m_fileNames;
        float m_volume;

    public:
        MusicPlayer();

        void play(const std::string &id);
        void stop();

        void setPaused(bool paused);
        void setVolume(float volume);

        void add(const std::string &id, const std::string &fileName);
};

#endif // MUSICPLAYER_HPP
