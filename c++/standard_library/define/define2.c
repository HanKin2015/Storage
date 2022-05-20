#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#define DEFINE_PROP_UNSIGNED(_name, _state, _field, _defval, _prop, _type) { \
    .name      = (_name),                                           \
    .set_default = true,                                            \
    .defval.u  = (_type)_defval,                                    \
}

#define DEFINE_PROP_UINT32(_n, _s, _f, _d)                      \
    DEFINE_PROP_UNSIGNED(_n, _s, _f, _d, qdev_prop_uint32, uint32_t)

struct Property {
    const char   *name;
    bool         set_default;
    union {
        int64_t i;
        uint64_t u;
    } defval;
};

int XHCIState = 1;
int numports_3 = 2;

static struct Property xhci_properties[] = {
    DEFINE_PROP_UINT32("p3", XHCIState, numports_3, 4),
};

int main()
{
    return 0;
}
