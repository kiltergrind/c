#ifndef __ARG_PARSE_H__
#define __ARG_PARSE_H__

    // Libs
    // ========================================================================
    #include <stdio.h>


    // Types
    // ========================================================================
    typedef int BASEPATH_RESULT;

    #define BASEPATH_OK 0
    #define BASEPATH_UNDEFINED 1


    // Functions
    // ========================================================================
    
    // extract base file path from given executable arguments
    char*** read_path_from_argv(int argc, char* **argv);
    BASEPATH_RESULT basepath_truncate(char* basePath);


#endif // __ARG_PARSE_H__