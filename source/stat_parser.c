#include <stdlib.h>

#include "stat_parser.h"

#define BUFF_SIZE 20
#define TMP_SIZE 4

bool scan_proc_stat(size_t *cpu_num) {
    FILE *proc_stat;
    if ((proc_stat = fopen("/proc/stat", "r")) == NULL) {
        return false;
    }
    rewind(proc_stat);

    *cpu_num = 0;
    char buff[25] = "";
    char tmp[4] = "";
    tmp[3] = '\0';
    
    while ((feof(proc_stat)) != -1) {
        if (fscanf(proc_stat, "%s", buff) != 1) {
        return false;
        }
        if (strcmp(strncpy(tmp, buff, 3), "cpu") == 0) {
            if (fscanf(proc_stat, "%*[^\n]\n") != 0) {
                return false;
            }
            (*cpu_num)++;
        }
        else {
            fclose(proc_stat);
            return true;
        }
    }

    fclose(proc_stat);
    return true;
}

bool read_proc_stat(stat_struct_t *stat) {
    char buff[BUFF_SIZE];
    char tmp[TMP_SIZE];
    tmp[TMP_SIZE - 1] = '\0';
    FILE *proc_stat = NULL;

    if ((proc_stat = fopen("/proc/stat", "r")) == NULL) {
        return false;
    }

    size_t i = 0;
    rewind(proc_stat);

    while ((feof(proc_stat)) != -1) {
        if (fscanf(proc_stat, "%s", buff) != 1){
            return false;
        }

        if (strcmp(strncpy(tmp, buff, 3), "cpu") == 0) {
            if (fscanf(proc_stat, "%llu %llu %llu %llu %llu %llu %llu %llu %llu %llu%*[^\n]\n", &stat->cpu[i].user, &stat->cpu[i].nice, &stat->cpu[i].system, &stat->cpu[i].idle, &stat->cpu[i].io_wait, &stat->cpu[i].irq, &stat->cpu[i].soft_irq, &stat->cpu[i].steal, &stat->cpu[i].guest, &stat->cpu[i].guest_nice) != 10) {
                return false;
            }
            i++;
        }
        else {
            fclose(proc_stat);
            return true;
        }
    }

    fclose(proc_stat);
    
    return true;
}

void print_proc_stat(stat_struct_t *stat) {
    for (size_t i = 0; i < stat->cpu_num; ++i) {
        printf("CPU%lu: %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu \n", i, stat->cpu[i].user, stat->cpu[i].nice, stat->cpu[i].system, stat->cpu[i].idle, stat->cpu[i].io_wait, stat->cpu[i].irq, stat->cpu[i].soft_irq, stat->cpu[i].steal, stat->cpu[i].guest, stat->cpu[i].guest_nice);
    }
}