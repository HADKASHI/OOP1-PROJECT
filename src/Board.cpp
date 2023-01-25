#include "Board.h"
#include <iostream>
#include <cstdlib>


Board::Board(std::fstream& file, sf::Vector2f maxSize, sf::Vector2f position)
	:m_position(position), m_tileEdgeSize(40)
{	
	loadBoard(file, maxSize);
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

	char c;

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

	if(!file.eof()) file.ignore();

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

