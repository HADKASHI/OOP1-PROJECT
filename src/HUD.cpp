#include "HUD.h"
#include <iostream>
#include "Resources.h"


HUD::HUD(const sf::Vector2f& postion) :
	m_position(postion), m_size(180, 600),
	m_titles({ sf::Text("LEVEL", Resources::instance().getFont()),
			   sf::Text("LIVES", Resources::instance().getFont()),
			   sf::Text("SCORE", Resources::instance().getFont()),
			   sf::Text("TIME", Resources::instance().getFont()) }),
	m_level(" ", Resources::instance().getFont()),
	m_score(" ", Resources::instance().getFont()),
	m_time(" ", Resources::instance().getFont()),
	m_lives({ 25, 25 })
{
	initBackGround();
	initLives();
	initTitles();
	initHudShow(&m_level, 110, 120);
	initHudShow(&m_score, 376, 120);
	initHudShow(&m_time, 509, 120);
}


void HUD::initBackGround()
{
	m_backGround.setSize(sf::Vector2f(m_size));
	m_backGround.setPosition(sf::Vector2f(m_position));
	m_backGround.setOrigin(m_backGround.getSize() / 2.f);
	m_backGround.setFillColor(sf::Color(250, 211, 231));
}

void HUD::initLives()
{
	m_livesTexture.loadFromFile("pacman.png");
	m_lives.setTexture(&m_livesTexture);
	m_lives.setFillColor(sf::Color(0, 0, 0, 120));
}

void HUD::initTitles()
{
	int y = 70;
	for (int i = 0; i < m_titles.size(); i++)
	{
		initHudShow(&m_titles[i], y, 255);
		y += 133;
		m_titles[i].setStyle(sf::Text::Italic);
	}
}


void HUD::initHudShow(sf::Text* text, float y, int color)
{
	text->setPosition({ m_position.x , 40 + y });
	text->setOrigin(text->getLocalBounds().width / 2.f,
		text->getLocalBounds().height / 2.f);
	text->setFillColor(sf::Color(0, 0, 0, color));

}


void HUD::drawHUD(sf::RenderWindow& window, unsigned int lives, unsigned int score, unsigned int level, unsigned int time)
{
	// Draw background
	window.draw(m_backGround);

	// Draw other text elements
//	window.draw(m_title);
	for (int i = 0; i < m_titles.size(); i++)
		window.draw(m_titles[i]);

	// Update and draw other data
	drawTime(&m_time, time, window);
	drawChangeData(&m_level, level, window);
	drawChangeData(&m_score, score, window);

	// Draw lives
	drawLives(lives, window);
}


void HUD::drawChangeData(sf::Text* text, unsigned int number, sf::RenderWindow& window)
{
	text->setString(std::to_string(number));
	text->setOrigin(text->getLocalBounds().width / 2.f,
		text->getLocalBounds().height / 2.f);
	window.draw(*text);
}

void HUD::drawTime(sf::Text* text, unsigned int time, sf::RenderWindow& window)
{
	int min = (time / 60), sec = (time % 60);

	if (min < 10 && sec < 10)
		text->setString("0" + std::to_string(min) + ":0" + (std::to_string(sec)));
	else if (min < 10)
		text->setString("0" + std::to_string(min) + ":" + (std::to_string(sec)));
	else if (sec < 10)
		text->setString(std::to_string(min) + ":0" + (std::to_string(sec)));
	else
		text->setString(std::to_string(min) + ":" + (std::to_string(sec)));

	if (min == 0 && sec <= 10)
		text->setFillColor(sf::Color::Red);

	text->setOrigin(text->getLocalBounds().width / 2.f,
		text->getLocalBounds().height / 2.f);
	window.draw(*text);

}




void HUD::drawLives(unsigned int lives, sf::RenderWindow& window)
{
	float xPosition = m_backGround.getPosition().x - 50;
	for (int i = 0; i < lives; i++)
	{
		m_lives.setPosition({ xPosition ,290 });
		xPosition += 50;
		m_lives.setOrigin(m_lives.getSize() / 2.f);
		window.draw(m_lives);
	}
}
