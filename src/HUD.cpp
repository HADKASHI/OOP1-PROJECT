#include "HUD.h"
#include <iostream>
#include "Graphics.h"


HUD::HUD(const sf::Vector2f& postion):
	m_position(postion), m_size(180, 530), m_title("H U D", Graphics::instance().getFont())
{
	m_title.setPosition({ m_position.x + 52, m_position.y + 6 });
	m_title.setFillColor(sf::Color::Black);
	m_title.setOutlineThickness(0.5);
	m_title.setOutlineColor(sf::Color::White);
}

void HUD::drawHUD(sf::RenderWindow& window) const
{
	auto backGround = sf::RectangleShape(sf::Vector2f(m_size));
	backGround.setPosition(sf::Vector2f(m_position));
	backGround.setFillColor(sf::Color(190, 209, 240));
	backGround.setOutlineColor(sf::Color(174, 192, 219));
	backGround.setOutlineThickness(8);
	window.draw(backGround);

	window.draw(m_title);
}