#pragma once

#include <link.h>
#include <stdbool.h>

#include "hashmap.h"

typedef enum Pluginator_DL_flags {
    PLUGINATOR_DL_NOFLAGS = 0,
    PLUGINATOR_DL_GLOBAL = RTLD_GLOBAL,
    PLUGINATOR_DL_LAZY = RTLD_LAZY,
    PLUGINATOR_DL_NOW = RTLD_NOW,
} Pluginator_DL_flags_e;
#define DL_DEFAULT_FLAGS (int)(PLUGINATOR_DL_GLOBAL | PLUGINATOR_DL_LAZY)

typedef struct Plugin {
        const char *path;
        int dl_flags;

        void *dl_handle;
        struct link_map *link_map;
        bool loaded;

        struct hashmap *symbol_cache;

} Plugin_t;

/// loads a plugin
Plugin_t plugin_load(const char *path, int dl_flags);
/// dispatches a function from the plugin
void *plugin_dispatch_function(Plugin_t *plugin, const char *name);
/// frees and re-loads the plugin
void plugin_reload(Plugin_t *plugin);
/// unloads and frees the plugin
void plugin_unload(Plugin_t *plugin);
