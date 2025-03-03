#include <stdio.h>
#include <omp.h>
#include <sys/sysctl.h>

int get_logical_cpu()
{
    int cpu;
    size_t size = sizeof(cpu);
    // 获取当前线程绑定的逻辑 CPU 编号
    if (sysctlbyname("machdep.cpu.logical_cpu", &cpu, &size, NULL, 0) == 0)
    {
        return cpu;
    }
    return -1;
}

int main()
{
#pragma omp parallel num_threads(10)
    {
        int thread_id = omp_get_thread_num();
        int cpu = get_logical_cpu();
        printf("Thread %d is running on Logical CPU %d\n", thread_id, cpu);
    }
    return 0;
}