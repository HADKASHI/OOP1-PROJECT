#pragma once
#include <SFML/Graphics.hpp>

class Board;
class HUD;

//this class handles all the window presentation and rendering
//e.g real time updates and drawings
class Render
{
public:
	Render(const sf::Vector2f &size);
	void gameLoop(Board &board, HUD &hud, bool &finished);
	void setIcon();
	sf::Vector2f getBoardSize() { return { 15 * 40, 15 * 40 }; }
	sf::Vector2f getBoardPosition() { return { 40.f + 20 * 15, 40.f + 20 * 15 }; }

private:
	sf::Vector2f m_size;
	sf::RenderWindow m_window;
};