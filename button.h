
#pragma once

#include <SFML/Graphics.hpp>

namespace myA {

    class Button {
    public:
        std::string name_;
        sf::RenderWindow* window_ = nullptr;
        sf::RectangleShape button_;
        sf::Text text_;
        Button();
        Button(sf::RenderWindow&, std::string, sf::Font&, float, float, float, float, const unsigned char, const unsigned char, const unsigned char);
        ~Button();
    private:
        sf::FloatRect textRect_;
    };
}

/*
    while (window.isOpen())
    {
        // ...

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (button.getGlobalBounds().contains(mousePos.x, mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // Button wurde geklickt
            // ...
        }

        // ...


    class Spieler
    {
    public:
        Spieler(sf::RenderWindow& window) : window(window)
        {
            // Initialisierung der Spielfigur
            sprite.setTexture(texture);
            // ...
        }

        void update()
        {
            // Bewegung, Animationen, ...
        }

        void draw()
        {
            window.draw(sprite);
        }

    private:
        sf::RenderWindow& window;
        sf::Sprite sprite;
        sf::Texture texture;
    };
*/