#include <stdlib.h>

#include "meson_error_codes.h"
#include "pluginator.h"

int main(void) {
    Plugin_t plugin = plugin_load(NULL, true);
    // don't check plugin.loaded intentionally and call a the dispatch function
    // instead, if it errors, then the test is cooked

    if (plugin_dispatch_function(&plugin, "A_VERY_REAL_FUNCTION"))
        return MESON_FAIL;

    // also if unloading fails, the test is also cooked
    plugin_unload(&plugin);
    return MESON_OK;
}
