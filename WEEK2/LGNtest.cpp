/**
 * @file LGNtest.cpp
 * @brief Large Number test
 */

#include <iostream>
#include <stdlib.h>
#include "core.h"
#include <time.h>
using namespace std;

int N = 1e7;       // test case
double dev = 0.03; // deviation

double f(double x)
{
    // if (x >= -0.48)
    //     return sqrt(x + 1.03);
    // else
    //     return sqrt(0.07 - x);
    return (x + 0.48) * (x + 0.48);
}
int main()
{
    int tc = 0;
    double l = -0.5, r = 1.5, acc = 1e-3;
    double thn = -0.48;
    double ans;
    ans = lineSearch::find_mininum(f, l, r, acc, lineSearch::BINARY);
    cout << "[Binary search] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 << " dev:" << max(0.0, abs(thn - ans) - acc) / acc * 100 << "%\n";
    ans = lineSearch::find_mininum(f, l, r, acc, lineSearch::GOLDEN_RATIO);
    cout << "[0.618  method] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 << " dev:" << max(0.0, abs(thn - ans) - acc) / acc * 100 << "%\n";
    ans = lineSearch::find_mininum(f, l, r, acc, lineSearch::FIBONACCI);
    cout << "[  Fibonacci  ] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 << " dev:" << max(0.0, abs(thn - ans) - acc) / acc * 100 << "%\n";
    int begin = clock();
    while (N > tc++)
    {

        ans += lineSearch::find_mininum(f, l, r, acc, lineSearch::BINARY);
    }
    int end = clock();
    tc = 0;
    cout << "[Binary search] cost:" << double(end-begin)/CLOCKS_PER_SEC << "s" << "\n";
    begin = clock();
    while (N > tc++)
    {

        ans +=lineSearch::find_mininum(f, l, r, acc, lineSearch::GOLDEN_RATIO);
    }
    end = clock();
    tc = 0;
    cout << "[0.618  method] cost:" << double(end-begin)/CLOCKS_PER_SEC << "s" << "\n";
    begin = clock();
    while (N > tc++)
    {

        ans +=lineSearch::find_mininum(f, l, r, acc, lineSearch::FIBONACCI);
    }
    end = clock();
    tc = 10;
    cout << "[  Fibonacci  ] cost:" << double(end-begin)/CLOCKS_PER_SEC << "s" << "\n";
    cout << ans << "\n";
    system("pause");
}