#include "Controller.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "HUD.h"
#include "Render.h"
#include <fstream>
#include "MainMenu.h"

//game loop: closes only when user pressed exit
void Controller::run()
{
    auto render = Render({ 890, 680 });

    auto mainMenu = MainMenu();
    mainMenu.menuLoop(&render);
}



