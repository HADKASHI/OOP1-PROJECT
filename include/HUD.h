#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

//this class holds and handles all the menu data
//i.e buttons and their effects, handle clicks etc
class HUD
{
public:
	HUD(const sf::Vector2f& postion);
	void drawHUD(sf::RenderWindow& window) const;
	
private:
	sf::Vector2u m_size;
	sf::Vector2f m_position;
	sf::Text m_title;
};