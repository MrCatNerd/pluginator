#include "config.h"
#include "meson_error_codes.h"
#include "pluginator.h"

int main(void) {
    Plugin_t plugin = plugin_load(PLUGIN_PATH, true);
    if (!plugin.loaded)
        return MESON_FAIL;

    plugin_unload(&plugin);

    return MESON_OK;
}
