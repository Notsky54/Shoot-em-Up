#include "ScrollingMap.h"

ScrollingMap::ScrollingMap(const std::string& textureFile1, const std::string& textureFile2, float speed)
    : bgSpeed(speed), posY1(0.f), posY2(0.f)
{
    if (!backgroundTexture1.loadFromFile(textureFile1))
    {
        std::cerr << "Erreur : impossible de charger la texture " << textureFile1 << std::endl;
    }
    backgroundSprite1.setTexture(backgroundTexture1);

    if (!backgroundTexture2.loadFromFile(textureFile2))
    {
        std::cerr << "Erreur : impossible de charger la texture " << textureFile2 << std::endl;
    }
    backgroundSprite2.setTexture(backgroundTexture2);
    backgroundSprite2.setPosition(0.f, -backgroundSprite2.getGlobalBounds().height);
}

void ScrollingMap::Update(float elapsedTime)
{
    float moveDistance = bgSpeed * elapsedTime;

    posY1 += moveDistance;
    posY2 += moveDistance;

    if (posY1 >= backgroundSprite1.getGlobalBounds().height)
    {
        posY1 = posY2 - backgroundSprite1.getGlobalBounds().height;
    }

    if (posY2 >= backgroundSprite2.getGlobalBounds().height)
    {
        posY2 = posY1 - backgroundSprite2.getGlobalBounds().height;
    }

    backgroundSprite1.setPosition(0.f, posY1);
    backgroundSprite2.setPosition(0.f, posY2);
}

void ScrollingMap::Draw(sf::RenderWindow& target)
{
    target.draw(backgroundSprite1);
    target.draw(backgroundSprite2);
}
