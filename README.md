# Цель работы
"Самая сложная часть каждого этапа: формулирование требований к тесту и анализ
полученных результатов. Собственно говоря, получение такого навыка и является целью
работы. Дополнительные цели: получение навыков разработки программ в вещественных
числах, умение учитывать вычислительные погрешности, навыки составления отчётов." (с) Методичка.pdf

# Задание:
Разработать подпрограмму численного интегрирования, реализующую метод трапеций;
Дополнительные указания:

а) использовать тип double;

б) на первых шагах использовать в качестве подынтегральной функции cos x, где x ∊ [ -π , π ];

в) в процессе выполнения задания подынтегральную функцию и/или пределы интегрирования надо менять 

г) см. методичку

Программу рекомендуется оформить примерно таким образом:
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

/* функция численного интегрирования */
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
    /* точное решение */
    setlocale( LC_ALL, "" );
    /* использовать , или . для отделения дробной части */
    printf("Число шагов;Относительная ошибка\n");
    for ( n = 1; n < 100; n += n/50+1) {
        V = Integral( L, R, n, f );
        /* приближенное решение для n шагов */
        printf( "%ld;=%.15G\n", n, (V-V0)/V0 );
        /* n и относительная ошибка */
    }
}
```

# Сборка
Проект написан на C. Для сборки необходима утилита qmake. 

В папке с проектом выполнить:

1 qmake arch2.pro

2 make

# Результат
Была разработана программа, которая учитывает все виды найденных ошибок (см. DZ_Борнев.pdf). В программе была снижена вычислительная погрешность, также устранен выход за правую границу интегрирования.

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
