#include "Resources.h"
#include <vector>

Resources ::Resources()
{
	loadGraphics();
	loadSounds();
}

Resources& Resources::instance()
{
	static auto resources = Resources();
	return resources;
}

void Resources::loadGraphics()
{
	std::vector <std::string> pngNames = { "redGhost.png" , "eyes.png" ,"save.png" ,"cleanPage.png", "door.png",
										   "pinkGhost.png", "orangeGhost.png" ,"cookie.png", "key.png", "greenGhost.png",
										   "pacman.png", "superpacman_present.png", "wall.png", "frightenedGhost.png", "clock_present.png",
											"ice_present.png", "life_present.png", "freezed_ghost.png"};

	std::vector <char> pngChars = { 'r', 'e', 's', 'c', 'D', 'p', 'o', '*', '%', 'g', 'a', '$', '#', 'f', 'T', 'I', 'L', 'F'};

	/*for (int i = 0; i < pngNames.size(); i++)
	{
		auto texture = sf::Texture();
		texture.loadFromFile(pngNames[i]);
		texture.setSmooth(true);
		m_textures.insert({ pngChars[i], texture });
	}

	m_font.loadFromFile("C:/Windows/Fonts/Bauhs93.ttf");*/

	std::vector <sf::Texture> png;


	auto texture = sf::Texture();
	texture.loadFromFile("redGhost.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[0], texture });

	//		auto texture = sf::Texture();
	texture.loadFromFile("eraser.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[1], texture });

	//		auto texture = sf::Texture();
	texture.loadFromFile("save.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[2], texture });


	//		auto texture = sf::Texture();
	texture.loadFromFile("cleanPage.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[3], texture });

	//		auto texture = sf::Texture();
	texture.loadFromFile("door.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[4], texture });

	//		auto texture = sf::Texture();
	texture.loadFromFile("pinkGhost.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[5], texture });

	//		auto texture = sf::Texture();
	texture.loadFromFile("orangeGhost.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[6], texture });

	//		auto texture = sf::Texture();
	texture.loadFromFile("cookie.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[7], texture });

	//		auto texture = sf::Texture();
	texture.loadFromFile("key.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[8], texture });

	//		auto texture = sf::Texture();
	texture.loadFromFile("greenGhost.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[9], texture });

	//	auto texture = sf::Texture();
	texture.loadFromFile("pacman.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[10], texture });

	//	auto texture = sf::Texture();
	texture.loadFromFile("superpacman_present.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[11], texture });

	//	auto texture = sf::Texture();
	texture.loadFromFile("wall.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[12], texture });

	texture.loadFromFile("frightenedGhost.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[13], texture });

	texture.loadFromFile("clock_present.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[14], texture });

	texture.loadFromFile("ice_present.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[15], texture });

	texture.loadFromFile("life_present.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[16], texture });

	texture.loadFromFile("freezed_ghost.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[17], texture });

	m_font.loadFromFile("C:/Windows/Fonts/Bauhs93.ttf");
}

sf::Texture & Resources::getTexture(char c)
{
	if (auto search = m_textures.find(c); search != m_textures.end())
		return m_textures[c];
}

void Resources::loadSounds()
{
	char sounds[][20] = { "timer.wav", "finish_level.wav", "game_over.wav", "pacman_dead.wav",
						  "ghost_eaten.wav", "present.wav", "eat_cookie.wav", "door_open.wav" };

	for (int i = 0; i < 8; i++)
	{
		sf::SoundBuffer sound;
		sound.loadFromFile(sounds[i]);
		m_sounds.push_back(sound);
	}

	m_backGround.openFromFile("background.wav");
}


void Resources::playMusic(enum Sounds i, int vol)
{
	m_backGround.setVolume(0);
	m_sound.setBuffer(m_sounds[i]);
	m_sound.setVolume(vol);
	m_sound.play();
}

void Resources::playBackGround()
{
	m_backGround.setVolume(50);
	m_backGround.play();
}

void Resources::volumeBackGround(int vol)
{
	m_backGround.setVolume(vol);
}

void Resources::stopBackGroundMusic()
{
	m_backGround.stop();
}