#include <iostream>
#include "Graphics/Graphics.hpp"
#include "Network/Network.hpp"
int main()
{
    Network server(8080);
    Graphics graphic;

    server.setString = [&](const std::string &str){
        graphic._text.setString(str);
    };
    server.Run();
    graphic.Run();
    return 0;
}