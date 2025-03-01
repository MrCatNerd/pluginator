#include <stdlib.h>

#include "meson_error_codes.h"
#include "pluginator.h"

int main(void) {
    int status = MESON_OK;
    Plugin_t plugin_null = plugin_load(NULL, true);
    if (plugin_null.loaded) {
        plugin_unload(&plugin_null);
        status = MESON_FAIL;
    }

    Plugin_t plugin_invalid_path = plugin_load("./averyrealplugin.so", // yes
                                               true);
    if (plugin_invalid_path.loaded) {
        plugin_unload(&plugin_invalid_path);
        status = MESON_FAIL;
    }

    return status;
}
