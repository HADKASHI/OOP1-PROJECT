#pragma once
#include "Board.h"
#include "Pacman.h"
#include "Collisions.h"
#include <iostream>
#include <cstdlib>
#include <random>

Board::Board(std::fstream& file, sf::Vector2f maxSize, sf::Vector2f position)
	:m_position(position), m_tileEdgeSize(TILE_SIZE)
{	
	loadBoard(file, maxSize);
	auto rng = std::default_random_engine{};
	std::shuffle(m_statics.begin(), m_statics.end(), rng);
}
//-----------------------------------------------
void Board::drawBoard(sf::RenderWindow &window)
{
	//draws board background
	auto boardWindow = sf::RectangleShape({ float(m_width), float(m_height) });
	boardWindow.setOrigin(boardWindow.getSize() / 2.f);
	boardWindow.setPosition(m_position);
	boardWindow.setOutlineThickness(8);
	boardWindow.setOutlineColor(BOARD_OUTLINE_COLOR);
	boardWindow.setFillColor(sf::Color::Black);
	window.draw(boardWindow);


	// draws static objects on board
	for (int i = 0; i < m_statics.size(); i++)
	{
		window.draw(*m_statics[i]);
	}

	// draws ghosts on board
	for (int i = 0; i < m_ghosts.size(); i++)
	{
		if(!m_ghosts[i]->isDead())
			PacmanState::instance().setTexture(*m_ghosts[i]);

		window.draw(*m_ghosts[i]);
	}
}
//-------------------------------------------
void Board::loadBoard(std::fstream& file, sf::Vector2f maxSize)
{
	int rows, cols;
	file >> rows >> cols;
	file.ignore();

	//down sizing edge size to fit in the board
	while (rows * m_tileEdgeSize > maxSize.y ||
		cols * m_tileEdgeSize > maxSize.x)
		m_tileEdgeSize--;

	m_height = rows * m_tileEdgeSize;
	m_width = cols * m_tileEdgeSize;

	m_maze.resize(rows);
	for (size_t i = 0; i < m_maze.size(); i++)
		m_maze[i].resize(cols);

	for (int row = 0; row < m_maze.size(); row++)
	{
		for (int col = 0; col < m_maze[row].size(); col++)
			m_maze[row][col] = file.get();

		file.ignore();
	}

	if (!file.eof()) file.ignore();

	loadMaze(rows, cols);
}



void Board::loadMaze(int rows, int cols)
{
	m_ghosts.clear();
	m_statics.clear();

	sf::Vector2f boardStartPoint = { m_position.x - float(0.5) * m_width,
									m_position.y - float(0.5) * m_height };

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			sf::Vector2f position({ boardStartPoint.x + col * m_tileEdgeSize,
				boardStartPoint.y + row * m_tileEdgeSize });

			//stretch walls if necessary
			if (m_maze[row][col] == '#')
			{
				bool height = true;
				bool width = true;
				if ((row > 0 && (m_maze[row - 1][col] == '#')) || (row < rows - 1 && (m_maze[row + 1][col] == '#')))
					height = false;
				if ((col > 0 && (m_maze[row][col - 1] == '#')) || (col < cols - 1 && (m_maze[row][col + 1] == '#')))
					width = false;

				addNewObject(m_maze[row][col], position, height, width);
			}
			else
				addNewObject(m_maze[row][col], position);
		}
	}
}


//--------------------------------------------
// This function adds a new tile to the board, by insert new cell
// to m_objects array.

void Board::addNewObject(char objectType, sf::Vector2f position, bool height, bool width)
{	
	switch (objectType)
	{
	case 'a':
	{
		m_pacmanPosition = position;
		break;
	}
	case 'r':
	{
		m_ghosts.push_back(std::make_unique<RedGhost>(m_tileEdgeSize, position, objectType));
		break;
	}
	case 'g':
	{
		m_ghosts.push_back(std::make_unique<GreenGhost>(m_tileEdgeSize, position, objectType));
		break;
	}
	case 'p':
	{
		m_ghosts.push_back(std::make_unique<PinkGhost>(m_tileEdgeSize, position, objectType));
		break;
	}
	case 'o':
	{
		m_ghosts.push_back(std::make_unique<OrangeGhost>(m_tileEdgeSize, position, objectType));
		break;
	}
	case '$':
	{
		m_statics.push_back(std::make_unique<SuperPresent>(m_tileEdgeSize, position, objectType));
		break;
	}
	case 'I':
	{
		m_statics.push_back(std::make_unique<FreezePresent>(m_tileEdgeSize, position, objectType));
		break;
	}
	case 'T':
	{
		m_statics.push_back(std::make_unique<TimePresent>(m_tileEdgeSize, position, objectType));
		break;
	}
	case 'L':
	{
		m_statics.push_back(std::make_unique<LivesPresent>(m_tileEdgeSize, position, objectType));
		break;
	}
	case '*':
	{
		m_statics.push_back(std::make_unique<Cookie>(m_tileEdgeSize, position, objectType));
		break;
	}
	case 'D':
	{
		m_statics.push_back(std::make_unique<Door>(m_tileEdgeSize, position, objectType));
		break;
	}
	case '%':
	{
		m_statics.push_back(std::make_unique<Key>(m_tileEdgeSize, position, objectType));
		break;
	}
	case '#':
	{
		m_statics.push_back(std::make_unique<Wall>(m_tileEdgeSize, position, objectType, height, width));
		break;
	}
	}
}
//---------------------------------------------
sf::Vector2f Board::getPacmanPosition() const
{
	return m_pacmanPosition;
}
//---------------------------------------------
float Board::getTileSize() const
{
	return m_tileEdgeSize;
}

