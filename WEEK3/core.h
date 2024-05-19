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

#include <iostream>
#include <initializer_list>


namespace ODSearch{
    
	const int GD = 1;		  //最速下降法
    const int CG = 2;		  //共轭梯度法

	const double _epsilon = 1e-3;	  //容限


	/**
	 * @brief
	 * a Corrdinate class as 2D vector
	 */
	class Corrdinate
	{
	public:
		double x;
		double y;

		Corrdinate(double x = 0,double y = 0):x(x),y(y){}

		Corrdinate(std::initializer_list<double> l)
		{
			auto it = l.begin();
			x = *it;
			y = *(++it);
		}

		Corrdinate operator-(Corrdinate c)
		{
			return Corrdinate(x - c.x,y - c.y);
		}

		//数乘
		Corrdinate operator*(double a)
		{
			return Corrdinate(x * a,y * a);
		}

		//加
		Corrdinate operator+(Corrdinate c)
		{
			return Corrdinate(x + c.x,y + c.y);
		}

		//点乘
		double operator*(Corrdinate c)
		{
			return x * c.x + y * c.y;
		}
		
		//求模
		double norm()
		{
			return sqrt(x * x + y * y);
		}

		//单位化
		Corrdinate normalize()
		{
			double n = norm();
			return Corrdinate(x / n,y / n);
		}

		//除
		Corrdinate operator/(double a)
		{
			return Corrdinate(x / a,y / a);
		}

		Corrdinate operator+=(const Corrdinate c)
		{
			x += c.x;
			y += c.y;
			return *this;
		}

		Corrdinate operator-=(const Corrdinate c)
		{
			x -= c.x;
			y -= c.y;
			return *this;
		}

		Corrdinate operator*=(double a)
		{
			x *= a;
			y *= a;
			return *this;
		}

		Corrdinate operator/=(double a)
		{
			x /= a;
			y /= a;
			return *this;
		}

	};
	

	double abs(Corrdinate c)
	{
		return sqrt(c.x * c.x + c.y * c.y);
	}

    /**
	 * @attention 
	 * function will return -1 and throw exceptions while getting illegal input
	 * @brief
	 * Finding the minnum num of a One-dimensional function
	 */
	std::pair<Corrdinate,double> find_mininum(
		double (*func)(Corrdinate), //目标函数
		Corrdinate (*dfunc)(Corrdinate),//目标函数梯度
		Corrdinate x_0, //初始搜索点
		int mod = GD, //搜索模式
		double epsilon = _epsilon //容限
	) {
		
        switch (mod)
        {
        case GD:
        {
			double alpha = 0.1;//初始步长因子
			Corrdinate curx = x_0;//当前搜索点
			double fmin = func(x_0);//当前函数值最小值
			Corrdinate grad = dfunc(x_0);//当前梯度

			// int tc = 0;
			while(grad.norm() > epsilon)
			{
				//二分线性搜索确定可选步长因子
				while(!(func(curx - grad * alpha) < func(curx)))
					alpha = alpha / 2.0;
				fmin = func(curx - grad * alpha);
				curx -= grad * alpha;
				grad = dfunc(curx);
				alpha = 0.1;
				// tc ++;
			}
			// std::cout << "tc:" << tc << "\n";
			return {curx,fmin};
        } break;

        case CG:
        {
			
        } break;

        
		default:
		{
			throw "Unexpection Search Mod Exception";
			return {{0,0},-1};
		}
			break;
		}
		throw "Unknown Exception";
		return {{0,0},-1};
    }
}
#endif
