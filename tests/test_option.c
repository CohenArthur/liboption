#include <assert.h>
#include "../src/option.h"

#define TEST(Name, Subname) void test_##Name##_##Subname()
#define RUN_TEST(Name, Subname) test_##Name##_##Subname()

#define ASSERT_TRUE(Exp) assert(Exp)
#define ASSERT_EQ(Lhs, Rhs) assert(Lhs == Rhs)

OPT_DECLARE(option_not_int, int);
OPT_DEFINE(option_not_int, int);

TEST(opt, init_none)
{
    struct option_not_int opt = option_not_int_none();

    ASSERT_TRUE(option_not_int_is_none(&opt));
}

TEST(opt, init_some)
{
    struct option_not_int opt = option_not_int_some(23);

    ASSERT_TRUE(option_not_int_is_some(&opt));
}

TEST(opt, get_on_some)
{
    struct option_not_int opt = option_not_int_some(23);

    ASSERT_EQ(23, option_not_int_get(&opt));
}

// Commented out or else tests will fail since this exits
TEST(opt, get_on_none)
{
    struct option_not_int opt = option_not_int_none();

    ASSERT_EQ(12, option_not_int_get(&opt));
}

int main(void)
{
    RUN_TEST(opt, init_none);
    RUN_TEST(opt, init_some);
    RUN_TEST(opt, get_on_some);
    // RUN_TEST(opt, get_on_none);
}
