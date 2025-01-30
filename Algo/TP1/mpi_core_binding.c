#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank, size;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    // 初始化 MPI 环境
    MPI_Init(&argc, &argv);

    // 获取进程的 rank 和总进程数
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 获取运行当前进程的处理器名称
    MPI_Get_processor_name(processor_name, &name_len);

    printf("MPI Rank %d/%d is running on processor: %s\n", rank, size, processor_name);

    // 结束 MPI 环境
    MPI_Finalize();
    return 0;
}