#include <iostream>
#include "week1.h"
using namespace std;
double f(double a)
{

}
int main()
{
    auto x = f;
    lineSearch::find_mininum(f,1,2,0.001,lineSearch::BINARY);
}