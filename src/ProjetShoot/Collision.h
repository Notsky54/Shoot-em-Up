#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Collision
{
public:
    // M�thode pour v�rifier la collision entre deux rectangles englobants
    static bool checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);

    // M�thode pour v�rifier la collision entre deux entit�s d�rivant d'Entity
    static bool checkCollision(const Entity& entity1, const Entity& entity2);

    // M�thode pour v�rifier la collision entre une balle et une entit�
    static bool checkCollision(const sf::Sprite& bullet, const Entity& entity);
};


