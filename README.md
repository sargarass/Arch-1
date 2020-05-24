# Numerical integration trapezoidal rule

This project was made in 2013 year at the first year of Bauman Moscow State Technical University (Computer architecture course).

## Task

You need to create a program of numerical integration which use trapezoidal rule 
Beginning rules:

a) use type double

b) at the first steps you have to used cos x as integrable function, where x ∊ [ -π , π ];

c) In the process of performing the task, function and limits of integration have to be changed..

d) For each changing in the code you have to formulate the requirements for the test/hypothesis and analyze the results.

e) for more information please read [методичка.pdf](https://github.com/sargarass/Arch-1/blob/master/%D0%BC%D0%B5%D1%82%D0%BE%D0%B4%D0%B8%D1%87%D0%BA%D0%B0.pdf) (in russian). 

It is recommended to write the program in this way:
```C
// Listing 1
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

# Solution (english translated version of [DZ_Борнев.pdf](https://github.com/sargarass/Arch-1/blob/master/DZ_%D0%91%D0%BE%D1%80%D0%BD%D0%B5%D0%B2.pdf))


First of all let's write naive version of numerical integration
```C
// Listing 2
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
// Listing 3
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
<img src="http://latex.codecogs.com/gif.latex?\sigma=((((x+dx)(1\pm\epsilon)+dx)(1\pm\epsilon)+dx)\dots)+dx)(1\pm\epsilon)" border="0"/> (1)

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
// Listing 4
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
Let's consider a sum of floating point set

<img src="http://latex.codecogs.com/gif.latex?f(x)=S(n)=x_0+\dots+x_n" border="0"/>

Using formula (1)  and neglecting terms with ε greater than the first degree:

<img src="http://latex.codecogs.com/gif.latex?f(x)=S(n)\approx{x_0+n\epsilon{x_0}+x_1+n\epsilon{x_1}+(n-1)x_2\epsilon+x_2+...+x_n+x_n\epsilon}=\sum_{i=0}^{n}x_i+n\epsilon{x_0}+\sum_{i=1}^{n}(n-i+1)x_i\epsilon" border="0"/>

It can be seen that the coefficients of the first x's, for example, <img src="http://latex.codecogs.com/gif.latex?f(x)=x_0" border="0"/>, <img src="http://latex.codecogs.com/gif.latex?f(x)=x_1" border="0"/> - εn, while the coefficient of <img src="http://latex.codecogs.com/gif.latex?f(x)=x_n" border="0"/> - ε. Hence we can make the assumption that with a naive summation it is advantageous to compute sum of numbers, starting from small in modulus, so that the relative summation error is the smallest. Also it is better to compute sum of positive numbers separately from negative ones.

### Test
Let's write the program for summing the set of random numbers that will use different summation algorithms:

1. The naive algorithm

2. Summation of the sorted array in descending order

3. Summation of the sorted array in ascending order

4. To compute sum of the numbers, we will use the heap: at each operation we take two min elements of heap, compute their sum, push sum back to heap. Therefore at every operation we will minimize the error of summation.

Result of testing on two sets of random numbers with size 741777 (the naive long double summation was taken as exact solution):

| |Result |Absolute error | Result (second) | Absolute error (second) |
| --- | --- | --- | --- | --- |
|Naive|-5.176118010672767e+11|0.000122338533401489258|1.343202116610425e+06|2.97998212772654369e-08|
|Sorted(less)|-5.176118010672769e+11|6.07669353485107422e-05|1.343202116610455e+06|-2.50111042987555265e-12|
|Sorted(more)|-5.176118010672816e+11|0.00482150912284851074|1.343202116610420e+06|3.44564341503428295e-08|
|Heapsum|-5.176118010672768e+11|2.68220901489257812e-07|1.343202116610455e+06|-2.50111042987555265e-12|
|Long double naive|-5.176118010672767947e+11| | 1.343202116610454859e+06| |

Almost in all tests, there are near equality results given by the heap sum and sorting in ascending order, but on some it is noticed the advantage of heap sum. Also, in almost all tests, summation from larger to smaller was worse than naive.

**Conclusion**:
Hypothesis 2 can be confirmed: the summation result really improves if we first summarize the small numbers. For further analysis, we assume that our sum is considered fairly accurate. To do this, change the type of the variable sum to long double. Also, add the -m128bit-long-double compilation flag to get more accurate calculations when using long double.

## Hypothesis 3: lost of accuracy arises from the incorrect calculation of the areas of elementary trapezoids.
Note: here needs test to show this, but it will be shown after on graphic as a result. 

Since each add operation is performed with some error, then from the hypothesis 1, 2 we can conclude that *dx* at the moment of step *i*  is not equal to i * *dx* (initial *dx*).

In our implementation we calculate trapezium square:

<img src="http://latex.codecogs.com/gif.latex?S_{\phi}(i)=0.5*(f(x_i+x_{i_\delta}+f(x_{i+1}+x_{{i+1}_\delta}))*dx" border="0"/>,
where <img src="http://latex.codecogs.com/gif.latex?x_{i_\delta},x_{{i+1}_\delta}" border="0"/> are some errors.

When the exect solution is:
<img src="http://latex.codecogs.com/gif.latex?S(i)=0.5*(f(x_i)+f(x_{i+1}))*dx" border="0"/>

Let's calculate the absolute error along the Y axis:

<img src="http://latex.codecogs.com/gif.latex?y_\Delta=\sum_{i=0}^{N-1}(S(i)-S_{\phi}(i))" border="0"/>

Since the trapezoid method approximates the function on the each interval to a straight line, we simplify the formula:

<img src="http://latex.codecogs.com/gif.latex?y_\Delta=\sum_{i=0}^{N-1}(0.5*dx(k_{i}x_i-k_i(x_i+x_{i_\delta})+k_{i}x_{i+1}-k_{i}(x_{i+1}+x_{{i+1}_\delta}))=-0.5dx{\sum_{i=0}^{N-1}k_i*(x_{i_\delta}+x_{{i+1}_\delta})" border="0"/>

As we can see error along the Y axis linearly depends on the error along the X axis and the first derivative. If we compensate errors along X, the effect of the first derivative of Y is also compensate. Therefore, we will consider the height (*dx*) not as a constant, but *x2 - x*, where *x* is the value of *dx* at the i-th step, and *x2* is the value of *dx* on the (i + 1)-th. 

## Result with last suggestion:
```C
// Listing 5
typedef double T;
typedef double LT;
T f(T x)
{
    return cos(x);
}

#define MAX(a,b) (((a) > (b))? (a) : (b))
T integrate(T left, T right, ulong steps, T* real_right)
{
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

Let's integrate the function y = cos (x) on the interval [100π; 101π] by two implementations (from Listing 4 and Listing 5). 
The absolute error of the method is greater than <img src="http://latex.codecogs.com/gif.latex?8*10^-5" border="0"/>
for the entire integration interval.  We use the float type for X-s, since problems for float will be visible much earlier than for double. For summation, we will also use long double to exclude as much as possible the accumulation of the error in the summation over Y. We will construct a schedule based on the results of the absolute error of both realizations:
![](https://github.com/sargarass/Arch-1/blob/master/result.png)


As can be seen from the last test, the implementation in listing 5 does not "overflow" relative to the line y = 2 * 10^-5, while the implementation in Listing 4 shows much worse results. Since in the implementation from Listing 5 all the errors investigated in the previous hypotheses were taken into account, it is advisable to use it.
