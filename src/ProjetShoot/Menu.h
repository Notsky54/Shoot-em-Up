#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include <string>
#include <vector>
#include <functional>

class Menu : public sf::Drawable
{
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> options;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    int selectedOptionIndex = 0;
public:
    Menu();
    void SetBackground(const std::string& textureFile);
    void AddOption(const std::string& text);
    void HandleInput(const sf::Event& event, std::function<void(int)> onOptionSelected);
    void Update();

protected:
    void  draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

