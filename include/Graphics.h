#pragma once
#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"
#include <SFML/audio.hpp>
#include "Macros.h"


class Graphics
{
public:
	Graphics(const Graphics&) = delete;
	void operator = (const Graphics&) = delete;
	static Graphics& instance();
	sf::Texture &getTexture(char c);
	sf::Font& getFont() { return m_font;  }
	void playMusic(enum Sounds i, int vol);
	void playBackGround();
	void volumeBackGround(int vol);


private:
	Graphics();
	void loadGraphics();
	void loadSounds();
	std::map <char, sf::Texture> m_textures;
	sf::Font m_font;
	std::vector<sf::SoundBuffer> m_sounds;
	sf::Music m_backGround;
	sf::Sound m_sound;
};
