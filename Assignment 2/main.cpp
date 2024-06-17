#include <SFML/Graphics.hpp>
#include<iostream>
#include "Vec2.h"
#include "Game.h"

int main()
{
    Game g("config.txt");
    g.run();
    std::cout << "Output on console" << std::endl;

    std::cout << std::endl << "=====================================================================================";

    return 0;
}