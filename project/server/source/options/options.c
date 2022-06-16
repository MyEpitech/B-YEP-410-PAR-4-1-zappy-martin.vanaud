/*
** EPITECH PROJECT, 2022
** B-YEP-410-PAR-4-1-zappy-martin.vanaud
** File description:
** options
*/

#include "options/options.h"
#include "options/usage.h"

#include "minilib.h"

void setup_options(options_t *options)
{
    options->port = -1;
    options->width = -1;
    options->height = -1;
    options->names = NULL;
    options->team_names = NULL;
    options->clients_nb = -1;
    options->freq = 100;
}

int get_options(int ac, char **av, options_t *options)
{
    int opt = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"port", required_argument, 0, 'p'},
        {"width", required_argument, 0, 'x'},
        {"heigth", required_argument, 0, 'y'},
        {"nameX", required_argument, 0, 'n'},
        {"clients_nb", required_argument, 0, 'c'},
        {"freq", optional_argument, 0, 'f'},
        {0, 0, 0, 0}};

    int long_index = 0;
    while ((opt = getopt_long(ac, av, "hp:x:y:n:c:f:",
                              long_options, &long_index)) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_usage(OPTIONS_ERROR_NONE);
            return (EXIT_FAILURE);
        case 'p':
            options->port = my_atoi(optarg);
            break;
        case 'x':
            options->width = my_atoi(optarg);
            break;
        case 'y':
            options->height = my_atoi(optarg);
            break;
        case 'n':
            options->names = optarg;
            break;
        case 'c':
            options->clients_nb = my_atoi(optarg);
            break;
        case 'f':
            options->freq = my_atoi(optarg);
            break;
        default:
            print_usage(INVALID_OPTION);
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

int handle_options(options_t *options)
{
    if (options->port == -1 || options->width == -1 ||
        options->height == -1 || options->names == NULL ||
        options->clients_nb == -1)
    {
        print_usage(MISSING_OPTION);
        return (EXIT_FAILURE);
    }
    if (options->port == 0 || options->width == 0 ||
        options->height == 0 || options->names == NULL ||
        options->clients_nb == 0)
    {
        print_usage(INVALID_OPTION);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int check_clients(options_t *options)
{
    int count = 1;

    for (int index = 0; options->names[index]; index += 1) {
        if (options->names[index] == ' ')
            count += 1;
    }

    if (count != options->clients_nb)
        return (EXIT_FAILURE);

    options->team_names = malloc(sizeof(char *) * options->clients_nb);

    char *team_name = strtok(options->names, " ");

    for (int index = 0; team_name != NULL; index += 1) {
        options->team_names[index] = team_name;
        team_name = strtok(NULL, " ");
    }
}

void debug_options(options_t *options)
{
    printf("[DEBUG] options->port: %d\n", options->port);
    printf("[DEBUG] options->width: %d\n", options->width);
    printf("[DEBUG] options->height: %d\n", options->height);
    printf("[DEBUG] options->names: %s\n", options->names);
    printf("[DEBUG] options->clients_nb: %d\n", options->clients_nb);
    for (int index = 0; index < options->clients_nb; index += 1) {
        printf("[DEBUG] options->team_names[%d]: %s\n", index,
               options->team_names[index]);
    }
    printf("[DEBUG] options->freq: %d\n", options->freq);
}

void free_options(options_t *options)
{
    // for (int index = 0; index < options->clients_nb; index += 1)
    //     free(options->team_names[index]);
    free(options);
}
