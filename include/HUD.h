#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

//this class holds and handles all the menu data
//i.e buttons and their effects, handle clicks etc
class HUD
{
public:
	HUD(const sf::Vector2f& postion);
	void drawHUD(sf::RenderWindow& window, unsigned int lives, unsigned int score, unsigned int level, unsigned int time);

private:
	void initBackGround();
	void initLives();
	void initTitles();
	void initHudShow(sf::Text* text, float y, int color);
	void drawChangeData(sf::Text *text, unsigned int number, sf::RenderWindow& window);
	void drawLives(unsigned int lives, sf::RenderWindow& window);
	void drawTime(sf::Text* text, unsigned int time, sf::RenderWindow& window);


	sf::Vector2u m_size;
	sf::Vector2f m_position;
	sf::RectangleShape m_backGround;
	std::vector <sf::Text> m_titles;
	sf::Text m_level;
	sf::RectangleShape m_lives;
	sf::Texture m_livesTexture;
	sf::Text m_score;
	sf::Text m_time;
};