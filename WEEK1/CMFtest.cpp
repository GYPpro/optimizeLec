/**
 * @file CMFtest.cpp
 * @brief Complex Model Funtion test
 */


#include <iostream>
#include <stdlib.h>
#include "core.h"
#include <time.h>
using namespace std;

int N = 5000;       // test case
double dev = 0.03; // deviation
int k = 1e5;

double f(double x)
{
    double pf = x-0.3;
    for(int i = 0;i < k -1;i ++)
        pf *= (x-0.3);
    pf = min(pf,0.001);
    return (x-0.3) * (x-0.3) + pf;
}
int main()
{
    // cout << f();
    int tc = 0;
    double l = -1e5, r = 1e5, acc = 1e-5;
    double thn = 0.3;
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