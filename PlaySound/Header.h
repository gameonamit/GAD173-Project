#pragma once
#include <SFML/Audio.hpp>
class SoundManager
{
private:
    sf::SoundBuffer missile_launch_buff;
    sf::Sound fire_sound;
public:
    SoundManager();
    void playMissileLaunch();

};