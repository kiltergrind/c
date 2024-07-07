#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arg_parse.h"



/* Function: read_path_from_argv
 * ----
 * Description:
 * ----
 * | This function takes references to array of arguments of the executable,
 * | splits them by `/` path symbol, and finds a base path.
 * | 
 * | After that writes the found path
 * | to the location passed as pointer to character list (char*) as a third parameter
 * ----
 * Parameters:
 * ----
 * @param argc {int} - count of arguments contained inside argv
 * @param argv {char* **} - pointer to a sequence of strings(char*) passed to program
 * @param resulting_path {char* *} - pointer to a buffer of characters that stores resulting base path
 * ----
 * Returns:
 * ----
 * {void}
 * 
 */
char*** read_path_from_argv(int argc, char* **argv)
{
    char **array = (char**) malloc(sizeof(char*) * argc);
    char *** pathList = &array;

    // track last status for base path extracting operation
    BASEPATH_RESULT last_result;


    // Allocate memory for path list strings
    //
    for (int i = 0; i < argc; ++i) {
        (*pathList)[i] =
            (char*) malloc(sizeof(char) * strlen((*argv)[i]) + 1);
        strcpy((*pathList)[i], (*argv)[i]);
    }

    // Extract base path for each string in argv and store them in pathList
    //

    for (int i = 0; i < argc; ++i) {
        last_result = basepath_truncate((*pathList)[i]);
        if (last_result != BASEPATH_OK) {
            fprintf(stdout,
                    "Base Path is undefined for: \"%s\"", (*argv)[i]);
            continue;
        }
        fprintf(stdout, "\nFound base path for: \"%s\" -> \"%s\"",
                (*argv)[i],
                (*pathList)[i]);
    }

    fflush(stdout);

    return pathList;
}


BASEPATH_RESULT basepath_truncate(char* basePath)
{
    char* token = strtok(basePath, "/");

    while (token != NULL) {
        basePath = token;
        token = strtok(NULL, "/");
    }

    if (basePath == NULL) {
        fprintf(stderr, "COULD NOT DETERMINE Base Path for %s", basePath);
        return BASEPATH_UNDEFINED;
    }

    return BASEPATH_OK;
}