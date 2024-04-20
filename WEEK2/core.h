/**
 * @author
 * JNU,Guo Yanpei,github@GYPpro
 * https://github.com/GYPpro/optimizeLec
 * @file
 * /optimizeLec/WEEK2/core.h
 * @brief
 * a functional lib solving One-dimensional search
 */

#ifndef _ONE_DIMENSIONAL_SEARCH_
#define _ONE_DIMENSIONAL_SEARCH_

#include <math.h>
#include <algorithm>
#include <vector>

namespace ODSearch{
    
	const int DESCENT = 1;		  //最速下降法
	const int NEWTON = 2;	      //牛顿法
	const int SECANT = 3;         //割线法
    
	const double _inf = 1e299;	  //最坏边界
	const double _acc = 1e-3;	  //默认精度

	
	
	// /*
	//  * @britf
	//  * Set Descent Rate of DESCTNE method
	//  * */
	// void setDescentAlpha(double _a)
	// {
	// 	alpha = _a;
	// }

    	/**
	 * @attention 
	 * function will return -1 and throw exceptions while getting illegal input
	 * @brief
	 * Finding the minnum num of a One-dimensional function
	 */
	std::pair<double,double> find_mininum(
		double (*func)(double x),  // 原函数
		double (*dfunc)(double x), // 一阶导函数
		double (*ddfunc)(double x) = nullptr,// 二阶导函数(可选)
		double l = -_inf,				   // 下界
		double r = _inf,				   // 上界
		double acc = _acc,				   // 搜索精度
        double x = 0.0,                    // 初始点
		int mod = DESCENT				   // 搜索方法
	) {
		if (l > r) {throw "Illegal Range Execption";return {-1,-1};}
        if (x < l || x > r) {throw "Illegal Initial Value";return {-1,-1};}
        if (mod == NEWTON && ddfunc == nullptr) {throw "Derivative Function NOT Provided";return {-1,-1};}
        switch (mod)
        {
        case DESCENT:
        {
			double alpha = 1.0;//步长因子
			double curx = x;//当前搜索点
			double fmin = func(x);//当前函数值最小值
			double grad = dfunc(x);//当前梯度

			while(abs(grad) > acc)
			{
				while(!(func(curx - alpha * grad) < func(curx)))
					alpha = alpha / 2.0;
				fmin = func(curx - alpha * grad);
				curx -= alpha * grad;
				grad = dfunc(curx);
			}
			return {curx,fmin};
        } break;

        case NEWTON:
        {
			/*
			 *@brief 计算近似二阶泰勒的 build in lambda function 
			*/
			auto Taylor = [&](double xk) -> double
			{
				return dfunc(xk) / (ddfunc(xk) * ddfunc(xk));
			};

			double curx = x;//当前搜索点
			double fmin = func(x);//当前函数值最小值
			double grad = dfunc(x);//当前梯度

			while(abs(grad) > acc)
			{
				fmin = func(curx - Taylor(curx));
				curx -= Taylor(curx);
				grad = dfunc(curx);
			}
			return {curx,fmin};
        } break;

        case SECANT:
        {

			double curx = x;//当前搜索点
			double prfx = (l + x)/ 2.0;//上一个搜索点
			double fmin = func(x);//当前函数值最小值
			double grad = dfunc(x);//当前梯度

			/*
			 *@brief 计算替代二阶导的割线斜率的 build in lambda function 
			*/
			auto getSec = [&]() -> double{
				return (curx - prfx) * dfunc(curx) / (dfunc(curx) - dfunc(prfx));
			};


			while(abs(grad) > acc)
			{
				fmin = func(curx - getSec());
				curx -= getSec();
				grad = dfunc(curx);
			}
			return {curx,fmin};

        } break;
        
        
		default:
		{
			throw "Unexpection Search Mod Exception";
			return {-1,-1};
		}
			break;
		}
		throw "Unknown Exception";
		return {-1,-1};
    }
}
#endif
