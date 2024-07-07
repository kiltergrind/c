#include <stdio.h>
#include <stdlib.h>

#include "arg_parse.h"
#include "inotifier.h"



int main (int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "--\nUSAGE: %s <PATH_1> <PATH_2> ..\n--\n", argv[0]);
        exit(EXT_ERR_TOO_FEW_ARGUMENTS);
    }

    // File path list to monitor changes for
    // starting from second argument (1st is the executable name)
    char **pathList = (char**) (&argv[1]);
    pathList = *read_path_from_argv(argc - 1, &pathList);

    // configure monitoring and return a new FSWatch identity
    setup_inotify(argc-1, &pathList);
    pthread_t handle = start_monitoring();

    pthread_join(handle, NULL);
}

