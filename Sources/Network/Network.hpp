//
// Created by antoine on 25/09/23.
//

#ifndef R_TYPE_NETWORK_HPP
#define R_TYPE_NETWORK_HPP

#include <string>
#include <vector>

#include <asio.hpp>

#include "Client.hpp"

class Network {
public:
    Network(unsigned int port = 80);
    ~Network();
    void Run();
    void StartAccept();
    void AcceptCallBack(Client &client);
    void StartReceive(Client &client);
    void ReceiveCallBack(Client &client, const std::error_code &error,
        std::size_t bytes_transfered);
    std::function<void(const std::string &)> setString;
    void SendResponse(Client &client, const std::string &data);

private:
    asio::io_context _io_context;
    asio::ip::tcp::acceptor _acceptor;
    std::thread _thread;
    std::unique_ptr<Client> _client;
};

#endif //R_TYPE_NETWORK_HPP
