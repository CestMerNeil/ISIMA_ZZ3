#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

// ANSI for output
// https://en.wikipedia.org/wiki/ANSI_escape_code
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define CYAN "\033[0;36m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

// Example 1: How does float and double compare?
void example1()
{
    float a = 0.7;
    float b = 0.5;

    if (a < 0.7)
    {
        if (b < 0.5)
            printf("2 Conditions are true\n");
        else
            printf("1st condition is true\n");
    }
    else
        printf("All conditions are false\n");
}

// Example 2: How different the representation of float and double?
void example2()
{
    float a = 0.7, b = 0.5;
    double c = (double)a;
    double d = 0.7;

    printf("Float a: %0.10f\n", a);
    printf("Double c: %0.15f\n", c);

    printf("Double d: %0.15f\n", d);
    printf("Double c: %0.18f\n", c);
    printf("Double d: %0.18f\n", d);

    if (a < .7)
    {
        if (b < .5)
            printf("2 Conditions are true\n");
        else
            printf("1st condition is true\n");
    }
    else
        printf("All conditions are false\n");
}

// Example 3: Control precision
void example3()
{
    double x = 10;
    double y = sqrt(x);

    y *= y;

    if (x == y)
        printf("Square is Equal\n");
    else
        printf("Not Equal and the diference is %1.15f\n", x - y);
    if (fabs(x - y) < 1e-9)
        printf("Square is in the range of 1e-9\n");
    // Relative error
    if (fabs(x - y) / x < 1e-9)
        printf("Relative error is in the range of 1e-9\n");
}

// Example 4: Loss of Accumulation Precision in Addition and Subtraction
void example4()
{
    float f = 0.1f;
    float sum = 0;

    for (int i = 0; i < 10; i++)
    {
        sum += f;
    }
    float product = f * 10;
    printf("Sum: %1.15f, Mul: %1.15f, Mul2: %1.15f\n", sum, product, f * 10);
    printf("Loss of Accumulation Precision in Addition: %1.15f\n", sum - product);
}

// Example 5: The effect of error on the function
void example5()
{
    for (int i = 0; i < 20; ++i)
    {
        double h = pow(10, -i);
        printf("h: %0.18f, f: %0.18f\n", h, (sin(1.0 + h) - sin(1.0)) / h);
    }
    printf("Exact: %0.18f\n", cos(1.0));
}

// Example 6: Finite Range of Floating Point Numbers
void example6()
{
    float f = 123456789;
    long long real_f = 123456789;
    printf("Long Long(Hope f): %lld\n", real_f);
    printf("Float(Real f): %f\n", f);
    printf("Float + 1: %f\n", f + 1);
    if (fabs(f - (f + 1)) / f < 1e-9)
        printf("f = f + 1 ... ? ¯\\_(ツ)_/¯\n");
    else
        printf("Not Equal\n");

    double d = 123456789123456789;
    long long real_d = 123456789123456789;
    printf("Long Long(Hope d): %lld\n", real_d);
    printf("Double(Real d): %f\n", d);
    printf("Double + 1: %f\n", d + 1);
    if (fabs(d - (d + 1)) / d < 1e-9)
        printf("d = d + 1 ... ? ¯\\_(ツ)_/¯\n");
    else
        printf("Not Equal\n");
}

// Example 7: Not return "Numbers"
void example7()
{
    double x = DBL_MAX;
    printf("DBL_MAX: %f\n", x);
    printf("DBL_MAX * 10: %f\n", x * 10);
}

int main()
{
    printf(BOLD GREEN "Examples\n" RESET);
    printf(BLUE "====================================================================================\n" RESET);
    printf(RED "Example 1: " RESET BOLD CYAN UNDERLINE "How does it impact my computing?\n" RESET);
    example1();

    printf(BLUE "====================================================================================\n" RESET);
    printf(RED "Example 2: " RESET BOLD CYAN UNDERLINE "How different the representation of float and double?\n" RESET);
    example2();

    printf(BLUE "====================================================================================\n" RESET);
    printf(RED "Example 3: " RESET BOLD CYAN UNDERLINE "Control precision\n" RESET);
    example3();

    printf(BLUE "====================================================================================\n" RESET);
    printf(RED "Example 4: " RESET BOLD CYAN UNDERLINE "Loss of Accumulation Precision in Addition and Subtraction\n" RESET);
    example4();

    printf(BLUE "====================================================================================\n" RESET);
    printf(RED "Example 5: " RESET BOLD CYAN UNDERLINE "The effect of error on the function\n" RESET);
    example5();

    printf(BLUE "====================================================================================\n" RESET);
    printf(RED "Example 6: " RESET BOLD CYAN UNDERLINE "Finite Range of Floating Point Numbers\n" RESET);
    example6();

    printf(BLUE "====================================================================================\n" RESET);
    printf(RED "Example 7: " RESET BOLD CYAN UNDERLINE "Not return \"Numbers\"\n" RESET);
    example7();

    return 0;
}
