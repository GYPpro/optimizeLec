/**
 * @file TOFtest.cpp
 * @brief True or False test
 */

#include <iostream>
#include <stdlib.h>
#include "core.h"
using namespace std;

int tc = 10; // test case
double dev = 0.03; // deviation

double f(double a)
{
    return (a - dev) * (a - dev);
}
int main()
{
    double l = -1,
           r = 1.0,
           acc = 0.001;
    double thn = 0.03;
    srand(1145);

    auto randint = [](int l,int r) -> int{
        return (int)((rand() * (r - l))/(RAND_MAX) + l);
    };

    while(tc --){

        dev = ((double)randint(1,100))/50.0;
        thn = dev;
        l = dev - ((double)randint(100,200))/50.0;
        r = dev + ((double)randint(100,200))/50.0;
        acc = pow(0.1,abs(randint(1,10)));

        cout << "\n----Test Cases" << 10 - tc<< "----\n";

        cout << "< search data > l:" << l << " r:" << r << " acc:" << acc <<  "\n";

        cout << "< Theoretical > ans:" << thn << " acc:"
             << "inf\n";

        double ans = lineSearch::find_mininum(f, l, r, acc, lineSearch::BINARY);
        cout << "[Binary search] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 << " dev:" << max(0.0, abs(thn - ans) - acc) / acc * 100 << "%\n";
        ans = lineSearch::find_mininum(f, l, r, acc, lineSearch::GOLDEN_RATIO);
        cout << "[0.618  method] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 << " dev:" << max(0.0, abs(thn - ans) - acc) / acc * 100 << "%\n";
        ans = lineSearch::find_mininum(f, l, r, acc, lineSearch::FIBONACCI);
        cout << "[  Fibonacci  ] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 << " dev:" << max(0.0, abs(thn - ans) - acc) / acc * 100 << "%\n";
    }
    system("pause");
}