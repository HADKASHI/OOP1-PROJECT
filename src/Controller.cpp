#pragma once
#include "Controller.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "MainMenu.h"

//game loop: closes only when user pressed exit
void Controller::run()
{
    auto render = Render(WINDOW_SIZE);

    auto mainMenu = MainMenu();
    mainMenu.menuLoop(&render);
}



