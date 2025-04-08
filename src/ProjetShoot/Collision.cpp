#include "Collision.h"

bool Collision::checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) 
{
    return rect1.intersects(rect2);
}

bool Collision::checkCollision(const Entity& entity1, const Entity& entity2)
{
    // Vérifier si les sprites des deux entités entrent en collision
    return entity1.getSprite().getGlobalBounds().intersects(entity2.getSprite().getGlobalBounds());

}

bool Collision::checkCollision(const sf::Sprite& bullet, const Entity& entity) 
{
    return checkCollision(bullet.getGlobalBounds(), entity.IdBox());
}
