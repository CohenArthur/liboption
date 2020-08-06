#include <stdlib.h>
#include <err.h>

#include "option.h"

static struct option *opt_new()
{
    // Careful: This is uninitialized memory
    return malloc(sizeof(struct option));
}

struct option* opt_some(OPT_TYPE value)
{
    struct option *opt = opt_new();

    opt->type = SOME;
    opt->value.some.value = value;

    return opt;
}

struct option* opt_none()
{
    struct option *opt = opt_new();

    opt->type = NONE;

    return opt;
}

void opt_destroy(struct option *opt)
{
    free(opt);
}

bool opt_is_some(struct option *opt)
{
    return opt->type == SOME;
}

bool opt_is_none(struct option *opt)
{
    return opt->type == NONE;
}

OPT_TYPE opt_get(struct option *opt)
{
    if (opt->type == NONE)
        err(1, "%s", "trying to access value on None option");

    return opt->value.some.value;
}
