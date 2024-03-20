#include <iostream>
#include "week1.h"
using namespace std;
double f(double a)
{
    return (a-0.03) * (a-0.03);
}
int main()
{
    double l = -1,
           r = 1.0,
           acc = 0.001;
    double thn = 0.03;
    cout << lineSearch::find_mininum(f,l,r,acc,lineSearch::FIBONACCI) << "\n";
    cout << "-- theoretical minimum:0.03000 -- acc:0.001 --\n";
    double ans = lineSearch::find_mininum(f,l,r,acc,lineSearch::BINARY);
    cout << "[Binary search] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 <<"%\n";
    ans = lineSearch::find_mininum(f,l,r,acc,lineSearch::GOLDEN_RATIO);
    cout << "[0.618  method] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 <<"%\n";
    ans = lineSearch::find_mininum(f,-1,1,acc,lineSearch::FIBONACCI);
    cout << "[  Fibonacci  ] ans:" << ans << " acc:" << (acc / abs(thn - ans)) * 100 <<"%\n";
    system("pause");
}