#include "Menu.h"

Menu::Menu()
{
    if (!font.loadFromFile("../../../src/ProjetShoot/wonderful_christmas_3/WonderfulChristmas_PERSONAL_USE_ONLY.otf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    title.setFont(font);
    title.setString("Menu");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setPosition(900, 200);
    selectedOptionIndex = 0;
}

void Menu::SetBackground(const std::string& textureFile)
{
    if (!backgroundTexture.loadFromFile(textureFile))
    {
        throw std::runtime_error("Failed to load background texture");
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void Menu::AddOption(const std::string& text)
{
    sf::Text option;
    option.setFont(font);
    option.setString(text);
    option.setCharacterSize(70);
    option.setFillColor(sf::Color::White);
    option.setPosition(950, 350 + options.size() * 80);
    options.push_back(option);
}

void Menu::HandleInput(const sf::Event& event, std::function<void(int)> onOptionSelected)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            selectedOptionIndex = (selectedOptionIndex - 1 + options.size()) % options.size();
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            selectedOptionIndex = (selectedOptionIndex + 1) % options.size();
        }
        else if (event.key.code == sf::Keyboard::Enter)
        {
            onOptionSelected(selectedOptionIndex);
        }
    }
}


//Updat lors de la selection
void Menu::Update()
{
    for (size_t i = 0; i < options.size(); ++i)
    {
        options[i].setFillColor(i == selectedOptionIndex ? sf::Color::Yellow : sf::Color::White);
    }
}


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backgroundSprite, states);
    target.draw(title, states);
    for (const auto& option : options)
    {
        target.draw(option, states);
    }
}
