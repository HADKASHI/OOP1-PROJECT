#pragma once
#include <SFML/Graphics.hpp>
#include <Macros.h>

class GameObject : public sf::RectangleShape
{
public:
	GameObject(float edgeSize, sf::Vector2f position, char c);

private:

};
//---------------------------------------------------
class StaticObjects : public GameObject {
public:
	StaticObjects(float edgeSize, sf::Vector2f position, char c);
	bool beenEaten() const { return m_beenEaten; }
	void isEaten() { m_beenEaten = true; } 

private:
	bool m_beenEaten;
};
//---------------------------------------------------
class MovingObjects : public GameObject 
{
public:
	MovingObjects(float edgeSize, sf::Vector2f position, char c);
	sf::Vector2f getDirection() const { return m_direction; }
	void setDirection(sf::Vector2f direction) { m_direction = direction; }

private:
	sf::Vector2f m_direction;
//	void move() = 0;
};
//---------------------------------------------------
class Pacman: public MovingObjects
{
public:
	Pacman(float edgeSize, sf::Vector2f position, char c);
	//using MovingObjects::MovingObjects;
	void keyDirection(sf::Keyboard::Key key);
	void update(sf::Time delta);
	void notMoving(sf::Keyboard::Key key);
	void addPoints(unsigned int points) { m_score += points; }
	void gotEaten() { m_lives--; }
	unsigned int getScore() const { return m_score; }
	unsigned int getLives() const { return m_lives; }

private:

	bool m_isKeyPressed;
	unsigned int m_lives;
	unsigned int m_score;


};

//----------------------------------------------------
class Wall : public StaticObjects
{
public:
	Wall(float edgeSize, sf::Vector2f position, char c, bool height = false, bool width = false);
};
//----------------------------------------------------
class Door : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
};
//----------------------------------------------------
class Key : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
	unsigned int pointsReward() { return KEYSPOINTS; }
};

//-------------	---------------------------------------
class Cookie : public StaticObjects
{
public:
	Cookie(float edgeSize, sf::Vector2f position, char c);
	unsigned int pointsReward() { return COOKIEPOINTS; }
};

//----------------------------------------------------
class Present : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
	unsigned int pointsReward() { return 5; }
};
//----------------------------------------------------


