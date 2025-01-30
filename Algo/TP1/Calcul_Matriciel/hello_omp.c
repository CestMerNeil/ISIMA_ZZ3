#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "omp.h"
#include <mach/mach.h>
#include <mach/thread_act.h>

int get_cpu_num()
{
#if defined(__APPLE__)
    mach_msg_type_number_t count = THREAD_BASIC_INFO_COUNT;
    thread_basic_info_data_t info;

    mach_port_t thread = mach_thread_self();
    kern_return_t ret = thread_info(
        thread,
        THREAD_BASIC_INFO,
        (thread_info_t)&info,
        &count);
    mach_port_deallocate(mach_task_self(), thread);

    return (ret == KERN_SUCCESS) ? info.cpu_usage : -1;
#else
    return sched_getcpu();
#endif
}

int main()
{
    int tid = -1;
    char hostname[1024];

    if (gethostname(hostname, sizeof(hostname)) == -1)
    {
        perror("gethostname failed");
        return EXIT_FAILURE;
    }

    printf("Before PARALLEL REGION TID %d: There are %d threads on CPU %d of %s\n\n",
           omp_get_thread_num(), omp_get_num_threads(), get_cpu_num(), hostname);

#pragma omp parallel num_threads(10) firstprivate(tid)
    {
        tid = omp_get_thread_num();
        if (!tid)
        {
            printf("In the PARALLEL REGION TID %d: There are %d threads in process\n",
                   tid, omp_get_num_threads());
        }
        printf("Hello World from TID %d / %d on CPU %d of %s!\n\n",
               tid, omp_get_num_threads(), get_cpu_num(), hostname);
    }

    printf("After PARALLEL REGION TID %d: There are %d threads\n\n",
           tid, omp_get_num_threads());

    return EXIT_SUCCESS;
}