#include "Graphics.h"
#include <vector>

Graphics ::Graphics()
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
										   "pinkGhost.png", "orangeGhost.png" ,"cookie.png", "key.png", "greenGhost.png",
										   "pacman.png", "present.png", "wall.png" };

	std::vector <char> pngChars = { 'r', 'e', 's', 'c', 'D', 'p', 'o', '*', '%', 'g', 'a', '$', '#'};

	for (int i = 0; i < pngNames.size(); i++)
	{
		auto texture = sf::Texture();
		texture.loadFromFile(pngNames[i]);
		texture.setSmooth(true);
		m_textures.insert({ pngChars[i], texture });
	}

	m_font.loadFromFile("C:/Windows/Fonts/Bauhs93.ttf");
}

sf::Texture & Graphics::getTexture(char c)
{
	if (auto search = m_textures.find(c); search != m_textures.end())
		return m_textures[c];
}