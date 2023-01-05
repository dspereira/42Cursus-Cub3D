#include "../includes/header.h"

static int  get_number(char *src, int *index);

/*
    int bgrValue = (b << 16) + (g << 8) + r
*/
int get_rgb_colour(char *src, int *tex_count, int actual_colour)
{
    int r;
    int g;
    int b;
    int index;

    if (actual_colour != -1)
        return (actual_colour);
    index = 2;
    while ((src[index] >= 9 && src[index] <= 13) || src[index] == 32)
        index++;
    r = get_number(src, &index);
    g = get_number(src, &index);
    b = get_number(src, &index);
    if (r == -1 || g == -1 || b == -1)
        return (-1);
    *tex_count += 1;
    return ((r << 16) + (g << 8) + b);
}

static int  get_number(char *src, int *index)
{
    int nbr;
    int i;

    i = *index;
    nbr = 0;
    if (!(src[i] >= '0' && src[i] <= '9'))
        return (-1);
    while (src[i] >= '0' && src[i] <= '9')
    {
        nbr = (nbr * 10) + (src[i] - 48);
        i++;
    }
    if (src[i] == ',')
        *index = i + 1;
    if (nbr > 255 || nbr < 0)
        nbr = -1;
    return (nbr);
}
