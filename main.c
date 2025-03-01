#include <stdio.h>
#include <stdlib.h>

#include "pluginator.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        const char *program_name; // very overcomplicated cuz idk
        if (argc < 1)
            program_name = "pluginator";
        else
            program_name = argv[0];
        printf("Usage: %s path-to-plugin\n", program_name);
        return EXIT_SUCCESS;
    }

    const char *plugin_path = argv[1];

    printf("loading plugin from: %s\n", plugin_path);
    Plugin_t plugin = plugin_load(plugin_path, true);

    printf("unloading plugin: %s\n", plugin_path);
    plugin_unload(&plugin);

    return EXIT_SUCCESS;
}
