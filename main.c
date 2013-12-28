//#pragma STDC FENV_ACCESS ON
#define _USE_MATH_DEFINES
#define _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "float.h"
#include "stdlib.h"
#include <stdbool.h>

typedef double T;
typedef double LT;

T f(T x)
{
    return cos(x);
}

long double F(long double x)
{
    return sin(x);
}

/*
double integrate(double left, double right, ulong steps, ulong* made_steps)
{
    long double sum = 0;
    double dx  = (right-left)/steps;
    double x1, x2;
    uint i;
    for(i = 0; i < steps; i++)
    {
       x1 = left + i * dx;
       x2 = left + (i + 1) * dx;
       double _dx = x2 - x1;
       sum += ((long double)f(x1) + f(x2))*0.5 * _dx;
    }

    //sum += 0.5 * (f(right) + f(left + x2)) * (right - x2);

    return  sum;
}*/


//typedef T LT;
/*
T integrate(T left, T right, ulong steps, T* real_right)
{
    if (steps >= (right - left) * ((ulong)(1) << (ulong)(53)) * MAX(fabs(left),fabs(right)))
        return NAN;

    LT sum = 0;
    T x2, _dx, x = left;
    T dx  = (right  - left) / steps;

    for(;;)
    {
        x2 = x + dx;


        if (x2 > right) break;

        _dx = x2 - x;
        sum += (((LT)f(x) + (LT)f(x2)) * _dx) * 0.5;
        x    = x2;
    }

    _dx = right - x;
    sum += ((LT)f(right) + (LT)f(x)) * _dx * 0.5;
    (*real_right) = x;

    return  sum;
}*/
//Last version. Will return NAN when "steps" value two big


#define MAX(a,b) (((a) > (b))? (a) : (b))
T integrate(T left, T right, ulong steps, T* real_right)
{
    if (steps >= ((long double)right - (long double)left) * ((ulong)(1) << (ulong)(53)) * MAX(fabsl((long double)left),fabsl((long double)right)))
     return NAN;
    LT sum = 0;
    T x2 = left, x = left;
    T dx  = (right  - left) / steps;
    for(; x2 < right; x = x2)
    {
         x2 = x + dx;
         sum += (LT)(((f(x) + f(x2)) * (x2-x)) * 0.5);
    }
    sum += (LT)(((f(right) + f(x)) * (right - x) * 0.5));
    (*real_right) = x + (right - x);
    return  sum;
}
/*
T integrate(T left, T right, ulong steps, T* real_right)
{
    LT sum = 0;
    T x   = left;
    T x2  = left;
    T dx = (right - left)/steps;
    for(;;)
    {
        x2 = x + dx;
        if (x2 > right) break;
        sum += (LT)((0.5 * (f(x) + f(x2)) * dx));
        x = x2;
    }
    sum += (LT)(0.5 * (f(right) + f(x)) * (right - x));
    (*real_right) = x + (right - x);
    return  sum;
}*/
/*
typedef double T;
typedef long double LT;

#define MAX(a,b) (((a) > (b))? (a) : (b))
#define DIF(a,b) ( ((a) - (b))*((a) + (b)) / ((a) + (b)) )
#define SUM(a,b) ( ((a) - (b))*((a) + (b)) / ((a) - (b)) )
double compdiff(double a, double b, double* out)
{
    (*out) = DIF(a , b);
    if ((*out) != (*out)) (*out) = a - b;
}
double compsum(double a, double b, double* out)
{
    (*out) = SUM(a , b);
    if ((*out) != (*out)) (*out) = a - b;
}
//Last version. Will return NAN when "steps" value two big
T integrate(T left, T right, ulong steps, T* real_right)
{
    if (steps >= ((long double)right - (long double)left) * ((ulong)(1) << (ulong)(53)) * MAX(fabsl((long double)left),fabsl((long double)right)))
        return NAN;

    LT sum = 0;
    T x2 = left, _dx, x = left;
    T dx  = (right  - left) / steps;
    for(x2 = x + dx; x2 < right; x = x2, x2 = x + dx)
    {
        compdiff(x2, x, &_dx);
        //if (fabs(_dx ) < fabs(x)) _dx = x2 - x;
        sum += (((LT)f(x) + (LT)f(x2)) * _dx) * 0.5;
    }
    compdiff(right, x, &_dx);
    sum += ((LT)f(right) + (LT)f(x)) * _dx * 0.5;
    (*real_right) = (T)((LT)(x) + (LT)(_dx));
    return  sum;
}
*/
/*
double integrate(double left, double right, ulong steps,
                 double* real_right)
{
    double sum = 0;
    double x   = left;
    double dx  = (right-left)/steps;
    while (x < right)
    {
        sum += 0.5 * (f(x) + f(x + dx)) * dx;
        x += dx;
    }
    (*real_right) = x;
    return  sum;
}*/

/*
double integrate(double left, double right, ulong steps, ulong* made_steps)
{
    double sum = 0;
    double x   = left;
    double dx  = (right-left)/steps;
    int i = 0;
    while (x + dx != x)
    {
        dx = (right-left)/steps;
        steps+= pow(10,14);
        i++;
    }
    printf("%i %llu\n", i, steps);
    return  sum;
}
*/

bool test(double left, double right, ulong steps, long double expect, bool show_steps, bool show_res, bool show_expect, bool show_absolute, bool show_obs, bool show_pass,bool only_numbers)
{
    double real_right;
    double res = integrate(left, right, steps, &real_right);

    if (show_steps)
    {
        if (!only_numbers)
        {
            printf("Steps: ");
        }
        printf("%5ld ",steps);
    }

    if (show_res)
    {
        if (!only_numbers)
        {
            printf("| Integral: ");
        }
        printf("%18.*f ", DBL_DIG, res);
    }
    if (show_expect)
    {
        if (!only_numbers)
        {
            printf("| Expected: ");
        }
        printf("%18.*Lf ", DBL_DIG, expect);
    }
    if (show_absolute)
    {
        if (!only_numbers)
        {
            printf("| Absolute error: ");
        }
        printf("%18.*Le ", LDBL_DIG, fabsl((expect - (long double)res)));
    }
    if (show_obs)
    {
        if (!only_numbers)
        {
            printf("| Observational error: ");
        }
        printf("%18.*Le ", LDBL_DIG, fabsl(((expect - (long double)res))/expect));
    }
    if (show_pass)
    {
        if (!only_numbers)
        {
            printf("| Pass: ");
        }

        if (fabsl(res - expect) <= DBL_EPSILON)
        {
            printf(" TRUE ");
        }
        else
        {
            printf("FALSE ");
        }
    }
    printf(" \n");
    return (fabsl(res - expect) <= DBL_EPSILON);
}

int main(void)
{
    const double LEFT  = 100*M_PI;
    const double RIGHT = 101*M_PI;
    const long double EXPECT = F(RIGHT)-F(LEFT);

    printf("==== Integral from %16.15f to %16.15f ====\n",LEFT,RIGHT);
   /* printf("start: ");
    scanf("%llu",&left);
    printf("count: ");
    scanf("%llu",&n);
*/
    for (ulong i = 100; i < 200; i++)
    {
        ///  left,right,steps, expect,eps,show_steps,show_res,show_expect,show_exptect_get,show_obs,show_pass,only_numbers)
        test(LEFT, RIGHT, i, EXPECT, true, true, true, true, true, true, true);
    }
    return 0;
}
