//
// Created by antoine on 25/09/23.
//

#ifndef R_TYPE_GRAPHICS_HPP
#define R_TYPE_GRAPHICS_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Graphics {
public:
    Graphics(unsigned int window_x = 1080, unsigned int window_y = 1920);
    void Run();
    sf::Text _text;

private:
    sf::RenderWindow _window;
    sf::Font _font;


};

#endif //R_TYPE_GRAPHICS_HPP
