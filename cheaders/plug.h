#ifndef PLUG_H_
#define PLUG_H_

#include <dlfcn.h>
#include <stdint.h> // for intptr_t
#include <stdbool.h>

#define PLUGS_LIST \
    PLUG(plug_update, void, void) \
    PLUG(plug_init, void, void) \
    PLUG(plug_pre_load, void*, void) \
    PLUG(plug_post_load, void, void*)

#define PLUG(name, ret, ...) typedef ret (name##_t)(__VA_ARGS__);
PLUGS_LIST
#undef PLUG
#endif // PLUG_H_

#ifdef PLUG_IMPLEMENTATION

const char *libplug_file_name = "./libplug.so";
void *libplug = NULL;

#ifdef HOT_RELOADABLE
#define PLUG(name, ret, ...) \
    union { \
        void *obj; \
        name##_t *func; \
    } name##_union; \
    name##_t *name = NULL;
PLUGS_LIST
#undef PLUG

bool reload_libplug(void) {
    if (libplug != NULL) {
        dlclose(libplug);
    }

    libplug = dlopen(libplug_file_name, RTLD_LAZY);
    if (libplug == NULL) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return false;
    }

    #define PLUG(name, ret, ...) \
        name##_union.obj = dlsym(libplug, #name); \
        if (name##_union.func == NULL) { \
            fprintf(stderr, "Error loading %s function: %s\n", #name, dlerror()); \
            return false; \
        } \
        name = *name##_union.func;

    PLUGS_LIST
    #undef PLUG

    return true;
}

#else
#define PLUG(name, ret, ...) name##_t name;
#define reload_libplug() true
PLUGS_LIST
#undef PLUG

#endif // HOT_RELOADABLE
#endif // PLUG_IMPLEMENTATION
