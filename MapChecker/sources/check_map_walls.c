#include "../includes/header.h"

static int  check_top_bot_lines(char **map);

int check_map_walls(char **map)
{
    if (!check_top_bot_lines(map))
    {
        print_error_msg("The map is not surrounded by Walls");
        return (FALSE);
    }
    return (TRUE);
}

static int  check_top_bot_lines(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        if (i == 0 || !map[i + 1])
        {
            printf("Line [%d] - \'%s\'\n", i, map[i]);
            j = 0;
            while (map[i][j])
            {
                if ((map[i][j] >= 9 && map[i][j] <= 13) || map[i][j] == 32
                    || map[i][j] == '1')
                    j++;
                else
                    return (FALSE);
            }
        }
        i++;
    }
    return (TRUE);
}
