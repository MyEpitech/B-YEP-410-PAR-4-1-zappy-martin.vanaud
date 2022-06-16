/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** client
*/

#include "minilib.h"
#include "netlib.h"

#include "server/server.h"

void connect_client(server_t *server, options_t *options)
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

        // REQUEST/RESPONSE BLOCK
        printf("%s", get_request(client_socket));
        send_response(client_socket, "WELCOME\n");

        // REQUEST/RESPONSE BLOCK
        char *team_name = get_request(client_socket);
        bool status = false;
        for (int index = 0; index < options->clients_nb; index += 1) {
            if (strncmp(team_name, options->team_names[index], strlen(team_name - 1)) == 0) {
                status = true;
                break;
            }
        }
        // TODO: store team_name and create a client
        printf("%s", team_name);
        if (!status) {
            send_response(client_socket, "KO\n");
            close(server->ss->client[client_socket]);
            server->ss->client[client_socket] = -1;
        } else {
            send_response(client_socket, "OK\n");
        }

        // REQUEST/RESPONSE BLOCK
        __attribute__((unused)) char *accepted = get_request(client_socket);
        send_response(client_socket, strcat(my_itoa(client_socket), "\n10 10\n"));
    }

    // HANDLE REQUEST HERE
    // handle_client(server);
}

void handle_client(server_t *server)
{
    for (int index = 0; index < server->ss->max_client; index += 1) {

        server->sd->socket_descriptor = server->ss->client[index];

        client_sent_request(server, server->ss->client[index]);
    }
}

void client_sent_request(__attribute__((unused)) server_t *server, int client_socket)
{
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
        exit(EXIT_FAILURE);
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
