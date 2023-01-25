#pragma once
#include "Render.h"

class MainMenu {
public:
	MainMenu();
	void menuLoop(Render* render);
private:
	void checkMouseOnButton(sf::RenderWindow* window, sf::Vector2f cursorLocation);
	void handleClickOnPlayGame(Render* render);
	void handleClickOnHelp(sf::RenderWindow* window);
	sf::Texture m_logoTexture;
	sf::RectangleShape m_logo;
	std::vector<sf::Text> m_buttons;
};