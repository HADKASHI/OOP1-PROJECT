#pragma once
#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"


class Graphics
{
public:
	Graphics(const Graphics&) = delete;
	void operator = (const Graphics&) = delete;
	static Graphics& instance();
	sf::Texture &getTexture(char c);
	sf::Font& getFont() { return m_font;  }

private:
	Graphics();
	void loadGraphics();

	std::map <char, sf::Texture> m_textures;
	sf::Font m_font;
};
