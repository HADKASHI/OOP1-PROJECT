#pragma once
#include "GameObject.h"
#include "Ghost.h"
#include "Pacman.h"
#include <vector>
#include <fstream>

using std::vector;

//this class holds all game objects that apears on the game board (excepts for pacman)
//e.g cookies, ghosts, the current map etc
class Board
{
public:
	Board(std::fstream& file, sf::Vector2f maxSize, sf::Vector2f position);
	void drawBoard(sf::RenderWindow & window);
	sf::Vector2f getPacmanPosition() const;
	float getTileSize() const;
	void update(Pacman& pacman, sf::Time delta);
	unsigned int getGhostsNumber() const { return m_ghosts.size(); }
	bool inBounds(sf::FloatRect rect) const;
	bool noCookiesLeft() const;
	void resetLevel();


private:
	void loadMaze(int rows, int cols);
	void addNewObject(char objectType, sf::Vector2f position, bool height = false, bool width = false);
	void loadBoard(std::fstream& file, sf::Vector2f maxSize);
	void handleCollisions(const std::string& object, sf::Vector2f pacmanLocation);
	void deleteDoor(sf::Vector2f pacmanLocation = { 0 , 0 });
	void moveGhosts(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection);
	void resetGhosts();
	sf::FloatRect getGlobalBounds() const;

	float m_height;
	float m_width;
	float m_tileEdgeSize;
	sf::Vector2f m_position;
	sf::Vector2f m_pacmanPosition;
	std::vector<std::unique_ptr<StaticObjects>> m_statics;
	std::vector<std::unique_ptr<Ghost>> m_ghosts;
	std::vector<std::vector<char>> m_maze;
};

