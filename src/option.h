#pragma once

#include <err.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * `None` struct. In the C standard, a struct cannot be empty. Therefore, this
 * None struct contains only one bit.
 */
struct opt_none {
    char phantom_field : 1;
};

/**
 * The different types of possible options
 */
enum opt_type {
    NONE = 0,
    SOME,
};

/**
 * Declare an option of the given type. The associated functions will be named
 * opt_<name>_get(), opt_<name>_is_none(), etc.
 * The resulting struct is named struct option_<name>
 */
#define OPT_DECLARE(Name, Type)                                            \
    struct opt_##Name##_some {                                             \
        Type value;                                                        \
    };                                                                     \
                                                                           \
    /**                                                                    \
     * Basic option struct, similar to Maybe in Haskell or Option in Rust  \
     */                                                                    \
    struct option_##Name {                                                 \
        /* What is contained in the Union */                               \
        enum opt_type type;                                                \
                                                                           \
        /* The contained (or not) value */                                 \
        union {                                                            \
            struct opt_##Name##_some some;                                 \
            struct opt_none none;                                          \
        } value;                                                           \
    };                                                                     \
                                                                           \
    /**                                                                    \
     * Create a new `Some` option and return it                            \
     */                                                                    \
    struct option_##Name opt_##Name##_some(Type value);                    \
                                                                           \
    /**                                                                    \
     * Create a new `None` option and return it                            \
     */                                                                    \
    struct option_##Name opt_##Name##_none();                              \
                                                                           \
    /**                                                                    \
     * Does the option contain something                                   \
     */                                                                    \
    bool opt_##Name##_is_some(struct option_##Name *opt);                  \
                                                                           \
    /**                                                                    \
     * Does the option contain nothing                                     \
     */                                                                    \
    bool opt_##Name##_is_none(struct option_##Name *opt);                  \
                                                                           \
    /**                                                                    \
     * Returns the value contained in the option. If the option is `None`, \
     * exits the program                                                   \
     */                                                                    \
    Type opt_##Name##_get(struct option_##Name *opt)

#define OPT_DEFINE(Name, Type)                                               \
    struct option_##Name opt_##Name##_some(Type value) {                     \
        struct option_##Name opt = {                                         \
            .type = SOME,                                                    \
            .value.some.value = value,                                       \
        };                                                                   \
                                                                             \
        return opt;                                                          \
    }                                                                        \
                                                                             \
    struct option_##Name opt_##Name##_none() {                               \
        struct option_##Name opt = {                                         \
            .type = NONE,                                                    \
            .value.none.phantom_field = 0,                                   \
        };                                                                   \
                                                                             \
        return opt;                                                          \
    }                                                                        \
                                                                             \
    bool opt_##Name##_is_some(struct option_##Name *opt) {                   \
        return opt->type == SOME;                                            \
    }                                                                        \
                                                                             \
    bool opt_##Name##_is_none(struct option_##Name *opt) {                   \
        return opt->type == NONE;                                            \
    }                                                                        \
                                                                             \
    Type opt_##Name##_get(struct option_##Name *opt) {                       \
        if (opt->type == NONE)                                               \
            errx(1, "%s", "trying to access value on `None` option_" #Name); \
                                                                             \
        return opt->value.some.value;                                        \
    }
