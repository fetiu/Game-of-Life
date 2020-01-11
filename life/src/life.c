#include "life.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "point.h"

#ifdef VERBOSE
#define log(s, ...) printf(s "\n", __VA_ARGS__)
#else
#define log(s, ...)
#endif

/* abstract types */

struct life_s
{
    linked_list_t cells;
    int width;
    int height;
};

/* private prototypes */

static void spawn(linked_list_t *cells, void *pos);
static bool poscmp(linked_list_node_t *node_to_compare, void *user_data);


/* public functions */

struct life_s *life_begin(char matrix[], int width, int height)
{
    struct life_s* life = malloc(sizeof(struct life_s));
    life->width = width;
    life->height = height;

    linked_list_init(&life->cells);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if(matrix[y * height + x] != ' ')
            {
                point_t *pos = malloc(sizeof(point_t));
                pos->x = x;
                pos->y = y;
                spawn(&life->cells, pos);
                // log("new cell (%d, %d)", x, y);
            }
        }
    }
    return life;
}

int life_count_neighbor(int x, int y, linked_list_t *cells)
{
    int count = 0;
    linked_list_node_t *unused;
    point_t neighbor[8] = {
        {x - 1, y - 1},
        {x, y - 1},
        {x + 1, y - 1},
        {x - 1, y},
        {x + 1, y},
        {x - 1, y + 1},
        {x, y + 1},
        {x + 1, y + 1},
    };

    for (int i = 0; i < 8; i++)
    {
        if (SUCCESS == linked_list_find_node(cells,
                                             poscmp,
                                             &neighbor[i],
                                             &unused))
        {
            count++; log("found cell(%d, %d)", neighbor[i].x, neighbor[i].y);
        }
    }
    return count;
}

linked_list_t life_get_cells(struct life_s *life)
{
    return life->cells;
}

void life_update(struct life_s* life)
{
    linked_list_t *cells = &life->cells;
    linked_list_node_t *node = cells->front;
    linked_list_t old;
    linked_list_init(&old);

    struct {
        linked_list_node_t cell;
        point_t pos;
    } clone[cells->count];

    /* copy cells to a local buffer before update */
    for (node = cells->front; node != NULL; node = node->next)
    {
        int i = old.count; //count increases after insertion
        clone[i].pos = *(point_t *)node->data;
        linked_list_set_node_data(&clone[i].cell, &clone[i].pos);
        linked_list_insert_node_at_front(&old, &clone[i].cell);
    }

    for (int y = 0; y < life->height; y++)
    {
        for (int x = 0; x < life->width; x++)
        {
            enum result_e result;
            point_t *pos = malloc(sizeof(point_t));
            pos->x = x;
            pos->y = y;

            int density = life_count_neighbor(x, y, &old);
            log("(%d, %d): density = %d", x, y, density);

            result = linked_list_find_node(cells, poscmp, pos, &node);

            if (result == NOT_FOUND)
            {
                if (density == 3)
                {
                    spawn(cells, pos);
                    log("new cell(%d, %d)", x, y);
                }
            }
            else if (density > 3 || density < 2)
            {
                log("kill cell(%d, %d)", x, y);
                linked_list_remove_node(cells, node);
                free(node->data);
                free(node);
            }
            else
            {
                log("living cell(%d, %d)", x, y);
            }
        }
    }
    linked_list_deinit(&old);
}

void life_draw(struct life_s* life)
{
    linked_list_node_t *node = life->cells.front;
    system("clear");

    while (node != NULL)
    {
        point_t *pos = node->data;
        /* draw 'o' on the pos of x doubled and y plus 1 */
        printf("\033[%dd\033[%dGo", pos->y + 1, pos->x * 2);
        node = node->next;
    }
    /* end of the world */
    printf("\033[%dd\n", life->height);
}

void life_end(struct life_s* life)
{
    linked_list_node_t *node = life->cells.front;
    while (node != NULL)
    {
        free(node->data);
        free(node);
        node = node->next;
    }
    free(life);
}


/* private functions */

static void spawn(linked_list_t *cells, void *pos)
{
    linked_list_node_t *node = malloc(sizeof(linked_list_node_t));
    linked_list_set_node_data(node, pos);
    linked_list_insert_node_at_front(cells, node);
}

static bool poscmp(linked_list_node_t *node_to_compare, void *user_data)
{
    point_t p1 = *(point_t *)user_data;
    point_t p2 = *(point_t *)node_to_compare->data;
    return point_is_equal(p1, p2);
}
