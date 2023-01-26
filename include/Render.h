#pragma once
#include <SFML/Graphics.hpp>
#include "Macros.h"

class Board;
class Pacman;
class HUD;

//this class handles all the window presentation and rendering
//e.g the game looop itself
class Render
{
public:
	Render(const sf::Vector2f& size);
	sf::RenderWindow* getP2Window() { return &m_window; }
	void gameLoop(HUD& hud, bool& finished);
	void setIcon();
	sf::Vector2f getBoardSize() { return BOARD_SIZE; }
	sf::Vector2f getBoardPosition() { return BOARD_POSITION; }

private:
	void handleTimeUp(Pacman& pacman, Board& board, sf::Clock& timer,
		HUD& hud, int level, int startTime, int endLevelScore);
	void eventsLoop(Pacman& pacman, bool& finished);
	void drawWindow(Board& board, HUD& hud, Pacman& pacman, int level, int time);
	void transitionSlide(const char* str, int fontSize, double sleepTime, sf::Color textColor, sf::Color outLineColor);
	void startLevelSlide(Pacman& pacman, Board& board, HUD& hud, int level, int timeAsSec);
	unsigned int initTimer(std::fstream& file);
	sf::Vector2f m_size;
	sf::RenderWindow m_window;
};