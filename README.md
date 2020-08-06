# option

"Generic" option Type in C

# Usage

The library is header only. You can simply add the following code to define an option type

* in your header:
```c
#include "option.h"

struct my_struct {
    size_t size;
    size_t capacity;
    char buffer[];
};

OPT_DECLARE(my_struct_opt, struct my_struct);
```

* in your source file:
```
#include "option.h"

OPT_DEFINE(my_struct_opt, struct my_struct);
```

This will declare and define a `struct my_struct_opt` type, as well as the associated
functions. Those are:

|function's name|
|---|
|`<name>_some`|
|`<name>_none`|
|`<name>_get`|
|`<name>_is_some`|
|`<name>_is_none`|

The file `tests/test_option.c` defines three opt types, `option_not_int`, `opt_ull` and
`opt_string`.

# Limitations

The option type adds 8 bytes to your return values but ensures better error handling
and safety.
This library does NOT work in C++. C++ does not support named initialization, on top
of being very dumb when it comes to macros sometimes.
