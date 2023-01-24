#pragma once
#include <SFML/Graphics.hpp>

class GameObject : public sf::RectangleShape
{
public:
	GameObject(float edgeSize, sf::Vector2f position, char c);

private:

};
//---------------------------------------------------
class StaticObjects : public GameObject {
public:
	using GameObject::GameObject;
};
//---------------------------------------------------
class MovingObjects : public GameObject 
{
public:
	MovingObjects(float edgeSize, sf::Vector2f position, char c);
//	void move() = 0;
};
//---------------------------------------------------
class Pacman: public MovingObjects
{
public:
	Pacman(float edgeSize, sf::Vector2f position, char c, unsigned int score);
	//using MovingObjects::MovingObjects;
	void setDirection(sf::Keyboard::Key key);
	void update(sf::Time delta);
	void notMoving(sf::Keyboard::Key key);
	unsigned int getLives() const { return m_lives; }
	unsigned int getScore() const { return m_score; }


private:
	sf::Vector2f m_direction;
	bool m_isKeyPressed;
	unsigned int m_lives;
	unsigned int m_score;

};
//----------------------------------------------------
class Ghost : public MovingObjects 
{
public:
	using MovingObjects::MovingObjects;
	//virtual void move() = 0;
};
//----------------------------------------------------
class RedGhost : public Ghost
{
public:
	using Ghost::Ghost;
//	void move(Controller& controller) override;
};
//----------------------------------------------------
class GreenGhost : public Ghost
{
public:
	using Ghost::Ghost;
	//	void move(Controller& controller) override;
};//----------------------------------------------------
class PinkGhost : public Ghost
{
public:
	using Ghost::Ghost;
	//	void move(Controller& controller) override;
};//----------------------------------------------------
class OrangeGhost : public Ghost
{
public:
	using Ghost::Ghost;
	//	void move(Controller& controller) override;
};
//----------------------------------------------------
class Wall : public StaticObjects
{
public:
	Wall(float edgeSize, sf::Vector2f position, char c, bool height, bool width);
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
};

//----------------------------------------------------
class Cookie : public StaticObjects
{
public:
	Cookie(float edgeSize, sf::Vector2f position, char c);
};

//----------------------------------------------------
class Present : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
};
//----------------------------------------------------


