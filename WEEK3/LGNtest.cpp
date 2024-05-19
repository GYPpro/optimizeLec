/**
 * @file LGNtest.cpp
 * @brief 大量数据测试
 */

#include <iostream>
#include <stdlib.h>
#include "core.h"
#include <time.h>
#include <math.h>
using namespace std;

int N = 1e5;       // test case
double dev = 0.5916079778; // deviation

double f(double x)
{
    return x + 0.35/x;
}
double df(double x)
{
    return (20.0 * x * x - 7.0) / (20.0 * x * x);
}
double ddf(double x)
{
    return 7.0 / (10.0 * x * x * x);
}
int main()
{
    int tc = 0;
    double l = 0, r = 1.5, acc = 1e-3;
    double thn =0.5916079778;
    // double ans;
    auto ans = ODSearch::find_mininum(f, df, l, r, acc, 0.2, ODSearch::DESCENT);
    cout << "[DESCENT] ans:" << ans.second << " at:" << ans.first<< " acc:" << (acc / abs(thn - ans.first)) * 100 << " dev:" << max(0.0, abs(thn - ans.first) - acc) / acc * 100 << "%\n";
    ans = ODSearch::find_mininum(f, df, l, r, acc, 0.2, ODSearch::NEWTON, ddf);
    cout << "[NEWTON ] ans:" << ans.second << " at:" << ans.first<< " acc:" << (acc / abs(thn - ans.first)) * 100 << " dev:" << max(0.0, abs(thn - ans.first) - acc) / acc * 100 << "%\n";
    ans = ODSearch::find_mininum(f, df, l, r, acc, 0.2, ODSearch::SECANT, ddf);
    cout << "[SECANT ] ans:" << ans.second << " at:" << ans.first<< " acc:" << (acc / abs(thn - ans.first)) * 100 << " dev:" << max(0.0, abs(thn - ans.first) - acc) / acc * 100 << "%\n";
    int begin = clock();
    while (N > tc++)
    {

        ans = ODSearch::find_mininum(f, df, l, r, acc, 0.5, ODSearch::DESCENT);
    }
    int end = clock();
    tc = 0;
    cout << "[DESCENT] cost:" << double(end-begin)/CLOCKS_PER_SEC << "s" << "\n";
    begin = clock();
    while (N > tc++)
    {

        ans = ODSearch::find_mininum(f, df, l, r, acc, 0.5, ODSearch::NEWTON, ddf);
    }
    end = clock();
    tc = 0;
    cout << "[NEWTON ] cost:" << double(end-begin)/CLOCKS_PER_SEC << "s" << "\n";
    begin = clock();
    while (N > tc++)
    {

        ans = ODSearch::find_mininum(f, df, l, r, acc, 0.5, ODSearch::SECANT, ddf);
    }
    end = clock();
    tc = 10;
    cout << "[SECANT ] cost:" << double(end-begin)/CLOCKS_PER_SEC << "s" << "\n";
    cout << ans.first << "\n";
    system("pause");
}