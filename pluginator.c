#include <stdio.h>
#include <link.h>
#include <dlfcn.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pluginator.h"

static void print_dl_error() {
    const char *errstr = dlerror();
    if (errstr != NULL)
        fprintf(stderr, "A dynamic linking error occurred: (%s)\n", errstr);
}

Plugin_t plugin_load(const char *path, bool lazy) {
    Plugin_t plugin = {.path = path,
                       .lazy = lazy,
                       .dl_handle = NULL,
                       .link_map = NULL,
                       .loaded = false};
    if (!path)
        return plugin;

    int flags = 0;
    if (lazy)
        flags |= RTLD_LAZY;
    else
        flags |= RTLD_NOW;
    flags |= RTLD_GLOBAL;

    plugin.dl_handle = dlopen(path, flags);
    if (plugin.dl_handle)
        plugin.loaded = true;
    print_dl_error();

    return plugin;
}

void *plugin_dispatch_function(Plugin_t *plugin, const char *name) {
    void *fp = NULL;
    if (plugin->dl_handle)
        fp = dlsym(plugin->dl_handle, name);
    print_dl_error();
    return fp;
}

void plugin_reload(Plugin_t *plugin, const char *path) {
    plugin_unload(plugin);
    *plugin = plugin_load(path, plugin->lazy);
}

void plugin_unload(Plugin_t *plugin) {
    if (plugin->dl_handle)
        dlclose(plugin->dl_handle);
    plugin->dl_handle = NULL;
    plugin->loaded = false;
}
