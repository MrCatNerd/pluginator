#include <stdio.h>
#include <link.h>
#include <dlfcn.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "pluginator.h"
#include "hashmap.h"

// -------- ERROR STUFF -------- //
static void print_dl_error() {
    const char *errstr = dlerror();
    if (errstr != NULL)
        fprintf(stderr, "A dynamic linking error occurred: (%s)\n", errstr);
}

// -------- CACHE HASHMAP STUFF -------- //
// TODO: max cache size with most recently used items priority thingy
typedef struct CachedSymbol {
        const char *name;
        void *fp;
} CachedSymbol_t;

int hm_compare(const void *a, const void *b, void *data) {
    (void)(data);
    const CachedSymbol_t *csa = a;
    const CachedSymbol_t *csb = b;
    return strcmp(csa->name, csb->name);
}

uint64_t hm_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    const CachedSymbol_t *cd = item;

    return hashmap_sip(cd->name, strlen(cd->name), seed0, seed1);
}

// -------- ACTUAL CODE -------- //
Plugin_t plugin_load(const char *path, int dl_flags) {
    Plugin_t plugin = {
        .path = path,
        .dl_flags = PLUGINATOR_DL_NOFLAGS,
        .dl_handle = NULL,
        .link_map = NULL,
        .loaded = false,
        .symbol_cache = NULL,
    };

    if (!path)
        return plugin;

    plugin.dl_handle = dlopen(path, dl_flags);
    print_dl_error();
    if (plugin.dl_handle)
        plugin.loaded = true;

    // create cache
    plugin.symbol_cache = hashmap_new(sizeof(CachedSymbol_t), 0, 0, 0, hm_hash,
                                      hm_compare, NULL, NULL);

    return plugin;
}

void *plugin_dispatch_function(Plugin_t *plugin, const char *name) {
    // try getting the symbol from the cache
    void *fp = (void *)hashmap_get(plugin->symbol_cache,
                                   &(CachedSymbol_t){.name = name});
    if (fp)
        return fp;

    // if it aint in the cache, than get the symbol from dlsym and cache it
    if (plugin->dl_handle) {
        fp = dlsym(plugin->dl_handle, name);
        print_dl_error();
    }
    if (fp)
        hashmap_set(plugin->symbol_cache,
                    &(CachedSymbol_t){.name = name, .fp = fp});

    return fp;
}

void plugin_unload(Plugin_t *plugin) {
    // close the handle
    if (plugin->dl_handle) {
        dlclose(plugin->dl_handle);
        plugin->dl_handle = NULL;
    }

    // free the cache
    if (plugin->symbol_cache) {
        hashmap_free(plugin->symbol_cache);
        plugin->symbol_cache = NULL;
    }

    // set loaded to false
    plugin->loaded = false;
}

void plugin_reload(Plugin_t *plugin) {
    plugin_unload(plugin);
    *plugin = plugin_load(plugin->path, plugin->dl_flags);
}
