#include "Controller.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "HUD.h"
#include "Render.h"
#include <fstream>

//game loop: closes only when user pressed exit
void Controller::run()
{
    bool finished = false;
    while (!finished)
    {        
        std::fstream file("Board.txt", std::fstream::in);

        auto render = Render({ 890, 680 });

        
        auto board = Board(file, render.getBoardSize(), render.getBoardPosition());

        auto hud = HUD({ 40 + 40 * 15 + 40, 40 });

        render.gameLoop(board, hud, finished);
    }
}



