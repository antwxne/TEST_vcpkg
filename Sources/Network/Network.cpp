//
// Created by antoine on 25/09/23.
//

#include <iostream>
#include "Network.hpp"

Network::Network(unsigned int port): _io_context(), _acceptor(_io_context)
{
    asio::ip::tcp::endpoint basicEndPoint(
        asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
    _acceptor.open(basicEndPoint.protocol());
    _acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(basicEndPoint);
    _acceptor.listen();
}

void Network::Run()
{
    StartAccept();

    _thread = std::thread([&]() {
        while (!_io_context.stopped()) {
            _io_context.run_one();
        }
    });
}

Network::~Network()
{
    _io_context.stop();
    if (_thread.joinable()) {
        _thread.join();
    }
}

void Network::StartAccept()
{
    _client = std::make_unique<Client>(_io_context);

    _acceptor.async_accept(_client->_socket, std::bind(&Network::AcceptCallBack, this, std::ref(*_client)));
}

void Network::AcceptCallBack(Client &client)
{
    if (client._socket.native_handle() < 0) {
        std::cerr << "Client fd corrupted" << std::endl;
        StartAccept();
        return;
    }
    std::cout << "Client connected" << std::endl;
    StartReceive(client);
}

void Network::StartReceive(Client &client)
{
    #ifdef _WIN32
    std::string delimiter = "\n";
    #else
    std::string delimiter = "\n";
    #endif
    asio::async_read_until(client._socket,
        asio::dynamic_buffer(client._buffer), delimiter,
        std::bind(&Network::ReceiveCallBack, this, std::ref(client),
            std::placeholders::_1, std::placeholders::_2));
}

void Network::ReceiveCallBack(Client &client, const std::error_code &error,
    const std::size_t bytes_transfered
)
{
    // magic value to handle when the client CTRL C
    if (error == asio::error::eof || error.value() == 10054) {
        std::cout << "Client disconnected" << std::endl;
        StartAccept();
        return;
    }
    setString(client.ToString());
    client._buffer.erase(client._buffer.begin(), client._buffer.end());
    #ifdef _WIN32
    std::string response = "OK\r\n";
    #else
    std::string response = "OK\n";
    #endif
    SendResponse(client, response);
    StartReceive(client);
}

void Network::SendResponse(Client &client, const std::string &data)
{
    client._socket.async_send(asio::buffer(&*data.begin(), data.size() * sizeof *data.begin()), [&](const asio::error_code &errorCode,
        std::size_t bytesTransferred){
    });
}
