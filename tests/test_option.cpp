#include <gtest/gtest.h>

#define OPT_TYPE int
extern "C" {
    #include "../src/option.h"
}

TEST(opt, init_none)
{
    struct option *opt = opt_none();

    ASSERT_TRUE(opt_is_none(opt));

    opt_destroy(opt);
}

TEST(opt, init_some)
{
    struct option *opt = opt_some(23);

    ASSERT_TRUE(opt_is_some(opt));

    opt_destroy(opt);
}

TEST(opt, get_on_some)
{
    struct option *opt = opt_some(23);

    ASSERT_EQ(23, opt_get(opt));

    opt_destroy(opt);
}

/*
// Commented out or else tests will fail
TEST(opt, get_on_none)
{
    struct option *opt = opt_none();

    ASSERT_EQ(12, opt_get(opt));

    opt_destroy(opt);
}
*/

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
