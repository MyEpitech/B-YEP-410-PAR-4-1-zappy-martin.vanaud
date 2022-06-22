/*
** EPITECH PROJECT, 2022
** project
** File description:
** left_request
*/

#include "ai_request.h"

void ai_left_request(zappy_t *zappy, void *data, int player_index)
{
    int socket = zappy->server->socket_descriptor->socket_descriptor;

    if (zappy->client[player_index].player.orientation <= NORTH)
        zappy->client[player_index].player.orientation = WEST;
    else
        zappy->client[player_index].player.orientation -= 1;
    ai_response_ok_ko(socket, true);
}