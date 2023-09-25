//
// Created by antoine on 25/09/23.
//

#include "Client.hpp"

Client::Client(asio::io_context &ioContext): _socket(ioContext)
{
}

std::string Client::ToString() const
{
    std::string dest;
    dest.resize(_buffer.size() * sizeof *_buffer.begin());
    std::memcpy(&*dest.begin(), &*_buffer.begin(), _buffer.size()* sizeof *_buffer.begin());
    return dest;
}
