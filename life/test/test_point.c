#include "unity.h"

#include "point.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_point_is_equal(void)
{
    point_t a = {1,2};
    point_t b = {0,0}, c = {1,1}, d = {1,2};

    TEST_ASSERT_FALSE(point_is_equal(a,b));
    TEST_ASSERT_FALSE(point_is_equal(a,c));
    TEST_ASSERT_TRUE(point_is_equal(a,d));
}
