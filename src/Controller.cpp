#include "Controller.h"
#include <iostream>
#include "Render.h"
#include "MainMenu.h"



void Controller::run()
{
    auto render = Render({ 890, 680 });

    auto mainMenu = MainMenu();
    mainMenu.menuLoop(&render);

}



