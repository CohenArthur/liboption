#include <assert.h>
#include <string.h>
#include "../src/option.h"

#define TEST(Name, Subname) void test_##Name##_##Subname()
#define RUN_TEST(Name, Subname) test_##Name##_##Subname()

#define ASSERT_TRUE(Exp) assert(Exp)
#define ASSERT_EQ(Lhs, Rhs) assert(Lhs == Rhs)

OPT_DECLARE(option_not_int, int);
OPT_DEFINE(option_not_int, int)

OPT_DECLARE(opt_ull, unsigned long long);
OPT_DEFINE(opt_ull, unsigned long long)

OPT_DECLARE(opt_string, char *);
OPT_DEFINE(opt_string, char *)

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

TEST(opt_ull, init_none)
{
    struct opt_ull opt = opt_ull_none();

    ASSERT_TRUE(opt_ull_is_none(&opt));
}

TEST(opt_ull, init_some)
{
    struct opt_ull opt = opt_ull_some(23);

    ASSERT_TRUE(opt_ull_is_some(&opt));
}

TEST(opt_ull, get_on_some)
{
    struct opt_ull opt = opt_ull_some(23);

    ASSERT_EQ(23, opt_ull_get(&opt));
}

TEST(opt_string, init_none)
{
    struct opt_string opt = opt_string_none();

    ASSERT_TRUE(opt_string_is_none(&opt));
}

TEST(opt_string, init_some)
{
    struct opt_string opt = opt_string_some("func");

    ASSERT_TRUE(opt_string_is_some(&opt));
}

TEST(opt_string, get_on_some)
{
    struct opt_string opt = opt_string_some("func");

    ASSERT_EQ(strcmp("func", opt_string_get(&opt)), 0);
}

int main(void)
{
    RUN_TEST(opt, init_none);
    RUN_TEST(opt, init_some);
    RUN_TEST(opt, get_on_some);
    // RUN_TEST(opt, get_on_none);
}
