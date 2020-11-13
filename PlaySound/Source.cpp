#include "Header.h"
#include <iostream>
using namespace std;


SoundManager::SoundManager()
{

    missile_launch_buff.loadFromFile("button.wav");

}

void SoundManager::playMissileLaunch()
{

    fire_sound.setBuffer(missile_launch_buff);
    fire_sound.play();
    cout << "Missile launch sound \n";
}