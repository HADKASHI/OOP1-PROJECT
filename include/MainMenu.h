#pragma once
#include "Render.h"

class MovingObjects;

class MainMenu {
public:
	MainMenu();
	void menuLoop(Render* render);
private:
	void checkMouseOnButton(sf::RenderWindow* window, sf::Vector2f cursorLocation);
	void handleClickOnPlayGame(Render* render);
	void handleClickOnHelp(sf::RenderWindow* window);
	void drawBackGroundCharacters(sf::RenderWindow* window, sf::Time delta, sf::Time timer);
	void addRandomCharacter();

	sf::Texture m_logoTexture;
	sf::RectangleShape m_logo;
	std::vector<sf::Text> m_buttons;
	std::vector <std::unique_ptr<MovingObjects>> m_backGroundCharacters;
};