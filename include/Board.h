#pragma once

#include "GameObject.h"
#include "Ghost.h"
#include <vector>
#include <fstream>

using std::vector;


class Board
{
public:
	Board(std::fstream& file, sf::Vector2f maxSize, sf::Vector2f position);
	void drawBoard(sf::RenderWindow & window);
	sf::Vector2f getPacmanPosition() const;
	float getTileSize() const;
	void update(Pacman& pacman, sf::Time delta);
	sf::FloatRect getGlobalBounds() const;
	bool inBounds(sf::FloatRect rect) const;


private:
	void addNewObject(char objectType, sf::Vector2f position, bool height = false, bool width = false);
	void loadBoard(std::fstream& file, sf::Vector2f maxSize);
	void handleCollisions(const std::string& object);
	void deleteDoor();
	void moveGhosts(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection);

	float m_height;
	float m_width;
	float m_tileEdgeSize;
	sf::Vector2f m_position;
	sf::Vector2f m_pacmanPosition;
	// std::unique_ptr<Pacman> m_pacman; ///////////////////////////////////
	std::vector<std::unique_ptr<StaticObjects>> m_statics;
	std::vector<std::unique_ptr<Ghost>> m_ghosts;
	
};