sf::FloatRect Board::getGlobalBounds() const
{
	sf::Vector2f boardStartPoint = { m_position.x - float(0.5) * m_width,
									m_position.y - float(0.5) * m_height };

	return sf::FloatRect(boardStartPoint.x, boardStartPoint.y, m_width, m_height);
}


bool toDelete(std::unique_ptr<StaticObjects> & object); 
void Board::update(Pacman &pacman, sf::Time delta)
{
	moveGhosts(delta, pacman.getPosition(), pacman.getDirection());

	//pacman and board bounds collisions
	if (!inBounds(pacman.getGlobalBounds()))
		pacmanWithBoard(pacman, *this);

	//ghosts and borad bounds collisions
	for (size_t i=0; i < m_ghosts.size(); i++)
		if (!inBounds(m_ghosts[i]->getGlobalBounds()))
			ghostWithBoard(*m_ghosts[i], *this);

	//pacman and ghost collisions
	for (size_t i = 0; i < m_ghosts.size(); i++)
	{
		if (pacman.getGlobalBounds().intersects(m_ghosts[i]->getGlobalBounds()))
		{
			processCollision(pacman, *m_ghosts[i]);

			if (!PacmanState::instance().isSuper() && !PacmanState::instance().isFreeze())
				this->resetGhosts();
		}
	}

	//pacman and static objects
	for (size_t i = 0 ; i < m_statics.size(); i++)
	{
		if(pacman.getGlobalBounds().intersects(m_statics[i]->getGlobalBounds()))
			processCollision(pacman, *m_statics[i]);
	}

	//ghosts and static objects collisions
	for (size_t i = 0; i < m_ghosts.size(); i++)
		for (size_t j = 0; j < m_statics.size(); j++)
		{
			if (m_ghosts[i]->getGlobalBounds().intersects(m_statics[j]->getGlobalBounds()))
				processCollision(*m_ghosts[i], *m_statics[j]);
		}

	//checks whats been eaten
	for (size_t i = 0; i < m_statics.size(); i++)
	{
		if (m_statics[i]->beenEaten())
			handleCollisions(typeid(*m_statics[i]).name(), pacman.getPosition());
	}

	m_statics.erase(
		std::remove_if(m_statics.begin(), m_statics.end(), &toDelete),
		m_statics.end());
}

void Board::moveGhosts(sf::Time delta, sf::Vector2f pacmanPosition, sf::Vector2f pacmanDirection)
{
	for (size_t i = 0; i < m_ghosts.size(); i++)
		m_ghosts[i]->moveGhost(delta, pacmanPosition, pacmanDirection);
}

void Board::resetGhosts()
{
	for (size_t i = 0; i < m_ghosts.size(); i++)
		m_ghosts[i]->reset();
}

bool Board::inBounds(sf::FloatRect rect) const
{
	auto bounds = this->getGlobalBounds();
	bool topLeft = bounds.contains(rect.left, rect.top);
	bool bottomLeft = bounds.contains(rect.left , rect.top + rect.height);
	bool topRight = bounds.contains(rect.left + rect.width , rect.top);
	bool bottomRight = bounds.contains(rect.left + rect.width, rect.top + rect.height);

	return (topLeft && topRight && bottomLeft && bottomRight);
}

bool toDelete(std::unique_ptr<StaticObjects> & object)
{
	return object->beenEaten();
}

bool isDoor(std::unique_ptr<StaticObjects>& object)
{
	return std::string(typeid(*object).name()) == "class Door";
}

void Board::deleteDoor(sf::Vector2f pacmanLocation)
{
	//deletes a random door
	if(pacmanLocation == sf::Vector2f{ 0 , 0 })
	{
		auto index = std::find_if(m_statics.begin(), m_statics.end(), isDoor);
		if (index == m_statics.end())
		{
			return;
		}

		index->get()->gotEaten();
	}
	else
	{
		for (size_t i = 0; i < m_statics.size(); i++)
			if (std::string(typeid(*m_statics[i]).name()) == "class Door" &&
				m_statics[i]->getGlobalBounds().contains(pacmanLocation))
				m_statics[i]->gotEaten();
	}
}

void Board::handleCollisions(const std::string& object, sf::Vector2f pacmanLocation)
{
	if (object == "class Key")
		deleteDoor();
	else if (object == "class Door")
		deleteDoor(pacmanLocation);
}

bool isCookie(const std::unique_ptr<StaticObjects>& object)
{
	return std::string(typeid(*object).name()) == "class Cookie";
}

bool Board::noCookiesLeft() const
{
	auto index = std::find_if(m_statics.begin(), m_statics.end(), isCookie);
	if (index == m_statics.end())
	{
		return true;
	}

	return false;
}

void Board::resetLevel()
{
	loadMaze(m_height / m_tileEdgeSize, m_width / m_tileEdgeSize);
	m_pacmanPosition = sf::Vector2f({ m_pacmanPosition.x + 0.5f * m_tileEdgeSize,
		m_pacmanPosition.y + 0.5f * m_tileEdgeSize });
}
