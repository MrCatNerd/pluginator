#include <stdlib.h>

#include "meson_error_codes.h"
#include "pluginator.h"

int main(void) {
    Plugin_t plugin = plugin_load(NULL, true);
    if (!plugin.loaded) {
        return MESON_FAIL;
    }

    if (plugin_dispatch_function(&plugin, "A_VERY_REAL_FUNCTION"))
        return MESON_FAIL;

    plugin_unload(&plugin);
    return MESON_OK;
}
