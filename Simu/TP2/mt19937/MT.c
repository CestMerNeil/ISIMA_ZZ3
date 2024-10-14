#include "mt19937ar_h.c"
#include <stdio.h>

#define N_MT 30000000

int main()
{
    init_genrand(5489UL);

    FILE *f = fopen("random_numbers.c", "w");
    fprintf(f, "double random_numbers[%d] = {\n", N_MT);
    for (int i = 0; i < N_MT; i++)
    {
        double random_number = genrand_real2(); // 生成[0, 1)区间的随机数
        if (i == N_MT - 1)
        {
            fprintf(f, "    %f\n", random_number); // 最后一个数不加逗号
        }
        else
        {
            fprintf(f, "    %f,\n", random_number);
        }
    }
    fprintf(f, "};\n");
    fclose(f);
    return 0;
}