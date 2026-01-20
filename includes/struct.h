/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** struct.h
*/

#ifndef STRUCT_H
    #define STRUCT_H
    #include "time.h"
    #include <sys/types.h>

typedef struct set_s {
    int frames;
    char *username;
    float secondes;
} set_t;

typedef struct p_s {
    int frames;
    int username;
    int secondes;
} p_t;

typedef struct system_s {
    time_t current_time;
    time_t uptime;
    int current_time_secondes;
    int current_time_minutes;
    int current_time_hours;
    int uptime_days;
    int uptime_hours;
    int uptime_minutes;
    int uptime_secondes;

    float loadavg_1;
    float loadavg_5;
    float loadavg_15;

    unsigned long long cpu_user;
    unsigned long long cpu_nice;
    unsigned long long cpu_system;
    unsigned long long cpu_idle;
    unsigned long long cpu_iowait;
    unsigned long long cpu_irq;
    unsigned long long cpu_softirq;
    unsigned long long cpu_steal;
    unsigned long long cpu_guest;
    unsigned long long cpu_guest_nice;

    float cpu_percent_user;
    float cpu_percent_system;
    float cpu_percent_nice;
    float cpu_percent_idle;
    float cpu_percent_iowait;
    float cpu_percent_irq;
    float cpu_percent_softirq;
    float cpu_percent_steal;

    unsigned long mem_total;
    unsigned long mem_free;
    unsigned long mem_available;
    unsigned long mem_buffers;
    unsigned long mem_cached;
    unsigned long mem_used;
    unsigned long mem_buff_cache;

    unsigned long swap_total;
    unsigned long swap_free;
    unsigned long swap_used;
    unsigned long swap_cached;

    unsigned int tasks_total;
    unsigned int tasks_running;
    unsigned int tasks_sleeping;
    unsigned int tasks_stopped;
    unsigned int tasks_zombie;

    unsigned int logged_users;

    int mem_unit_process;
    int mem_unit_system;
} system_t;

typedef struct process_s {
    pid_t pid;
    pid_t ppid;
    uid_t uid;
    gid_t gid;
    char user[32];
    char group[32];

    int priority;
    int nice;

    char state;
    char state_full;

    unsigned long virt_memory;
    unsigned long res_memory;
    unsigned long shared_memory;

    float cpu_percent;
    float mem_percent;

    unsigned long utime;
    unsigned long stime;
    unsigned long cutime;
    unsigned long cstime;
    unsigned long starttime;
    char time_str[32];

    char command[256];
    char command_path[512];

    unsigned int threads;

    int selected;
} process_t;

typedef struct inf_s {

    process_t *processes;
    int process_count;
    int process_capacity;

    char filter_user[32];
    int max_frames;
    int current_frame;
    float refresh_delay;

    int sort_column;
    int sort_reverse;
    int scroll_offset;
    int selected_pid;

    int running;
    int need_refresh;

    int term_width;
    int term_height;

    int show_threads;
    int forest_mode;
    int show_full_cmd;
    int color_mode;

    int mem_unit_process;
    int mem_unit_system;

    unsigned long long old_total;
    unsigned long long old_user;
    unsigned long long old_nice;
    unsigned long long old_system;
    unsigned long long old_idle;
    unsigned long long old_iowait;
    unsigned long long old_irq;
    unsigned long long old_softirq;
    unsigned long long old_steal;
} inf_t;

typedef struct top_s {
    struct p_s *p;
    struct set_s *s;
    struct inf_s *inf;
    struct process_s *pros;
    system_t *sys;
} top_t;

#endif /*STRUCT_H*/
