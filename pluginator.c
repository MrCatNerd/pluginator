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

// -------- CACHE STUFF + HASHMAP -------- //
// TODO: max cache size with most recently used items priority thingy
typedef struct CachedSymbol {
        const char *name;
        void *fp;
} CachedSymbol_t;

int hm_compare(const void *a, const void *b, void *data) {
    const CachedSymbol_t *cda = a;
    const CachedSymbol_t *cdb = b;
    // nah i aint comparing the pointer
    return strcmp(cda->name, cdb->name);
}

uint64_t hm_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    const CachedSymbol_t *cd = item;

    return hashmap_sip(cd->name, strlen(cd->name), seed0, seed1);
}

// -------- ACTUAL CODE -------- //
Plugin_t plugin_load(const char *path, bool lazy) {
    Plugin_t plugin = {.path = path,
                       .lazy = lazy,
                       .symbol_cache = NULL,
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
    if (plugin->dl_handle)
        fp = dlsym(plugin->dl_handle, name);
    print_dl_error();
    if (fp)
        hashmap_set(plugin->symbol_cache,
                    &(CachedSymbol_t){.name = name, .fp = fp});
    return fp;
}

void plugin_reload(Plugin_t *plugin, const char *path) {
    plugin_unload(plugin);
    *plugin = plugin_load(path, plugin->lazy);
}

void plugin_unload(Plugin_t *plugin) {
    // free the cache
    hashmap_free(plugin->symbol_cache);

    // close the handle
    if (plugin->dl_handle)
        dlclose(plugin->dl_handle);

    // reset some vars
    plugin->dl_handle = NULL;
    plugin->symbol_cache = NULL;
    plugin->loaded = false;
}
