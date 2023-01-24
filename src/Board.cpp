#include "Board.h"
#include "Collisions.h"
#include <iostream>
#include <cstdlib>
#include <random>

Board::Board(std::fstream& file, sf::Vector2f maxSize, sf::Vector2f position)
	:m_position(position), m_tileEdgeSize(40)
{	
	loadBoard(file, maxSize);
	auto rng = std::default_random_engine{};
	std::shuffle(m_statics.begin(), m_statics.end(), rng);
}
//-----------------------------------------------
void Board::drawBoard(sf::RenderWindow &window)
{
	//draw empty board
	auto boardWindow = sf::RectangleShape({ float(m_width), float(m_height) });
	boardWindow.setOrigin(boardWindow.getSize() / 2.f);
	boardWindow.setPosition(m_position);
	boardWindow.setOutlineThickness(8);
	boardWindow.setOutlineColor(sf::Color(19, 43, 209));
	boardWindow.setFillColor(sf::Color::Black);
	window.draw(boardWindow);


	// draw static objects on board
	for (int i = 0; i < m_statics.size(); i++)
	{
		window.draw(*m_statics[i]/*->draw()*/);
	}

	// draw ghosts on board
	for (int i = 0; i < m_ghosts.size(); i++)
	{
		window.draw(*m_ghosts[i]);
	}
}
//-------------------------------------------
void Board::loadBoard(std::fstream& file, sf::Vector2f maxSize)
{
	int rows, cols;
	file >> rows >> cols;
	file.ignore();

	while (rows * m_tileEdgeSize > maxSize.y ||
		cols * m_tileEdgeSize > maxSize.x)
		m_tileEdgeSize--;

	m_height = rows * m_tileEdgeSize;
	m_width = cols * m_tileEdgeSize;

	sf::Vector2f boardStartPoint = { m_position.x - float(0.5) * m_width,
									m_position.y - float(0.5) * m_height };

	std::vector<std::vector<char>> maze;
	maze.resize(rows);
	for (size_t i = 0; i < maze.size(); i++)
		maze[i].resize(cols);

	for (int row = 0; row < maze.size(); row++)
	{
		for (int col = 0; col < maze[row].size(); col++)
			maze[row][col] = file.get();

		file.ignore();
	}

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			sf::Vector2f position({ boardStartPoint.x + col * m_tileEdgeSize,
				boardStartPoint.y + row * m_tileEdgeSize });

			if (maze[row][col] == '#')
			{
				bool height = true;
				bool width = true;
				if ((row > 0 && (maze[row - 1][col] == '#')) || (row < rows - 1 && (maze[row + 1][col] == '#')))
					height = false;
				if ((col > 0 && (maze[row][col - 1] == '#')) || (col < cols - 1 && (maze[row][col + 1] == '#')))
					width = false;

				addNewObject(maze[row][col], position, height, width);
			}
			else
				addNewObject(maze[row][col], position);
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
		m_statics.push_back(std::make_unique<Present>(m_tileEdgeSize, position, objectType));
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

	if (!inBounds(pacman.getGlobalBounds()))
		pacmanWithBoard(pacman, *this);

	/*for (size_t i=0; i < m_ghosts.size(); i++)
		if (!inBounds(m_ghosts[i]->getGlobalBounds()))
			ghostWithBoard(*m_ghosts[i], *this);*/

	for (size_t i = 0; i < m_ghosts.size(); i++)
	{
		if (pacman.getGlobalBounds().intersects(m_ghosts[i]->getGlobalBounds()))
			processCollision(pacman, *m_ghosts[i]);
	}

	for (size_t i = 0 ; i < m_statics.size(); i++)
	{
		if(pacman.getGlobalBounds().intersects(m_statics[i]->getGlobalBounds()))
			processCollision(pacman, *m_statics[i]);
	}

	for (size_t i = 0; i < m_ghosts.size(); i++)
		for (size_t j = 0; j < m_statics.size(); j++)
		{
			if (std::string(typeid(*m_statics[i]).name()) == "class Wall" ||
				std::string(typeid(*m_statics[i]).name()) == "class Door")
			{
				if (m_ghosts[i]->getGlobalBounds().intersects(m_statics[j]->getGlobalBounds()))
					processCollision(*m_ghosts[i], *m_statics[j]);
			}
			else
				m_ghosts[i]->setMomentum(m_ghosts[i]->getDirection());
		}

	for (size_t i = 0; i < m_statics.size(); i++)
	{
		if (m_statics[i]->beenEaten())
			handleCollisions(typeid(*m_statics[i]).name());
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

bool Board::inBounds(sf::FloatRect rect) const
{
	return
		(this->getGlobalBounds().contains(rect.top, rect.left) &&
		 this->getGlobalBounds().contains(rect.top + rect.height, rect.left) &&
		 this->getGlobalBounds().contains(rect.top, rect.left + rect.width) &&
		 this->getGlobalBounds().contains(rect.top + rect.height, rect.left + rect.width));

}

bool toDelete(std::unique_ptr<StaticObjects> & object)
{
	return object->beenEaten();
}

bool isDoor(std::unique_ptr<StaticObjects>& object)
{
	return std::string(typeid(*object).name()) == "class Door";
}

void Board::deleteDoor()
{
	auto index = std::find_if(m_statics.begin(), m_statics.end(), isDoor);
	if (index == m_statics.end())
	{
		return;
	}
	
	index->get()->isEaten();
}

void Board::handleCollisions(const std::string& object)
{
	if (object == "class Key")
		deleteDoor();
	//else if (object == "class Door")
		//deleteDoor();
}
