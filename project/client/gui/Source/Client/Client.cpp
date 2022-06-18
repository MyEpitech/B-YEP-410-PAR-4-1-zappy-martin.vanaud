/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** Client
*/

extern "C" {
    #include "netlib.h"
    #include "protocol/greeting.h"
}

#include "Client.hpp"

Client::Client()
{
    _options = std::make_unique<Options>();
}

Client::~Client()
{
}

void Client::setup()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
        throw ClientErrors("Socket initialization");

    bzero(&_server, sizeof(_server));

    _server.sin_family = AF_INET;
    _server.sin_addr.s_addr = inet_addr(_options->getMachine().c_str());
    _server.sin_port = htons(_options->getPort());
}

void Client::connection()
{
    if (connect(_socket, (struct sockaddr *)&_server, sizeof(_server)) != 0)
        throw ClientErrors("Connect failed");
    else
        handle();
}

void Client::handle()
{
    // SEND CLIENT TYPE & GET WELCOME MESSAGE
    post_request(_socket, request_payload_t{"GRAPHIC\n"});
    response_payload_t response = get_response(_socket);
    std::cout << response.payload;

    // SEND TEAM NAME & GET OK RESPONSE
    post_request(_socket, request_payload_t{"GRAPHIC"});
    response_payload_t team_response = get_response(_socket);

    // SEND INFO REQUEST & GET CLIENT NUMBER
    post_request(_socket, request_payload_t{"INFO CLIENT\n"});
    response_payload_client_number_t client_number_response = get_response_client_number(_socket);
    _clientNumber = client_number_response.client_id;
    std::cout << client_number_response.client_id << std::endl;
}

std::pair<int, int> Client::getMapDimension()
{
    int unblock = 0;

    // SEND INFO REQUEST & GET MAP DIMENSIONS
    std::pair<int, int> mapDimension(9, 9);
    post_request(_socket, request_payload_t{"INFO MAP\n"});
    response_payload_map_t map_response = get_response_map(_socket);
    mapDimension.first = map_response.width;
    mapDimension.second = map_response.height;
    std::cout << "mapSize" << map_response.height << " " << map_response.width << std::endl;

    // UNBLOCK SOCKET
    unblock = fcntl(_socket, F_GETFL, 0);
    fcntl(_socket, F_SETFL, unblock | O_NONBLOCK);
    return (mapDimension);
}

void Client::serverSentResponse()
{
    // CODE HERE ALL RESPONSES RELATED FUNCTIONS

    return;
}


void Client::setupOptions(int ac, char **av)
{
    _options->setupOptions(ac, av);
}

void Client::handleOptions()
{
    _options->handleOptions();
}

void Client::listen()
{
    char *data = nullptr;
    int readResult = 0;
    payload_header_t header = {SENDER_ID::GUI, 0, 0};

    readResult = read(_socket, &header, sizeof(payload_header_t));
    if (readResult <= 0) {
        return;
    }
    data = (char*)malloc(header.size);
    readResult = read(_socket, data, header.size);
    if (readResult <= 0)
        return;
    _eventsHandler.eventReceive(data, header.type);
    free(data);
}
