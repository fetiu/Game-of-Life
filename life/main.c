#include <stdio.h>

#include "life.h"

int main(int argc, char *argv[])
{
    char input[] =
        "     "
        " xxx "
        "     "
        " xxx "
        "     ";

    struct life_s* life = life_begin(input, 5, 5);

    life_update(life);

    life_draw(life);

    life_end(life);

    return 0;
}
