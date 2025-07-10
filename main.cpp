#include <iostream>

#include "Cofig.h"
#include "Game.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"


int main() {
    std::cout << "Hello Player!" << std::endl;
    Cofig g_cofigconfig = Cofig();
    int n = 1;

    while (!n == g_cofigconfig.configureateGame()) {


        Game game1 = Game(g_cofigconfig);


    }










    return 0;
}
