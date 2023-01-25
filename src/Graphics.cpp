//#include "Graphics.h"
//#include <vector>
//
//Graphics ::Graphics()
//{
//	loadGraphics();
//}
//
//Graphics& Graphics::instance()
//{
//	static auto graphics = Graphics();
//	return graphics;
//}
//
//void Graphics::loadGraphics()
//{
//	std::vector <std::string> pngNames = { "redGhost.png" , "eraser.png" ,"save.png" ,"cleanPage.png", "door.png",
//										   "pinkGhost.png", "orangeGhost.png" ,"cookie.png", "key.png", "greenGhost.png",
//										   "pacman.png", "present.png", "wall.png" };
//
//	std::vector <char> pngChars = { 'r', 'e', 's', 'c', 'D', 'p', 'o', '*', '%', 'g', 'a', '$', '#'};
//
//	for (int i = 0; i < pngNames.size(); i++)
//	{
//		auto texture = sf::Texture();
//		texture.loadFromFile(pngNames[i]);
//		texture.setSmooth(true);
//		m_textures.insert({ pngChars[i], texture });
//	}
//
//	m_font.loadFromFile("C:/Windows/Fonts/Bauhs93.ttf");
//}
//
//sf::Texture & Graphics::getTexture(char c)
//{
//	if (auto search = m_textures.find(c); search != m_textures.end())
//		return m_textures[c];
//}

#include "Graphics.h"
#include <vector>

Graphics::Graphics()
{
	loadGraphics();
}

Graphics& Graphics::instance()
{
	static auto graphics = Graphics();
	return graphics;
}

void Graphics::loadGraphics()
{
	std::vector <std::string> pngNames = { "redGhost.png" , "eraser.png" ,"save.png" ,"cleanPage.png", "door.png",
										   "pinkGhost.png", "blueGhost.png" ,"cookie.png.png", "key.png", "greenGhost.png",
										   "pacman.png", "present.png", "wall.png" };

	std::vector <char> pngChars = { 'r', 'e', 's', 'c', 'D', 'p', 'o', '*', '%', 'g', 'a', '$', '#' };
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
	texture.loadFromFile("present.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[11], texture });

	//	auto texture = sf::Texture();
	texture.loadFromFile("wall.png");
	texture.setSmooth(true);
	m_textures.insert({ pngChars[12], texture });

	//for (int i = 0; i < pngNames.size(); i++)
	//{
	//	auto texture = sf::Texture();
	//	/*if (!*/texture.loadFromFile(pngNames[i]);
	//	/*{
	//		texture.loadFromFile("blueGhost.png");
	//	}*/
	//	texture.setSmooth(true);
	//	m_textures.insert({ pngChars[i], texture });
	//}

	m_font.loadFromFile("C:/Windows/Fonts/Bauhs93.ttf");
}

sf::Texture& Graphics::getTexture(char c)
{
	if (auto search = m_textures.find(c); search != m_textures.end())
		return m_textures[c];
}