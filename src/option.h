#pragma once

#include <err.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * `None` struct. In the C standard, a struct cannot be empty. Therefore, this
 * None struct contains only one bit.
 * An empty struct is possible when using a GNU extension.
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
 * The resulting struct is named struct <name>
 */
#define OPT_DECLARE(Name, Type)                                            \
    struct Name##_some {                                             \
        Type value;                                                        \
    };                                                                     \
                                                                           \
    /**                                                                    \
     * Basic option struct, similar to Maybe in Haskell or Option in Rust  \
     */                                                                    \
    struct Name {                                                 \
        /* What is contained in the Union */                               \
        enum opt_type type;                                                \
                                                                           \
        /* The contained (or not) value */                                 \
        union {                                                            \
            struct Name##_some some;                                 \
            struct opt_none none;                                          \
        } value;                                                           \
    };                                                                     \
                                                                           \
    /**                                                                    \
     * Create a new `Some` option and return it                            \
     */                                                                    \
    struct Name Name##_some(Type value);                    \
                                                                           \
    /**                                                                    \
     * Create a new `None` option and return it                            \
     */                                                                    \
    struct Name Name##_none();                              \
                                                                           \
    /**                                                                    \
     * Does the option contain something                                   \
     */                                                                    \
    bool Name##_is_some(struct Name *opt);                  \
                                                                           \
    /**                                                                    \
     * Does the option contain nothing                                     \
     */                                                                    \
    bool Name##_is_none(struct Name *opt);                  \
                                                                           \
    /**                                                                    \
     * Returns the value contained in the option. If the option is `None`, \
     * exits the program                                                   \
     */                                                                    \
    Type Name##_get(struct Name *opt)

#define OPT_DEFINE(Name, Type)                                               \
    struct Name Name##_some(Type value) {                     \
        struct Name opt = {                                         \
            .type = SOME,                                                    \
            .value.some.value = value,                                       \
        };                                                                   \
                                                                             \
        return opt;                                                          \
    }                                                                        \
                                                                             \
    struct Name Name##_none() {                               \
        struct Name opt = {                                         \
            .type = NONE,                                                    \
            .value.none.phantom_field = 0,                                   \
        };                                                                   \
                                                                             \
        return opt;                                                          \
    }                                                                        \
                                                                             \
    bool Name##_is_some(struct Name *opt) {                   \
        return opt->type == SOME;                                            \
    }                                                                        \
                                                                             \
    bool Name##_is_none(struct Name *opt) {                   \
        return opt->type == NONE;                                            \
    }                                                                        \
                                                                             \
    Type Name##_get(struct Name *opt) {                       \
        if (opt->type == NONE)                                               \
            errx(1, "%s", "trying to access value on `None` option_" #Name); \
                                                                             \
        return opt->value.some.value;                                        \
    }
