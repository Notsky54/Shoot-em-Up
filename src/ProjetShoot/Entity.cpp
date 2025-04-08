#include "Entity.h"

Entity::Entity()
{
    // Constructeur par défaut sans texture
}

Entity::Entity(const std::string& textureFile)
{
    if (!texture.loadFromFile(textureFile))
    {
        throw std::runtime_error("Failed to load texture: " + textureFile);
    }
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2); // Centrer le sprite
}

Entity::~Entity()
{
  
}

sf::Sprite& Entity::getSprite()
{
    return sprite;
}

sf::Vector2f Entity::getPosition() const
{
    return sprite.getPosition();
}

void Entity::Update(float deltaTime)
{
    deltaTime = 0;
}

bool Entity::isOffScreen() const
{
    const sf::FloatRect screenBounds(0.f, 0.f, 1920.f, 1080.f);
    return !screenBounds.intersects(sprite.getGlobalBounds());
}

sf::FloatRect Entity::IdBox() const
{
    return sprite.getGlobalBounds(); 
}






