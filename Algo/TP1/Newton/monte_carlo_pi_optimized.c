#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

// 函数声明：生成[0,1)之间的随机浮点数
double rand_double(unsigned int *seed)
{
    return (double)rand_r(seed) / (double)RAND_MAX;
}

int main(int argc, char *argv[])
{
    // 默认总点数
    unsigned long long total_points = 10000000000; // 10亿

    // 如果用户提供了参数，则使用用户指定的点数
    if (argc > 1)
    {
        total_points = strtoull(argv[1], NULL, 10);
    }

    unsigned long long points_in_circle = 0;

    // 获取主机名
    char hostname[1024];
    gethostname(hostname, 1024);
    printf("Before PARALLEL REGION TID %d: There are %d threads on CPU of %s\n\n",
           omp_get_thread_num(), omp_get_num_threads(), hostname);

    // 获取开始时间
    double start_time = omp_get_wtime();

// 并行区域
#pragma omp parallel num_threads(1)
    {
        // 每个线程有自己的随机数种子
        unsigned int seed = time(NULL) ^ omp_get_thread_num();

// 仅由一个线程执行，打印线程数信息
#pragma omp single
        {
            printf("In the PARALLEL REGION: Using %d threads on CPU of %s\n",
                   omp_get_num_threads(), hostname);
        }

// 使用reduction进行并行累加
#pragma omp for reduction(+ : points_in_circle) schedule(static)
        for (unsigned long long i = 0; i < total_points; i++)
        {
            double x = rand_double(&seed);
            double y = rand_double(&seed);
            if (x * x + y * y <= 1.0)
            {
                points_in_circle++;
            }
        }
    }

    // 获取结束时间
    double end_time = omp_get_wtime();

    // 计算π的估计值
    double pi_estimate = 4.0 * ((double)points_in_circle / (double)total_points);

    printf("After PARALLEL REGION: There are %d threads\n\n",
           omp_get_num_threads());

    printf("总点数: %llu\n", total_points);
    printf("圆内点数: %llu\n", points_in_circle);
    printf("估计的π值: %.10f\n", pi_estimate);
    printf("计算时间: %.4f 秒\n", end_time - start_time);

    printf("π的真实值: %.10f\n", 3.1415926535);

    return EXIT_SUCCESS;
}