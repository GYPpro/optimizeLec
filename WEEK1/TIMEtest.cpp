#include <iostream>
#include <stdlib.h>
#include "week1.h"
using namespace std;

int tc = 10;       // test case
double dev = 0.03; // deviation

double f(double x)
{
    if (x >= -0.48)
        return sqrt(x + 1.03);
    else
        return sqrt(0.07 - x);
}
int main()
{

    double l = -1e5, r = 1e5, acc = 0.00001;
    double thn = -0.48;
    double ans;
    ans = lineSearch::find_mininum(f, l, r, acc, lineSearch::BINARY);
    cout << "[Binary search] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 << " dev:" << max(0.0, abs(thn - ans) - acc) / acc * 100 << "%\n";
    ans = lineSearch::find_mininum(f, l, r, acc, lineSearch::GOLDEN_RATIO);
    cout << "[0.618  method] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 << " dev:" << max(0.0, abs(thn - ans) - acc) / acc * 100 << "%\n";
    ans = lineSearch::find_mininum(f, l, r, acc, lineSearch::FIBONACCI);
    cout << "[  Fibonacci  ] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 << " dev:" << max(0.0, abs(thn - ans) - acc) / acc * 100 << "%\n";
    while (tc--)
    {

        lineSearch::find_mininum(f, l, r, acc, lineSearch::BINARY);

        lineSearch::find_mininum(f, l, r, acc, lineSearch::GOLDEN_RATIO);

        lineSearch::find_mininum(f, l, r, acc, lineSearch::FIBONACCI);
    }
    system("pause");
}