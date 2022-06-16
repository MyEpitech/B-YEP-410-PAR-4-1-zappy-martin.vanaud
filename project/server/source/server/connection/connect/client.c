/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#include "minilib.h"
#include "netlib.h"

#include "server/server.h"

void connect_client(server_t *server)
{
    int client_socket;

    if (FD_ISSET(server->ss->server, &server->sd->readfd))
    {
        if ((client_socket = accept(server->ss->server,
                                 (struct sockaddr *)&server->address, (socklen_t *)&server->address_length)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        add_client_to_server(server, client_socket);

        printf("%s", get_request(client_socket));
        send_response(client_socket, "WELCOME\n");

        char *team_name = get_request(client_socket);
        // TODO: HANDLE HERE TEAM NAME

        // send_response(client_socket, strcat(my_itoa(client_socket), "\n10 10\n"));
    }

    // handle_client(server);
}

void handle_client(server_t *server)
{
    for (int index = 0; index < server->ss->max_client; index += 1) {

        server->sd->socket_descriptor = server->ss->client[index];

        client_sent_request(server, server->ss->client[index]);
    }
}

void client_sent_request(server_t *server, int client_socket)
{
    // HANDLE REQUEST HERE

    printf("%s", get_request(client_socket));
    send_response(client_socket, "OK\n");
}

void clear_socket_set(server_t *server)
{
    FD_ZERO(&server->sd->readfd);
}

void add_server_socket_to_set(server_t *server)
{
    FD_SET(server->ss->server, &server->sd->readfd);
    server->sd->max_socket_descriptor = server->ss->server;
}

void add_client_socket_to_set(server_t *server)
{
    for (int index = 0; index < server->ss->max_client; index += 1)
    {
        server->sd->socket_descriptor = server->ss->client[index];

        if (server->sd->socket_descriptor > 0)
            FD_SET(server->sd->socket_descriptor, &server->sd->readfd);

        if (server->sd->socket_descriptor > server->sd->max_socket_descriptor)
            server->sd->max_socket_descriptor = server->sd->socket_descriptor;
    }
}

void wait_for_connections(server_t *server)
{
    if ((select(server->sd->max_socket_descriptor + 1, &server->sd->readfd, NULL, NULL, NULL) < 0))
    {
        perror("select");
    }
}

void add_client_to_server(server_t *server, int client_socket)
{
    for (int index = 0; index < server->ss->max_client; index += 1)
    {
        if (server->ss->client[index] == 0)
        {
            server->ss->client[index] = client_socket;
            break;
        }
    }
}
