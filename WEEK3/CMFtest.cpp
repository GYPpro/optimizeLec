/**
 * @file CMFtest.cpp
 * @brief Complex Model Funtion test
 */

#include <iostream>
#include <stdlib.h>
#include "core.h"
#include <time.h>
#include <math.h>
using namespace std;
using SDsearch::Corrdinate;

int N = 50;              // test case
Corrdinate dev = {1, 1}; // deviation
int k = 1e5;

double f(Corrdinate x)
{
    return (1 - x.x) * (1 - x.x) + 3 * (x.y - x.x * x.x) * (x.y - x.x * x.x);
}
Corrdinate df(Corrdinate x)
{
    return Corrdinate(-2 * (1 - x.x) - 12.0 * (x.x * x.y - x.x * x.x * x.x), 6 * x.y - 6.0 * x.x * x.x);
}
int main()
{
    int tc = 0;
    Corrdinate thn = dev;
    double eps = 1e-5;
    cout << "<search data> eps:" << eps << "\n";

    cout << "<Theoretical> ans:(" << thn.x << " " << thn.y << ") acc:"
         << "inf\n";
    double acc = eps;
    auto ans = SDsearch::find_mininum(f, df, {0.0, 0.0}, SDsearch::GD, eps);
    cout << "[    G D    ] ans:" << ans.second << " df(ans)" << df(ans.first).norm() << " df(thn):" << df(thn).norm() << " at:(" << ans.first.x << " " << ans.first.y << ") acc:" << (acc / (df(thn) - df(ans.first)).norm()) * 100 << " dev:" << max(0.0, (df(thn) - df(ans.first)).norm() - acc) / acc * 100 << "%\n";
    ans = SDsearch::find_mininum(f, df, {0.0, 0.0}, SDsearch::CG, eps);
    cout << "[  C G(FR)  ] ans:" << ans.second << " df(ans)" << df(ans.first).norm() << " df(thn):" << df(thn).norm() << " at:(" << ans.first.x << " " << ans.first.y << ") acc:" << (acc / (df(thn) - df(ans.first)).norm()) * 100 << " dev:" << max(0.0, (df(thn) - df(ans.first)).norm() - acc) / acc * 100 << "%\n";
    SDsearch::FRorPRP = 0;
    ans = SDsearch::find_mininum(f, df, {0.0, 0.0}, SDsearch::CG, eps);
    cout << "[  C G(PBD) ] ans:" << ans.second << " df(ans)" << df(ans.first).norm() << " df(thn):" << df(thn).norm() << " at:(" << ans.first.x << " " << ans.first.y << ") acc:" << (acc / (df(thn) - df(ans.first)).norm()) * 100 << " dev:" << max(0.0, (df(thn) - df(ans.first)).norm() - acc) / acc * 100 << "%\n";
    SDsearch::FRorPRP = 1;
    int begin = clock();
    while (N > tc++)
    {

        ans = SDsearch::find_mininum(f, df, {0.0, 0.0}, SDsearch::GD, eps);
    }
    int end = clock();
    tc = 0;
    cout << "[    G D    ] cost:" << double(end - begin) / CLOCKS_PER_SEC << "s" << "\n";
    begin = clock();
    while (N > tc++)
    {

        ans = SDsearch::find_mininum(f, df, {0.0, 0.0}, SDsearch::CG, eps);
    }
    end = clock();
    tc = 0;
    cout << "[  C G(FR)  ] cost:" << double(end - begin) / CLOCKS_PER_SEC << "s" << "\n";
    begin = clock();
    while (N > tc++)
    {

        SDsearch::FRorPRP = 0;
        ans = SDsearch::find_mininum(f, df, {0.0, 0.0}, SDsearch::CG, eps);

        SDsearch::FRorPRP = 1;
    }
    end = clock();
    tc = 10;
    cout << "[  C G(PBD) ] cost:" << double(end - begin) / CLOCKS_PER_SEC << "s" << "\n";
    cout << ans.first.x << "\n";
    system("pause");
}