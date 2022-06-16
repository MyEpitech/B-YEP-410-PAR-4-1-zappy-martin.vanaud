/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>

#include "../server/include/options/options.h"

void redirect_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(server_test, options_handling_correct, .init = redirect_std)
{
    int ac = 13;
    char *av[13] = {"./zappy_server",
                          "-p", "4242",
                          "-x", "20",
                          "-y", "20",
                          "-n", "marvin",
                          "-c", "5",
                          "-f", "10"};

    options_t *options = malloc(sizeof(options_t));
    int options_status = 1;

    setup_options(options);

    options_status = get_options(ac, av, options);
    if (options_status != EXIT_FAILURE)
        cr_assert(true);

    options_status = handle_options(options);
    if (options_status != EXIT_FAILURE)
        cr_assert(true);

    free_options(options);
}

Test(server_test, options_handling_helper, .init = redirect_std)
{
    int ac = 2;
    char *av[2] = {"./zappy_server", "-h"};

    options_t *options = malloc(sizeof(options_t));
    int options_status = 1;

    setup_options(options);

    options_status = get_options(ac, av, options);
    if (options_status == EXIT_FAILURE)
        cr_assert(true);

    free_options(options);
}

Test(server_test, options_handling_missing, .init = redirect_std)
{
    int ac = 7;
    char *av[7] = {"./zappy_server",
                          "-p", "4242",
                          "-x", "20",
                          "-y", "20",};

    options_t *options = malloc(sizeof(options_t));
    int options_status = 1;

    setup_options(options);

    options_status = get_options(ac, av, options);
    if (options_status == EXIT_FAILURE)
        cr_assert(true);

    debug_options(options);

    free_options(options);
}

// Test(server_test, options_handling_invalid, .init = redirect_std)
// {
//     int ac = 13;
//     char *av[13] = {"./zappy_server",
//                           "-p", "4242",
//                           "-x", "20",
//                           "-y", "20",
//                           "-n", NULL,
//                           "-c", "5",
//                           "-f", "10"};

//     options_t *options = malloc(sizeof(options_t));
//     int options_status = 1;

//     setup_options(options);

//     options_status = get_options(ac, av, options);
//     if (options_status == EXIT_FAILURE)
//         cr_assert(true);

//     options_status = handle_options(options);
//     if (options_status == EXIT_FAILURE)
//         cr_assert(true);

//     free_options(options);
// }

// Test(server_test, options_handling_unknown, .init = redirect_std)
// {
//     int ac = 13;
//     char *av[13] = {"./zappy_server",
//                           "-p", "4242",
//                           "-x", "20",
//                           "-j", "20",
//                           "-n", "marvin",
//                           "-c", "5",
//                           "-f", "10"};

//     options_t *options = malloc(sizeof(options_t));
//     int options_status = 1;

//     setup_options(options);

//     options_status = get_options(ac, av, options);
//     if (options_status == EXIT_FAILURE)
//         cr_assert(true);

//     options_status = handle_options(options);
//     if (options_status == EXIT_FAILURE)
//         cr_assert(true);

//     free_options(options);
// }

#include "../server/include/zappy/map/map.h"
#include "../server/include/zappy/map/resources.h"

Test(server_test, map_creation, .init = redirect_std)
{
    int width = 20;
    int height = 20;

    map_t *map = malloc(sizeof(map_t));

    create_map(map, width, height);

    free_map(map);
}

Test(server_test, resources_creation, .init = redirect_std)
{
    int width = 20;
    int height = 20;

    map_t *map = malloc(sizeof(map_t));
    resources_t *resources = malloc(sizeof(resources_t));

    create_map(map, width, height);

    resources_t resource[] = {
        {
            .name = "food",
            .resources = FOOD,
            .density = 0.5,
            .quantity = 0,
        },
        {
            .name = "linemate",
            .resources = LINEMATE,
            .density = 0.3,
            .quantity = 0,
        },
        {
            .name = "deraumere",
            .resources = DERAUMERE,
            .density = 0.15,
            .quantity = 0,
        },
        {
            .name = "sibur",
            .resources = SIBUR,
            .density = 0.1,
            .quantity = 0,
        },
        {
            .name = "mendiane",
            .resources = MENDIANE,
            .density = 0.1,
            .quantity = 0,
        },
        {
            .name = "phiras",
            .resources = PHIRAS,
            .density = 0.08,
            .quantity = 0,
        },
        {
            .name = "thystame",
            .resources = THYSTAME,
            .density = 0.05,
            .quantity = 0,
        },
    };

    setup_resources(resource, map->width, map->height);

    float number_of_resources = 0.0f;
    for (int index = 0; index < NB_ITEMS ; index += 1)
        number_of_resources += resource[index].quantity;

    map->ratio = number_of_resources / map->size;

    fill_map(map, resource);

    debug_map(map, resources);

    free_map(map);

    free_resources(resources);
}

#include "../server/include/server/server.h"

Test(server_test, server_creation, .init = redirect_std)
{
    int ac = 13;
    char *av[13] = {"./zappy_server",
                          "-p", "4242",
                          "-x", "20",
                          "-y", "20",
                          "-n", "marvin",
                          "-c", "5",
                          "-f", "10"};

    options_t *options = malloc(sizeof(options_t));
    int options_status = 1;

    setup_options(options);

    options_status = get_options(ac, av, options);
    if (options_status != EXIT_FAILURE)
        cr_assert(true);

    options_status = handle_options(options);
    if (options_status != EXIT_FAILURE)
        cr_assert(true);

    server_t *server = malloc(sizeof(server_t));

    setup_server(server, options);
    initialise_all_clients_sockets(server);
    create_server_socket(server);
    allow_multiple_connections(server);

    configure_socket_type(server);

    free_options(options);

    free_server(server);
}
