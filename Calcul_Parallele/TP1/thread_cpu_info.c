#include <stdio.h>
#include <omp.h>
#include <mach/mach.h>
#include <mach/thread_info.h>
#include <mach/thread_act.h>
#include <mach/thread_policy.h>

// 获取当前线程的CPU核心ID
int get_cpu_core_id()
{
    thread_identifier_info_data_t identifier_info;
    mach_msg_type_number_t count = THREAD_IDENTIFIER_INFO_COUNT;

    // 获取当前线程的Mach端口
    mach_port_t thread_port = mach_thread_self();

    // 获取线程标识符信息
    kern_return_t kr = thread_info(thread_port,
                                   THREAD_IDENTIFIER_INFO,
                                   (thread_info_t)&identifier_info,
                                   &count);

    // 释放端口
    mach_port_deallocate(mach_task_self(), thread_port);

    if (kr != KERN_SUCCESS)
    {
        printf("Error getting thread info: %d\n", kr);
        return -1;
    }

    // 获取线程运行的最后一个CPU核心ID
    return (int)(identifier_info.thread_handle & 0xFFF);
}

int main()
{
    // 设置要使用的线程数
    int num_threads = 10;
    omp_set_num_threads(num_threads);

// 并行区域
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int cpu_id = get_cpu_core_id();

#pragma omp critical
        {
            printf("OpenMP Thread %d is running on CPU core %d\n",
                   thread_id, cpu_id);
        }

        // 添加一些计算工作，让线程有机会被分配到不同的核心
        double sum = 0.0;
        for (int i = 0; i < 1000000; i++)
        {
            sum += i * 1.0;
        }
    }

    return 0;
}