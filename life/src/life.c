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

static void spawn(linked_list_t *cells, point_t pos);
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
            if(matrix[y * height + x] == 'o')
            {
                point_t pos = {x, y};
                spawn(&life->cells, pos);
            }
        }
    }
    return life;
}

int life_count_neighbor(int x, int y, linked_list_t *cells)
{
    int count = 0;
    linked_list_node_t *node;
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
        if (SUCCESS == linked_list_find_node(cells, poscmp, &neighbor[i], &node))
        {
            count++;
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
    linked_list_node_t *node;

    if (cells->count == 0)
    {
        return;
    }

    /* copy cells to a local buffer before update */
    struct {
        linked_list_node_t node;
        point_t data;
    } clone[cells->count];

    linked_list_t old;
    linked_list_init(&old);

    for (node = cells->front; node != NULL; node = node->next)
    {
        int i = old.count; //count increases after insertion
        clone[i].data = *(point_t *)node->data;
        linked_list_set_node_data(&clone[i].node, &clone[i].data);
        linked_list_insert_node_at_front(&old, &clone[i].node);
    }

    for (int y = 0; y < life->height; y++)
    {
        for (int x = 0; x < life->width; x++)
        {
            enum result_e result;
            point_t pos = {x, y};

            int density = life_count_neighbor(x, y, &old);
            log("%d cells around cell(%d, %d)", density, x, y);

            result = linked_list_find_node(cells, poscmp, &pos, &node);

            if (result == NOT_FOUND)
            {
                if (density == 3)
                {
                    spawn(cells, pos);
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
                log("keep cell(%d, %d)", x, y);
            }
        }
    }
    linked_list_deinit(&old);
}

void life_draw(struct life_s* life)
{
    linked_list_node_t *node = life->cells.front;
    printf("\033[2J"); // Clear the screen, move to (0,0)

    while (node != NULL)
    {
        point_t *pos = node->data;
        /* Draw 'o' on desirable position (x + 1, y + 1) */
        printf("\033[%dd\033[%dGo", pos->y + 1, pos->x + 1);
        node = node->next;
    }
    printf("\033[%dd\n", life->height); // Move to the end
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

static void spawn(linked_list_t *cells, point_t pos)
{
    point_t *data = malloc(sizeof(point_t));
    linked_list_node_t *node = malloc(sizeof(linked_list_node_t));
    data->x = pos.x;
    data->y = pos.y;
    linked_list_set_node_data(node, data);
    linked_list_insert_node_at_front(cells, node);
    log("new cell(%d, %d)", pos.x, pos.y);
}

static bool poscmp(linked_list_node_t *node_to_compare, void *user_data)
{
    point_t p1 = *(point_t *)user_data;
    point_t p2 = *(point_t *)node_to_compare->data;
    return point_is_equal(p1, p2);
}
