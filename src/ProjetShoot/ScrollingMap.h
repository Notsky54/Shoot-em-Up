#pragma once
#include"Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class ScrollingMap
{
private:
    sf::Texture backgroundTexture1;
    sf::Sprite backgroundSprite1;
    sf::Texture backgroundTexture2;
    sf::Sprite backgroundSprite2;

    float bgSpeed;
    float posY1;
    float posY2;

public:
    ScrollingMap(const std::string& textureFile1, const std::string& textureFile2, float speed);
    void Update(float elapsedTime);
    void Draw(sf::RenderWindow& window);
};
