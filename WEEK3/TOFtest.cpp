/**
 * @file TOFtest.cpp
 * @brief True or False test
 */

#include <iostream>
#include <stdlib.h>
#include "core.h"
using namespace std;

using SDsearch::Corrdinate;

int tc = 1;       // test case
Corrdinate dev = 0.03; // deviation

double f(Corrdinate x)
{
    return (x.x - dev.x) * (x.x - dev.x) + (x.y - dev.y) * (x.y - dev.y);
}
Corrdinate df(Corrdinate x)
{
    return Corrdinate(2 * (x.x - dev.x), 2 * (x.y - dev.y));
}
int main()
{
    double acc = 0.001;
    Corrdinate thn = dev;
    double eps = 1e-5;
    srand(1145);

    auto randint = [](int l, int r) -> int
    {
        return (int)((rand() * (r - l)) / (RAND_MAX) + l);
    };

    while (tc--)
    {

        if(tc == 5)
            tc -= 0;
        dev = {((double)randint(1, 100)) / 50.0,((double)randint(1, 100)) / 50.0};
        thn = dev;
        eps = pow(0.1, abs(randint(1, 10)));

        cout << "\n----Test Cases" << 10 - tc << "----\n";

        cout << "<search data> eps:" << eps << "\n";
                 
        cout << "<Theoretical> ans:(" << thn.x << " " << thn.y << ") acc:"
             << "inf\n";
        acc = eps;
        try
        {        
            auto ans = SDsearch::find_mininum(f, df,{0.0,0.0}, SDsearch::GD,eps);
            cout << "[    G D    ] ans:" << ans.second << " df(ans)"<<df(ans.first).norm()<<" df(thn):"<<df(thn).norm()<< " at:(" << ans.first.x << " " << ans.first.y << ") acc:" << (acc / (df(thn)-df(ans.first)).norm()) * 100 << " dev:" << max(0.0, (df(thn)-df(ans.first)).norm() - acc) / acc * 100 << "%\n";
            ans = SDsearch::find_mininum(f, df,{0.0,0.0}, SDsearch::CG,eps);
            cout << "[  C G(FR)  ] ans:" << ans.second << " df(ans)"<<df(ans.first).norm()<<" df(thn):"<<df(thn).norm()<< " at:(" << ans.first.x << " " << ans.first.y << ") acc:" << (acc / (df(thn)-df(ans.first)).norm()) * 100 << " dev:" << max(0.0, (df(thn)-df(ans.first)).norm() - acc) / acc * 100 << "%\n";
            SDsearch::FRorPRP = 0;
            ans = SDsearch::find_mininum(f, df,{0.0,0.0}, SDsearch::CG,eps);
            cout << "[  C G(PBD) ] ans:" << ans.second << " df(ans)"<<df(ans.first).norm()<<" df(thn):"<<df(thn).norm()<< " at:(" << ans.first.x << " " << ans.first.y << ") acc:" << (acc / (df(thn)-df(ans.first)).norm()) * 100 << " dev:" << max(0.0, (df(thn)-df(ans.first)).norm() - acc) / acc * 100 << "%\n";
            SDsearch::FRorPRP = 1;
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
        

        
        // cout << "[SECANT ] ans:" << ans.second << " at:" << ans.first << " acc:" << (acc / abs(thn - ans.first)) * 100 << " dev:" << max(0.0, abs(thn - ans.first) - acc) / acc * 100 << "%\n";
    }
    system("pause");
}