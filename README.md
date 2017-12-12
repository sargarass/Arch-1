# This project was made in 2013 year at the first year of Bauman Moscow State Technical University (Computer architecture course).

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
#define _USE_MATH_DEFINES
#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>

double f(double x) /* integrable function */
{
    return cos(x);
}
 
double F(double x) /* 
{
    return sin(x);
}

/*
@left, right - limits of integration
@steps - number of steps
*/
double integrate(double left, double right, ulong steps)
{
    double sum = 0; // result
    double x   = left; // left bound of integration on i-step
    double dx  = (right-left)/steps; // height
    while(x < right)
    {
       sum += 0.5 * (f(x) + f(x + dx)) * dx;
       x   += dx;
    }
    return  sum;
}
```

## Preliminary preparation:
Let's check that compiler generates code corresponding to the standard IEEE 754.
In this project gcc compiler was used. For full IEEE 754 support official wiki recommends to use following compilation flags
```
-frounding-math -fsignaling-nans
```
We changed QMAKE_CFLAGS in file [arch2.pro]() in the following way:
```
-O0 -std=c99 -frounding-math -fsignaling-nans
```
Noticed that we turned off gcc optimization because we want to find our own mistakes in working with float-point arithmetic, not gcc.


## First run
| Number of steps | Program result | Expected result | Absolute Error |
| --- | --- | --- | --- |
1 | **-6.283185307179586** | **0.000000000000000** | **6.283185307179586477e+00**
2 | 0.000000000000000 | 0.000000000000000 | 2.449293598294706414e-16  |
3 |**-0.523598775598299** | **0.000000000000000** | **5.235987755982992826e-01**  |
4 | 0.000000000000000 |  0.000000000000000 | 2.288475490443933335e-17  |
5 | 0.000000000000000 | 0.000000000000000 | 1.339070573669549874e-16  |
6 | **-0.785398163397448** | **0.000000000000000** | **7.853981633974485239e-01** |
7 | 0.000000000000000 | 0.000000000000000 | 1.991598500205919747e-16  |
8 | 0.000000000000000 | 0.000000000000000 |2.449293598294706414e-16  |
9 | 0.000000000000000 | 0.000000000000000 | 8.813754755807632069e-17  |
10 | 0.000000000000000 | 0.000000000000000 | 1.339070573669549874e-16  |
11 | **-0.000000000000000** | ***0.000000000000000** |***5.779962672170176036e-16***  |
12 |**-0.488524308328426** | **0.000000000000000** |**4.885243083284261052e-01**  |
13 | 0.000000000000000 | 0.000000000000000 |1.436486987893341477e-16  |
14 | 0.000000000000000 | 0.000000000000000 |1.991598500205919747e-16  |
15 | 0.000000000000001 | 0.000000000000000 |6.987602111019124179e-16  |
16 | 0.000000000000000 | 0.000000000000000 |7.839590613569716037e-17  |
17 |**-0.357120032891942** | **0.000000000000000** |**3.571200328919425744e-01**  |
18 |-0.000000000000000 | 0.000000000000000 |4.114628135232441225e-16  |
19 |-0.000000000000000 | 0.000000000000000 |5.779962672170176036e-16  |
   20 | 0.000000000000000 | 0.000000000000000 |1.436486987893341477e-16  |
   21 |-0.000000000000001 | 0.000000000000000 |8.555520233733067387e-16  |
   22 |**-0.279814942303097** | **0.000000000000000** |**2.798149423030970813e-01**  |
   23 |**-0.268116805632010** | **0.000000000000000**|**2.681168056320099808e-01**  |
   24 | 0.000000000000001 | 0.000000000000000 |8.652936647956858990e-16  |
   25 |**-0.247379455879290** | **0.000000000000000** |**2.473794558792904948e-01**  |
   26 |**-0.238149859010715** |  **0.000000000000000** | **2.381498590107149989e-01**  |
   27 | 0.000000000000000 | 0.000000000000000 | 1.894182085982128144e-16  |
   28 | 0.000000000000000 | 0.000000000000000 |2.288475490443933335e-17  |
   29 |-0.000000000000000 | 0.000000000000000 |5.779962672170176036e-16  |
   30 |**0.207151132339387**| **0.000000000000000** |**2.071511323393869182e-01**  |

Notice that in some rows (highlighted in bold) expected results differ from program results. 

Consider number of steps equals 1. Using trapezoidal rule we can get:

<img src="http://latex.codecogs.com/gif.latex?\int^{\pi}_{-\pi}cos(x)=0.5*2\pi\(cos(-\pi)+cos(\pi)\)\approx-6.2831853071795864769252" border="0"/>
We can conclude that for this number of steps program result is right.

Then consider number of steps equals 3:

<img src="http://latex.codecogs.com/gif.latex?\int^{\pi}_{-\pi}cos(x)=0.5*\frac{2\pi}{3}(cos(-\pi)+2cos(\frac{-\pi}{3})+2cos(\frac{\pi}{3})+cos(\pi))=0" border="0"/>

The result of compution is differ from program result. So we can decide that our program has an error in the implementation.
Since in the "naive implementation" we used "while loop" and all floating points operation are perfomed with some kind of error, we can assuming we made one extra step of integration and the *right* border were crossed.

Change our program in the following way for getting *right* bound of interval after integration:
```C
double integrate(double left, double right, ulong steps, double* real_right)
{
    double sum = 0;
    double x   = left;
    double dx  = (right-left)/steps;
    while(x < right)
    {
        sum += 0.5 * (f(x) + f(x + dx)) * dx;
        x   += dx;
    }
    (*real_right) = x; /* new */
    return  sum;
}
```
| Number of steps | Right bound | Program's result | Expected result | Absolute Error |
| --- | --- | --- | --- | --- |
1|3.141592653589793|-6.283185307179586|0.000000000000000|6.283185307179586477e+00|
2|3.141592653589793|0.000000000000000|0.000000000000000|2.449293598294706414e-16|
3|**5.235987755982988**|-0.523598775598299|0.000000000000000|5.235987755982992826e-01|
4|3.141592653589793|0.000000000000000|0.000000000000000|2.288475490443933335e-17|
5|3.141592653589793|0.000000000000000|0.000000000000000|1.339070573669549874e-16|
6|**4.188790204786390**|-0.785398163397448|0.000000000000000|7.853981633974485239e-01|
7|3.141592653589793|0.000000000000000|0.000000000000000|1.991598500205919747e-16|
8|3.141592653589793|0.000000000000000|0.000000000000000|2.449293598294706414e-16|
9|3.141592653589794|0.000000000000000|0.000000000000000|8.813754755807632069e-17|
10|3.141592653589793|0.000000000000000|0.000000000000000|1.339070573669549874e-16|
11|3.141592653589794|-0.000000000000000|0.000000000000000|5.779962672170176036e-16|
12|**3.665191429188090**|-0.488524308328426|0.000000000000000|4.885243083284261052e-01|
13|3.141592653589793|0.000000000000000|0.000000000000000|1.436486987893341477e-16|
14|3.141592653589793|0.000000000000000|0.000000000000000|1.991598500205919747e-16|
15|3.141592653589793|0.000000000000001|0.000000000000000|6.987602111019124179e-16|
16|3.141592653589793|0.000000000000000|0.000000000000000|7.839590613569716037e-17|
17|**3.511191789306239**|-0.357120032891942|0.000000000000000|3.571200328919425744e-01|
18|3.141592653589794|-0.000000000000000|0.000000000000000|4.114628135232441225e-16|
19|3.141592653589794|-0.000000000000000|0.000000000000000|5.779962672170176036e-16|
20|3.141592653589793|0.000000000000000|0.000000000000000|1.436486987893341477e-16|
21|3.141592653589793|-0.000000000000001|0.000000000000000|8.555520233733067387e-16|
22|**3.427191985734319**|-0.279814942303097|0.000000000000000|2.798149423030970813e-01|
23|**3.414774623467165**|-0.268116805632010|0.000000000000000|2.681168056320099808e-01|
24|3.141592653589794|0.000000000000001|0.000000000000000|8.652936647956858990e-16|
25|**3.392920065876975**|-0.247379455879290|0.000000000000000|2.473794558792904948e-01|
26|**3.383253626942852**|-0.238149859010715|0.000000000000000|2.381498590107149989e-01|
27|3.141592653589794|0.000000000000000|0.000000000000000|1.894182085982128144e-16|
28|3.141592653589793|0.000000000000000|0.000000000000000|2.288475490443933335e-17|
29|3.141592653589794|-0.000000000000000|0.000000000000000|5.779962672170176036e-16|
30|**3.351032163829112**|-0.207151132339387|0.000000000000000|2.071511323393869182e-01|

## Hypothesis 1
As we can see in tests from last table rows which have differ program's result from expected result also have different right bound.

### 1. Estimate the accumulated error in the summation 
```
x = x + dx
```
If every operation of summation is performing with some error <img src="http://latex.codecogs.com/gif.latex?\epsilon" border="0"/> then:
<img src="http://latex.codecogs.com/gif.latex?\sigma=((((x+dx)(1\pm\epsilon)+dx)(1\pm\epsilon)+dx)\dots)+dx)(1\pm\epsilon)" border="0"/>
where <img src="http://latex.codecogs.com/gif.latex?\sigma" border="0"/> - is sum computed with some error.
Subtracting from this formula the exact value of the sum for the nth step <img src="http://latex.codecogs.com/gif.latex?x+ndx" border="0"/> and neglecting terms with ε greater than the first degree we can get formula to computing sum's error for n steps:

<img src="http://latex.codecogs.com/gif.latex?\delta(n)=\pm\frac{\epsilon(right(n+1)-left(n-1))}{2}" border="0"/>

Conclude that expected an approximately linear increase in the error with increasing of steps. 

For number of steps=3:

<img src="http://latex.codecogs.com/gif.latex?\delta(3)=1.04*10^{-15}" border="0"/>

Which does not explain the absolute error <img src="http://latex.codecogs.com/gif.latex?\Delta\approx0.5" border="0"/>.
Conclude that error is not in summation <img src="http://latex.codecogs.com/gif.latex?x+dx" border="0"/> 

### 2. Estimate the error of crossing right bound
The crossing right bound occurs at an approximate equality of *x* and *right*. Since *x* is still considered less than the *right*, another iteration of the loop is performed. Let's try to estimate what it will lead to.
Let *x = right* then absolute error of crossing bound will be approximate equal:

<img src="http://latex.codecogs.com/gif.latex?0.5(f(x)+f(x+dx))*dx" border="0"/>

In case of our function and number of steps equals 3:
<img src="http://latex.codecogs.com/gif.latex?dx=\frac{2\pi}{3}" border="0"/>, 
<img src="http://latex.codecogs.com/gif.latex?x=\pi" border="0"/>, 
<img src="http://latex.codecogs.com/gif.latex?x=f(x)=cos(x)" border="0"/>

<img src="http://latex.codecogs.com/gif.latex?S_{\delta}=0.5(f(x)+f(x+dx))*dx=-0.5cos(\frac{2\pi}{3})*\frac{2\pi}{3}\approx-0.5235987755982988" border="0"/>
We can admit that this number coincides with the absolute error, therefore, our hypothesis was confirmed.
If we used "for loop" with fixed number of steps we still be able to get same error, or even didn't get right bound *(left + ndx < right)*.

We perform modification of program:
1. Loop will stop when *right < x2* which means that we will be stopped at n-1 step of integration
2. Last step of integration will be performed right after loop
Using this modification we also avoid error if function was not defined beyond integration interval

```C
double integrate(double left, double right, ulong steps, double* real_right)
{
 	 double sum   = 0;
     double x2, x = left;
     double dx    = (right - left)/steps;
     for(;;)
     {
         x2 = x + dx;
         if (x2 > right) break;
         sum += 0.5 * (f(x) + f(x2)) * dx;
         x = x2;
     }
     sum += 0.5 * (f(right) + f(x)) * (right - x);
     (*real_right) = x + (right - x);
     return  sum;
}
```

For confidence we can integrate piecewise function *f(x)* which is defined as:

<img src="http://latex.codecogs.com/gif.latex?f(x)=g(x)" border="0"/>, <img src="http://latex.codecogs.com/gif.latex?x\le{right}" border="0"/>

<img src="http://latex.codecogs.com/gif.latex?f(x)=NaN" border="0"/>, <img src="http://latex.codecogs.com/gif.latex?x>{right}" border="0"/>

All operation perfomed with *NaN* will return *NaN* and it would be immediately noticeable if the integration failed.
The results of testing are not given here because of their obviousness.
**Conclusion**:
After the introduced changes integral at those steps on which there were "big" absolute error is considered sufficiently accurate. The serious error has been eliminated, therefore, it is **advisable to make these changes into the program**. 

## Hypothesis 2: 
Let's consider a sum of floating point vector
S(n)

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
