#include <SFML/Graphics.hpp>
#include<iostream>
#include "Vec2.h"
#include "Game.h"

int main()
{
    Game g("Config.txt");
    g.run();
    std::cout << "Output on console" << std::endl;

    Vec2 v1(100, 200);
    Vec2 v2(10, 20);
    Vec2 v4 = v1 + v2;
    float d = v2.dist(v1);
    std::cout << d << std::endl;
    v4.normalize();
    std::cout << v4.x << "," << v4.y << std::endl;
    if (v1 != v2)
        std::cout << v1.x;
    else
        std::cout << v2.x;

    std::cout << std::endl << "=====================================================================================";

    return 0;
}