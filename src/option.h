#ifndef OPTION_H
#define OPTION_H

#include <stdbool.h>

/**
 * Type contained in the option. You can use #define OPT_OPT_TYPE <type> before
 * including option.h in your source code to change it
 */
// FIXME: Make it fake generic instead
#ifndef OPT_TYPE
    #define OPT_TYPE void*
#endif // OPT_OPT_TYPE

/**
 * `Some` struct. It contains the held value
 */
struct opt_some {
    void *value;
};

/**
 * `None` struct
 */
struct opt_none {};

/**
 * Basic option struct, similar to Maybe in Haskell or Option in Rust
 */
struct option {
    // What is contained in the Union
    enum opt_type {
        NONE = 0,
        SOME,
    } type;

    // The contained (or not) value
    union {
        struct opt_some some;
        struct opt_none none;
    } value;
};

/**
 * Create a new `Some` option and return it
 */
struct option *opt_some(OPT_TYPE value);

/**
 * Create a new `None` option and return it
 */
struct option *opt_none();

/**
 * Release the memory associated with an option. Does NOT release the memory of the
 * contained value
 */
void opt_destroy(struct option *opt);

/**
 * Does the option contain something
 */
bool opt_is_some(struct option *opt);

/**
 * Does the option contain nothing
 */
bool opt_is_none(struct option *opt);

/**
 * Returns the value contained in the option. If the option is `None`, exits the program
 */
OPT_TYPE opt_get(struct option *opt);

#endif // OPTION_H
