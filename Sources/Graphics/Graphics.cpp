//
// Created by antoine on 25/09/23.
//

#include <SFML/Window/Event.hpp>
#include "Graphics.hpp"

Graphics::Graphics(unsigned int window_x, unsigned int window_y) : _window(sf::VideoMode(window_y, window_x), "VCPKG"),
_font()
{
    _font.loadFromFile("./Assets/font.ttf");
    _text.setFont(_font);
    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(60);
    _text.setString("");
}

void Graphics::Run()
{
    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _window.clear(sf::Color::White);
        _window.draw(_text);
        _window.display();
    }
}

