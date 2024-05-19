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
#include <string>
#include <iostream>
#include <initializer_list>

#include <fstream>

class Logger {
private:
    std::ofstream logFile;
public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::out); // 打开文件用于写入，fugai
        if (!logFile.is_open()) {
            std::cerr << "Error opening log file: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(const std::string& message) {
        // 输出到控制台
        // std::cout << message << std::endl;

        // 写入到日志文件
        logFile << message << std::endl;
    }
};

// int main() {
//     Logger logger("app.log"); // 创建日志对象，并指定日志文件名

//     // 示例：记录一些信息
//     logger.log("Starting application...");
//     // ... 应用程序的其他代码 ...

//     return 0;
// }


namespace ODSearch{
    
	const int GD = 1;		  //最速下降法
    const int CG = 2;		  //共轭梯度法

	const double _epsilon = 1e-3;	  //默认容限

	int FRorPRP = 1; // 共轭梯度方向公式选择，1为FR，0为PBD


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

		Corrdinate operator-()
		{
			return Corrdinate(-x,-y);
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
	
	/**
	 * @brief
	 * set the FRorPRP
	 */
	void setFRorPRP(int mod)
	{
		FRorPRP = mod;
	}

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
		if(epsilon <= 1e-14) {throw "Epsilon out of Precision Exception";return {{0,0},-1};}
        switch (mod)
        {
        case GD:
        {
			Logger logger("WEEK3\\GD.log");
			int k = 0;//迭代次数
			double alpha = 0.1;//初始步长因子
			Corrdinate curx = x_0;//当前搜索点
			double fmin = func(x_0);//当前函数值最小值
			Corrdinate grad = dfunc(x_0);//当前梯度

			// int tc = 0;
			while(grad.norm() > epsilon)
			{
				std::string Log; 
				Log += std::to_string(curx.x);
				Log += " ";
				Log += std::to_string(curx.y);
				logger.log(Log);
				if(k > 10 && (curx.norm() < 1e-20 || curx.norm() > 1e20)) {throw "Coordinate out of Precision Warning";}

				//二分线性搜索确定可选步长因子
				while(!(func(curx - grad * alpha) < func(curx)))
					alpha = alpha / 2.0;
				fmin = func(curx - grad * alpha);
				curx -= grad * alpha;
				grad = dfunc(curx);
				alpha = 0.1;
				k ++;
				// tc ++;
			}
			// std::cout << "tc:" << tc << "\n";
			return {curx,fmin};
        } break;

        case CG:
        {
			int k = 0;//迭代次数
			double alpha = 0.1;//初始步长因子
			Corrdinate curx = x_0;//当前搜索点
			double fmin = func(x_0);//当前函数值最小值
			Corrdinate grad_k = dfunc(x_0);//当前梯度
			Corrdinate grad_k_1 = grad_k;//上一次梯度
			Corrdinate d_k = -grad_k;//搜索方向
			Corrdinate d_k_1 = d_k;//上一次搜索方向

			Logger logger(std::string("WEEK3\\CG_") + (FRorPRP?"FR":"PRP") + ".log");
			while(grad_k.norm() > epsilon)
			{
				std::string Log; 
				Log += std::to_string(curx.x);
				Log += " ";
				Log += std::to_string(curx.y);
				logger.log(Log);
				if(k > 10 && (curx.norm() < 1e-20 || curx.norm() > 1e20)) {throw "Coordinate out of Precision Warning";}

				if(k == 0)
				{
					//二分线性搜索确定可选步长因子
					while(!(func(curx + d_k * alpha) < func(curx)))
						alpha = alpha / 2.0;
					fmin = func(curx + d_k * alpha);
					curx += d_k * alpha;
					grad_k_1 = grad_k;
					grad_k = dfunc(curx);
					d_k = -grad_k;
					alpha = 0.1;
				}
				else
				{
					if (FRorPRP == 1)
					{
						//FR公式
						double beta = (grad_k * grad_k) / (grad_k_1 * grad_k_1);
						d_k = -grad_k + d_k * beta;
					}
					else
					{
						//PRP公式
						double beta = (grad_k * (grad_k - grad_k_1)) / (grad_k_1 * grad_k_1);
						d_k = -grad_k + d_k * beta;
					}
					
					//二分线性搜索确定可选步长因子
					while(!(func(curx + d_k * alpha) < func(curx)))
						alpha = alpha / 2.0;
					fmin = func(curx + d_k * alpha);
					curx += d_k * alpha;
					grad_k_1 = grad_k;
					grad_k = dfunc(curx);
					d_k = -grad_k;
					alpha = 0.1;
				}
				k ++;
			}
			return {curx,fmin};
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
