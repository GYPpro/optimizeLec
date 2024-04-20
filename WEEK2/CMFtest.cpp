/**
 * @file CMFtest.cpp
 * @brief Complex Model Funtion test
 */


#include <iostream>
#include <stdlib.h>
#include "core.h"
#include <time.h>
using namespace std;

int N = 50;       // test case
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
double df(double x)
{
    // double pf = x-0.3;
    // for(int i = 0;i < k -1;i ++)
    //     pf *= (x-0.3);
    // pf = min(pf,0.001);
    return 2 * x - 0.6;
}
double ddf(double x)
{
    double pf = x-0.3;
    for(int i = 0;i < k -1;i ++)
        pf *= (x-0.3);
    pf = min(pf,0.001);
    return 2.0 + pf;
}
int main()
{
    // cout << f();
    int tc = 0;
    double l = -1e5, r = 1e5, acc = 1e-5;
    double thn = 0.3;
    
    auto ans = ODSearch::find_mininum(f, df, l, r, acc, 15, ODSearch::DESCENT);
    cout << "[DESCENT] ans:" << ans.second << " at:" << ans.first<< " acc:" << (acc / abs(thn - ans.first)) * 100 << " dev:" << max(0.0, abs(thn - ans.first) - acc) / acc * 100 << "%\n";
    ans = ODSearch::find_mininum(f, df, l, r, acc, 15, ODSearch::NEWTON, ddf);
    cout << "[NEWTON ] ans:" << ans.second << " at:" << ans.first<< " acc:" << (acc / abs(thn - ans.first)) * 100 << " dev:" << max(0.0, abs(thn - ans.first) - acc) / acc * 100 << "%\n";
    ans = ODSearch::find_mininum(f, df, l, r, acc, 15, ODSearch::SECANT, ddf);
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