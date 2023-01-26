#pragma once
#include "GameObject.h"

//
// used as the player class. holds the score ,lives and handles movement
//
class Pacman : public MovingObjects
{
public:
	Pacman(float edgeSize, sf::Vector2f position, char c, unsigned int score);
	void keyDirection(sf::Keyboard::Key key);
	void update(sf::Time delta);
	void notMoving(sf::Keyboard::Key key);
	void addPoints(unsigned int points) { m_score += points; }
	void gotEaten() { m_lives--; this->reset(); this->died(); }
	void addLives() { m_lives++; }
	void addTime() { m_bonusTime = true; }
	unsigned int getBonusTime() const { if (m_bonusTime) return TIMEBONUS; return 0; }
	unsigned int getScore() const { return m_score; }
	unsigned int getLives() const { return m_lives; }
	void setScore(int score) { m_score = score; }
	void setLives(int lives) { m_lives = lives; }

private:
	unsigned int m_bonusTime;
	bool m_isKeyPressed;
	unsigned int m_lives;
	unsigned int m_score;
};
