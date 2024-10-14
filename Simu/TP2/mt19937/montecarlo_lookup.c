#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// 引入任务二中生成的随机数数组
extern double random_numbers[]; // 声明外部数组，任务二生成的数组会在别的文件中定义

// 函数：判断点是否在球体内
int is_inside_sphere(double x, double y, double z, double radius)
{
    return (x * x + y * y + z * z) <= (radius * radius);
}

int main()
{
    // 初始化
    int total_points = 10000000; // 生成10,000,000个点
    int experiments = 10;        // 做10次实验
    double radius = 1.0;         // 球体半径为1
    int points_inside;           // 在球体内的点数量
    double estimated_volume;     // 估算的球体体积
    double pi = M_PI;            // 数学常数π
    double sum_volumes = 0.0;    // 估算体积的和，用于求平均
    double sum_error = 0.0;      // 误差的和

    // 使用时间函数来测量每次实验的耗时
    clock_t start_time, end_time, total_time;

    // 进行10次实验
    for (int exp = 0; exp < experiments; exp++)
    {
        points_inside = 0; // 重置球体内的点数量

        start_time = clock(); // 开始计时

        // 使用预生成的随机数进行模拟
        for (int i = 0; i < total_points; i++)
        {
            double x = (random_numbers[3 * i] * 2.0) - 1.0;     // 从数组中读取第1个随机数，转换到[-1, 1]区间
            double y = (random_numbers[3 * i + 1] * 2.0) - 1.0; // 从数组中读取第2个随机数
            double z = (random_numbers[3 * i + 2] * 2.0) - 1.0; // 从数组中读取第3个随机数

            // 判断点是否在球体内
            if (is_inside_sphere(x, y, z, radius))
            {
                points_inside++;
            }
        }

        // 估算球体体积：球体占立方体的比例 * 立方体体积
        estimated_volume = ((double)points_inside / total_points) * 8.0; // 立方体体积为2^3=8

        // 计算体积和π的误差
        double error = fabs((estimated_volume - (4.0 / 3.0) * pi) / ((4.0 / 3.0) * pi));

        // 累加体积和误差
        sum_volumes += estimated_volume;
        sum_error += error;

        end_time = clock(); // 结束计时

        // 输出每次实验的结果
        printf("TEST %d: V = %f, V_real = %f, loss = %f, time = %f s\n", exp + 1,
               estimated_volume, (4.0 / 3.0) * pi, error,
               ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
        total_time += end_time - start_time;
    }

    // 计算10次实验的平均值和平均误差
    printf("V = %f\n", sum_volumes / experiments);
    printf("loss = %f\n", sum_error / experiments);
    printf("total time = %f s\n", ((double)(total_time / CLOCKS_PER_SEC)));

    return 0;
}
