#include <assert.h>

#include "config.h"
#include "meson_error_codes.h"
#include "pluginator.h"

int main(void) {
    Plugin_t plugin = plugin_load(PLUGIN_PATH, true);
    if (!plugin.loaded)
        return MESON_FAIL;

    int (*func)() = plugin_dispatch_function(&plugin, "meow");
    if (!func)
        return MESON_FAIL;

    assert((*func)() == -1234891);

    plugin_unload(&plugin);

    return MESON_OK;
}
