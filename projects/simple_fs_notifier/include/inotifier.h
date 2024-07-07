#ifndef __INOTIFIER_H__
#define __INOTIFIER_H__

    // LIBS
    // ========================================================================
    #include <pthread.h>
    #include <stdio.h>
    #include "fswatch/libfswatch.h"


    // Types
    // ========================================================================
    typedef int INOTIFY_RESULT;
    typedef pthread_t monitor_session_thread_t;


    // Constants
    // ========================================================================

    #define INOTIFY_SUCCESS 0

    // not enough arguments provided to the executable
    #define EXT_ERR_TOO_FEW_ARGUMENTS 1

    // Cannot determine the base file path for FSWAtch to monitor
    #define EXT_ERR_BASEPATH_UNDEFINED 73

    // Could not initialize the LibFswatch library
    #define EXT_ERR_FSW_INIT_ERROR 72
    #define EXT_ERR_FSW_INIT_SESSION_ERR 73
    #define EXT_ERR_FSW_SET_FILTERS 74


    // Globals
    // ========================================================================
    static pthread_mutex_t glob_fsw_lock = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t globv_monitoring_ready_cond = PTHREAD_COND_INITIALIZER;
    FSW_HANDLE glob_monitor_session_handle;
    static FILE * monitor_log_file_p;


    // Functions
    // ========================================================================
    // perform a common configuration for the LibFSWatch library
    INOTIFY_RESULT setup_inotify
    (
        int files_count,
        char* **watchover_files
    );
    
    void monitoring_callback
    (
        fsw_cevent const *const events,
        const unsigned int event_num,
        void * data
    );

    monitor_session_thread_t start_monitoring();
    void * fsw_session_starter();
    void fsw_session_graceful_shutdown(int sig);
    void grace_exit(INOTIFY_RESULT res);



#endif // __INOTIFIER_H__