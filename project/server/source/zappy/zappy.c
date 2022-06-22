/*
** EPITECH PROJECT, 2022
** project
** File description:
** zappy
*/

#include <stdlib.h>

#include "minilib.h"
#include "server.h"

zappy_t *init_zappy(void)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));

    if (!zappy)
        return NULL;
    zappy->options = malloc(sizeof(options_t));
    if (!zappy->options) {
        free(zappy);
        return NULL;
    }
    setup_options(zappy->options);
    return zappy;
}

bool setup_zappy_content(zappy_t *zappy)
{
    zappy->options->team_names = my_strtok(zappy->options->names, ' ');
    if (!zappy->options->team_names)
        return false;
    zappy->options->max_clients = my_arrlen(zappy->options->team_names) * zappy->options->clients_nb;
    zappy->client = malloc(sizeof(ai_client_t) * zappy->options->clients_nb);
    if (!zappy->client)
        return false;
    zappy->server = malloc(sizeof(server_t));
    if (!zappy->server)
        return false;
    zappy->map = create_map(10, 10);
    zappy->resources = setup_resources(10, 10);
    if (!setup_server(zappy->server, zappy->options))
        return false;
    return true;
}

void free_zappy(zappy_t *zappy)
{
    free_options(zappy->options);
    free(zappy->client);
    free_map(zappy->map);
    free_resources(zappy->resources);
    free_server(zappy->server);
    free(zappy);
}