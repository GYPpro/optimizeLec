/**
 * @file WTHtest.cpp
 * @brief 最速下降法的最坏情况：
测试
 */

#include <iostream>
#include <stdlib.h>
#include "core.h"
#include <time.h>
#include <math.h>
using namespace std;
using ODSearch::Corrdinate;

int N = 1e5;       // test case
Corrdinate dev ={0.5,0.5}; // deviation

double f(Corrdinate x)
{
    return (x.x - dev.x) * (x.x - dev.x) + (x.y - dev.y) * (x.y - dev.y)/2;
}
Corrdinate df(Corrdinate x)
{
    return Corrdinate(2 * (x.x - dev.x),(x.y - dev.y));
}
int main()
{
    int tc = 0;
    // double l = 0, r = 1.5, acc = 1e-3;
    // double thn =0.5916079778;
    Corrdinate thn = dev;
    double eps = 1e-5;
    // double ans;        cout << "\n----Test Cases" << 10 - tc << "----\n";

        cout << "<search data> eps:" << eps << "\n";
                 
        cout << "<Theoretical> ans:(" << thn.x << " " << thn.y << ") acc:"
             << "inf\n";
        double acc = eps;
            auto ans = ODSearch::find_mininum(f, df,{0.0,0.0}, ODSearch::GD,eps);
            cout << "[    G D    ] ans:" << ans.second << " df(ans)"<<df(ans.first).norm()<<" df(thn):"<<df(thn).norm()<< " at:(" << ans.first.x << " " << ans.first.y << ") acc:" << (acc / (df(thn)-df(ans.first)).norm()) * 100 << " dev:" << max(0.0, (df(thn)-df(ans.first)).norm() - acc) / acc * 100 << "%\n";
            ans = ODSearch::find_mininum(f, df,{0.0,0.0}, ODSearch::CG,eps);
            cout << "[  C G(FR)  ] ans:" << ans.second << " df(ans)"<<df(ans.first).norm()<<" df(thn):"<<df(thn).norm()<< " at:(" << ans.first.x << " " << ans.first.y << ") acc:" << (acc / (df(thn)-df(ans.first)).norm()) * 100 << " dev:" << max(0.0, (df(thn)-df(ans.first)).norm() - acc) / acc * 100 << "%\n";
            ODSearch::FRorPRP = 0;
            ans = ODSearch::find_mininum(f, df,{0.0,0.0}, ODSearch::CG,eps);
            cout << "[  C G(PBD) ] ans:" << ans.second << " df(ans)"<<df(ans.first).norm()<<" df(thn):"<<df(thn).norm()<< " at:(" << ans.first.x << " " << ans.first.y << ") acc:" << (acc / (df(thn)-df(ans.first)).norm()) * 100 << " dev:" << max(0.0, (df(thn)-df(ans.first)).norm() - acc) / acc * 100 << "%\n";
            ODSearch::FRorPRP = 1;
    // int begin = clock();
    // while (N > tc++)
    // {

    //     ans = ODSearch::find_mininum(f, df,{0.0,0.0}, ODSearch::GD,eps);
    // }
    // int end = clock();
    // tc = 0;
    // cout << "[    G D    ] cost:" << double(end-begin)/CLOCKS_PER_SEC << "s" << "\n";
    // begin = clock();
    // while (N > tc++)
    // {

    //     ans = ODSearch::find_mininum(f, df,{0.0,0.0}, ODSearch::CG,eps);
    // }
    // end = clock();
    // tc = 0;
    // cout << "[  C G(FR)  ] cost:" << double(end-begin)/CLOCKS_PER_SEC << "s" << "\n";
    // begin = clock();
    // while (N > tc++)
    // {

    //         ODSearch::FRorPRP = 0;
    //     ans =ODSearch::find_mininum(f, df,{0.0,0.0}, ODSearch::CG,eps);
        
    //         ODSearch::FRorPRP = 1;
    // }
    // end = clock();
    // tc = 10;
    // cout << "[  C G(PBD) ] cost:" << double(end-begin)/CLOCKS_PER_SEC << "s" << "\n";
    // cout << ans.first.x << "\n";
    system("pause");
}