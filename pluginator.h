#pragma once

#include <link.h>
#include <stdbool.h>

#include "hashmap.h"

typedef struct Plugin {
        const char *path;
        bool lazy;
        bool loaded;
        struct hashmap *symbol_cache;

        void *dl_handle;
        struct link_map *link_map;
} Plugin_t;

Plugin_t plugin_load(const char *path, bool lazy);
void *plugin_dispatch_function(Plugin_t *plugin, const char *name);
void plugin_reload(Plugin_t *plugin, const char *path);
void plugin_unload(Plugin_t *plugin);
