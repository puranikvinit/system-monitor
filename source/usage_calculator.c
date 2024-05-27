#include "usage_calculator.h"

float calculate_cpu_use_per_c(cpu_struct_t prev_cpu, cpu_struct_t curr_cpu) {
    unsigned long long int prev_idle = prev_cpu.idle + prev_cpu.io_wait;
    unsigned long long int curr_idle = curr_cpu.idle + curr_cpu.io_wait;

    unsigned long long int prev_non_idle = prev_cpu.user + prev_cpu.nice + prev_cpu.system + prev_cpu.irq + prev_cpu.soft_irq + prev_cpu.steal;
    unsigned long long int curr_non_idle = curr_cpu.user + curr_cpu.nice + curr_cpu.system + curr_cpu.irq + curr_cpu.soft_irq + curr_cpu.steal;

    unsigned long long int prev_total = prev_idle + prev_non_idle;
    unsigned long long int curr_total = curr_idle + curr_non_idle;

    unsigned long long int total_diff = curr_total - prev_total;
    unsigned long long int idle_diff = curr_idle - prev_idle;

    return ((float)total_diff - (float)idle_diff) / (float)total_diff * 100.0f;
}

bool calculate_all_cpus(stat_struct_t *prev_stat, stat_struct_t *curr_stat, size_t cpu_num, float *cpu_per_c) {
    bool exit = true;
    
    if(prev_stat->cpu_num != curr_stat->cpu_num) {
        return false;
    }

    size_t i = 0;
    for(; i < cpu_num; ++i) {
        cpu_per_c[i] = calculate_cpu_use_per_c(prev_stat->cpu[i], curr_stat->cpu[i]);
    }

    return exit;
}
