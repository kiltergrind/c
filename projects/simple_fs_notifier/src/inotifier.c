#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>


// Filesystem monitor notifications
#include "fswatch/libfswatch.h"
#include "inotifier.h"


INOTIFY_RESULT setup_inotify
(
    int files_count,
    char* **watchover_files
)
{
    FSW_HANDLE handle;
    FSW_STATUS lastStatus;
    char* current_file;
    int flags[15] = {Created, Updated, Removed, Renamed, MovedTo};

    monitor_log_file_p = fopen("monitor.log", "w");

    if (fsw_init_library() != FSW_OK) {
        fprintf(monitor_log_file_p,
                "\nUNABLE to initialize the FSWATCH library"
                "\n\tERROR STATUS: %d", fsw_last_error());
        grace_exit(EXT_ERR_FSW_INIT_ERROR);
    }

    handle = fsw_init_session(system_default_monitor_type);
    lastStatus = fsw_last_error();

    if (lastStatus != FSW_OK) {
        fprintf(monitor_log_file_p,
                "\nUNABLE to initialize the FSWATCH session"
                "\nERROR STATUS: %d", lastStatus);
        grace_exit(EXT_ERR_FSW_INIT_SESSION_ERR);
    }

    // Add files to watch over changes
    //
    for (int i = 0; i < files_count; ++i)
    {
        current_file = (*watchover_files)[i];
        if (fsw_add_path(handle, current_file) != FSW_OK) {
            fprintf(monitor_log_file_p,
                    "\nCould not add file to monitor: %s", current_file);
            continue;
        }
        fprintf(monitor_log_file_p, "\nAdded monitor file: %s", current_file);
    }

    lastStatus = fsw_add_filter(handle, (fsw_cmonitor_filter) {
        .text = "Include Filter",
        .type = filter_include,
        .case_sensitive = false,
        .extended = true,
    });

    for (unsigned i = 0; i < 15; ++i)
        lastStatus = fsw_add_event_type_filter(
            handle, (struct fsw_event_type_filter) { .flag = flags[i] });

    fsw_set_callback(handle, &monitoring_callback, (void*) NULL);
    signal(SIGINT, fsw_session_graceful_shutdown);

    if (lastStatus != FSW_OK) {
        fprintf(monitor_log_file_p,
                "Failed to set filters for current session, exiting...");
        grace_exit(EXT_ERR_FSW_SET_FILTERS);
    }

    glob_monitor_session_handle = handle;

    return INOTIFY_SUCCESS;
}


void
monitoring_callback(
    fsw_cevent const *const events,
    const unsigned int event_num,
    void *data
)
{
    printf("%u", event_num);
    char action[512];
    int pos = -1;

    while (++pos < events->flags_num) switch (events->flags[pos])
    {
        case Created: snprintf(action, 512, "CREATED");         break;
        case Removed: snprintf(action, 512, "REMOVED");         break;
        case Renamed: snprintf(action, 512, "RENAMED");         break;
        case Updated: snprintf(action, 512, "UPDATED/CHANGED"); break;
        default:      snprintf(action, 512, "UNKNOWN");

    }
    fprintf(monitor_log_file_p,
        "\n-------------------"
        "\n@@ | FILE   -> (%s)"
        "\n@@ | ACTION -> [%s]"
        "\n-------------------",
            // asctime(events->evt_time),
        events->path,
        action);
    fflush(monitor_log_file_p);
}


monitor_session_thread_t start_monitoring()
{
    pthread_t backround_handler_thread_id;

    fprintf(monitor_log_file_p, "\nStarting FSW session...");

    pthread_create(
        &backround_handler_thread_id, NULL, &fsw_session_starter, NULL);
    while (!fsw_is_running(glob_monitor_session_handle)) sleep(1);

    fprintf(monitor_log_file_p, "\nSession successfully started!");
    fflush(monitor_log_file_p);

    return backround_handler_thread_id;
}


void * fsw_session_starter()
{
    fsw_start_monitor(glob_monitor_session_handle);
    return NULL;
}


void fsw_session_graceful_shutdown(int _sig)
{
    unsigned short attempts = 3;
    fprintf(monitor_log_file_p, "\nStopping session...");

    fsw_stop_monitor(glob_monitor_session_handle);
    while (fsw_is_running(glob_monitor_session_handle) && --attempts) sleep(1);

    fprintf(monitor_log_file_p, "\nSession halted!");
    fflush(monitor_log_file_p);
}


void grace_exit(INOTIFY_RESULT code)
{
    fsw_session_graceful_shutdown(0);
    fclose(monitor_log_file_p);
    exit(code);
}
