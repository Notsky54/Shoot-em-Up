#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Collision
{
public:
    // Méthode pour vérifier la collision entre deux rectangles englobants
    static bool checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);

    // Méthode pour vérifier la collision entre deux entités dérivant d'Entity
    static bool checkCollision(const Entity& entity1, const Entity& entity2);

    // Méthode pour vérifier la collision entre une balle et une entité
    static bool checkCollision(const sf::Sprite& bullet, const Entity& entity);
};


