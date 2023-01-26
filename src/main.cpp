#pragma once
//#include "Macros.h"
#include "Controller.h"
#include "Resources.h"
#include "Board.h"

int main()
{
    srand(time(NULL));
    auto controller = Controller();
    controller.run();
 
    return EXIT_SUCCESS;
}
