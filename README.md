# Цель работы
"Самая сложная часть каждого этапа: формулирование требований к тесту и анализ
полученных результатов. Собственно говоря, получение такого навыка и является целью
работы. Дополнительные цели: получение навыков разработки программ в вещественных
числах, умение учитывать вычислительные погрешности, навыки составления отчётов." (с) Методичка.pdf

# Task
You need to create a program of numerical integration which use trapezoidal rule 
Beginning rules:
a) use type double
b) at the first steps you have to used cos x as integrable function, where x ∊ [ -π , π ];
c) In the process of performing the task, function and limits of integration have to be changed..
d) for more information please read [методичка.pdf](https://github.com/sargarass/Arch-1/blob/master/%D0%BC%D0%B5%D1%82%D0%BE%D0%B4%D0%B8%D1%87%D0%BA%D0%B0.pdf) (in russian). 

It is recommended to write the program in this way:
```C

#define _USE_MATH_DEFINES
#include <math.h>
#include <locale.h>
#include <stdio.h>

double f( double x )
{
    return sin(x);
}

double F( double x )
{
    return -cos( x );
}

/* function of numerical integration */
double Integral( double Left, double Right, long N, double (*func)(double) )
{
    double x, dx, res = 0.0;
    dx = (Right - Left) / N;
    for ( x = Left; x < Right; x+=dx ) res += ... func( ... ) ...;
    res *= dx;
    return res;

}

int main()
{
    long n;
    double L = 0.0, R = M_PI;
    double V, V0 = F( R ) - F( L );
    /* exact solution */
    setlocale( LC_ALL, "" );
    /* use , or . to seperate fractional and decimal part of real number */
    printf("Number of steps;Relative error\n");
    for ( n = 1; n < 100; n += n/50+1) {
        V = Integral( L, R, n, f );
        /* approximate solution for n steps */
        printf( "%ld;=%.15G\n", n, (V-V0)/V0 );
        /* n and relative error */
    }
}
```

# How to build
The program is written in C. For building you need to use qmake from Qt:
In the folder with project run following commands:
1 qmake arch2.pro
2 make

# Solution
It is english translated version of [DZ_Борнев.pdf](https://github.com/sargarass/Arch-1/blob/master/DZ_%D0%91%D0%BE%D1%80%D0%BD%D0%B5%D0%B2.pdf)

First of all let's write naive version of numerical integration
```C

```


Финальная реализация:
```C
typedef double T;
typedef double LT;
T f(T x)
{
    return cos(x);
}

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
```
