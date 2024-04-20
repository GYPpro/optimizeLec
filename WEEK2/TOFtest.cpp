/**
 * @file TOFtest.cpp
 * @brief True or False test
 */

#include <iostream>
#include <stdlib.h>
#include "core.h"
using namespace std;

int tc = 10;       // test case
double dev = 0.03; // deviation

double f(double a)
{
    return (a - dev) * (a - dev);
}
double df(double a)
{
    return 2 * a - 2 * dev;
}
double ddf(double a)
{
    return 2.0;
}
int main()
{
    double l = -1,
           r = 1.0,
           acc = 0.001;
    double thn = 0.03;
    srand(1145);

    auto randint = [](int l, int r) -> int
    {
        return (int)((rand() * (r - l)) / (RAND_MAX) + l);
    };

    while (tc--)
    {

        dev = ((double)randint(1, 100)) / 50.0;
        thn = dev;
        l = dev - ((double)randint(100, 200)) / 50.0;
        r = dev + ((double)randint(100, 200)) / 50.0;
        acc = pow(0.1, abs(randint(1, 10)));

        cout << "\n----Test Cases" << 10 - tc << "----\n";

        cout << "< search data > l:" << l << " r:" << r << " acc:" << acc << "\n";

        cout << "< Theoretical > ans:" << thn << " acc:"
             << "inf\n";

        auto ans = ODSearch::find_mininum(f, df, ddf, l, r, acc, 0.0, ODSearch::DESCENT);
        cout << "[Binary search] ans:" << ans.second << " at:" << ans.first << " acc:" << (acc / abs(thn - ans.first)) * 100 << " dev:" << max(0.0, abs(thn - ans.first) - acc) / acc * 100 << "%\n";
        ans = ODSearch::find_mininum(f, df, ddf, l, r, acc, 0.0, ODSearch::NEWTON);
        cout << "[0.618  method] ans:" << ans.second << " at:" << ans.first << " acc:" << (acc / abs(thn - ans.first)) * 100 << " dev:" << max(0.0, abs(thn - ans.first) - acc) / acc * 100 << "%\n";
        ans = ODSearch::find_mininum(f, df, ddf, l, r, acc, 0.0, ODSearch::SECANT);
        cout << "[  Fibonacci  ] ans:" << ans.second << " at:" << ans.first << " acc:" << (acc / abs(thn - ans.first)) * 100 << " dev:" << max(0.0, abs(thn - ans.first) - acc) / acc * 100 << "%\n";
    }
    system("pause");
}