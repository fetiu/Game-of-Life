#include "unity.h"

#include "life.h"
#include "point.h"
#include "linked_list.h"

#include <stdio.h>

static bool point_cmp(linked_list_node_t *node_to_compare, void *user_data);

linked_list_node_t *dummy_node;
static struct life_s* life;

void setUp(void)
{
    char input[] =
        "     "
        " ooo "
        "     "
        " ooo "
        "     ";

    life = life_begin(input,5,5);
}

void tearDown(void)
{
    life_end(life);
    life = NULL;
}

void test_life_begin(void)
{
    // TEST_IGNORE();
    point_t expected[6] = {
        {1, 1},
        {2, 1},
        {3, 1},
        {1, 3},
        {2, 3},
        {3, 3},
    };
    linked_list_t actual = life_get_cells(life);

    uint32_t count;
    linked_list_get_count(&actual, &count);
    int len = sizeof(expected)/sizeof(point_t);
    TEST_ASSERT_EQUAL_INT(len, count);

    for (int i; i < len; i++)
    {
        enum result_e ret = linked_list_find_node(&actual,
                                                point_cmp,
                                                &expected[i],
                                                &dummy_node);
        char msg[60];
        sprintf(msg, "expected[%d]: (%d,%d) not found", i, expected[i].x, expected[i].y);
        TEST_ASSERT_MESSAGE(SUCCESS == ret, msg);
    }
}

void test_life_count_neighbor(void)
{
    // TEST_IGNORE();
    linked_list_t cells = life_get_cells(life);

    int actual = life_count_neighbor(2, 2, &cells);
    TEST_ASSERT_EQUAL_INT(6, actual);

    actual = life_count_neighbor(4, 4, &cells);
    TEST_ASSERT_EQUAL_INT(1, actual);

    actual = life_count_neighbor(2, 1, &cells);
    TEST_ASSERT_EQUAL_INT(2, actual);
}

void test_life_update()
{
    // TEST_IGNORE();
    point_t expected[] = {
        {2, 0},
        {2, 1},
        {2, 3},
        {2, 4},
    };

    life_update(life);

    linked_list_t actual = life_get_cells(life);

    uint32_t count;
    linked_list_get_count(&actual, &count);
    int len = sizeof(expected)/sizeof(point_t);
    TEST_ASSERT_EQUAL_INT(len, count);

    for (int i; i < len; i++)
    {
        enum result_e ret = linked_list_find_node(&actual,
                                                point_cmp,
                                                &expected[i],
                                                &dummy_node);
        char msg[60];
        sprintf(msg, "expected[%d]: (%d,%d) not found", i, expected[i].x, expected[i].y);
        TEST_ASSERT_MESSAGE(SUCCESS == ret, msg);
    }
}

/*
void test_life_to_array()
{
    char input[] =
        "     "
        " ooo "
        "     "
        " ooo "
        "     ";
    char expected[] =
        "  o  "
        "  o  "
        "     "
        "  o  "
        "  o  ";
    char actual[5*5];
}
*/

static bool point_cmp(linked_list_node_t *node_to_compare, void *user_data)
{
    point_t p1 = *(point_t *)user_data;
    point_t p2 = *(point_t *)node_to_compare->data;
    return point_is_equal(p1, p2);
}
