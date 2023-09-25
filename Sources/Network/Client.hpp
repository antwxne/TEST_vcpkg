//
// Created by antoine on 25/09/23.
//

#ifndef R_TYPE_CLIENT_HPP
#define R_TYPE_CLIENT_HPP

#include <cstdint>
#include <vector>

#include <asio.hpp>

class Client {
public:
    Client(asio::io_context &ioContext);
    std::vector <uint8_t> _buffer;
    asio::ip::tcp::socket _socket;
    std::string ToString() const;
};

#endif //R_TYPE_CLIENT_HPP
