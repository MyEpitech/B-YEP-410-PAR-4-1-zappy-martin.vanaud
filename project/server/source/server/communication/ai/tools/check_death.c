/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** check_death
*/

#include "ai_request.h"

bool check_death(zappy_t *zappy, int player_index)
{
    if (zappy->client[player_index].player.resource_inventory[FOOD].quantity <= 0) {
        // dprintf(zappy->client[player_index].socket, "dead\n"); // ici ou pas ?
        return (true);
    }
    return (false);
}
