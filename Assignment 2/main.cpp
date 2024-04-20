#include <SFML/Graphics.hpp>
#include<iostream>
#include "Vec2.h"
//#include "Game.h"

int main()
{
    //Game g("Config.txt");
    //g.run();
    std::cout << "Output on console" << std::endl;

    Vec2 v1(100, 200);
    Vec2 v2(10, 20);
    Vec2 v3 = v1 + v2;
    std::cout << v3.x << "," << v3.y;

    std::cout << std::endl << "=====================================================================================";

    return 0;
}