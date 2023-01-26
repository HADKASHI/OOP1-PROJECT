#pragma once
#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"
#include <SFML/audio.hpp>
#include "Macros.h"


class Resources
{
public:
	Resources(const Resources&) = delete;
	void operator = (const Resources&) = delete;
	static Resources& instance();
	sf::Texture &getTexture(char c);
	sf::Font& getFont() { return m_font;  }
	void playMusic(enum Sounds i, int vol = 100);
	void playBackGround();
	void volumeBackGround(int vol);

private:
	Resources();
	void loadGraphics();
	void loadSounds();

	std::map <char, sf::Texture> m_textures;
	sf::Font m_font;
	std::vector<sf::SoundBuffer> m_sounds;
	sf::Music m_backGround;
	sf::Sound m_sound;
};
