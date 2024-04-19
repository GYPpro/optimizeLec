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
	const int SECANT = 2;         //割线法
	const int NEWTON = 3;	      //牛顿法
    
    	/**
	 * @attention 
	 * function will return -1 and throw exceptions while getting illegal input
	 * @brief
	 * Finding the minnum num of a One-dimensional function
	 */
	double find_mininum(
		double (*func)(double x),  // 原函数
		double (*dfunc)(double x), // 一阶导函数
		double (*ddfunc)(double x) = nullptr,// 二阶导函数(可选)
		double l,				   // 下界
		double r,				   // 上界
		double acc,				   // 搜索精度
        double x,                  // 初始点
		int mod 				   // 搜索方法
	) {
		if (l > r) {throw "Illegal Range Execption";return -1;}
        if (x < l || x > r) {throw "Illegal Initial Value";return -1;}
        if (mod == NEWTON && ddfunc == nullptr) {throw "Derivative Function NOT Provided";return -1;}
        switch (mod)
        {
        case DESCENT:
        {

        } break;

        case SECANT:
        {

        } break;
        
        case NEWTON:
        {

        } break;
        
		default:
		{
			throw "Unexpection Search Mod Exception";
			return -1;
		}
			break;
		}
		throw "Unknown Exception";
		return -1;
    }
}
#endif
