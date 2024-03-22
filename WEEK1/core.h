/**
 * @author
 * JNU,Guo Yanpei,github@GYPpro
 * https://github.com/GYPpro/optimizeLec
 * @file
 * /optimizeLec/WEEK1/week1.h
 * @brief
 * a functional lib solving linner search problem
 */

#ifndef _LINE_SEARCH_
#define _LINE_SEARCH_

#include <math.h>
#include <algorithm>
#include <vector>

namespace lineSearch{

	const int BINARY = 1;		  //binary search method
	const int GOLDEN_RATIO = 2; //0.618 method
	const int FIBONACCI = 3;	  //Fibonacci method
 
	const double GOLDEN_RATIO_VALUE = (sqrt(5.0) - 1.0)/2.0;

	double INF_ACC_RATIO = 10; 	  //the ratio between infinitesimal unit in binary search method and given accuracy, which means inf = acc / INF_ACC_RATIO;

	/**
	 * @brief 
	 * caculate 2 value in Fibonacci Array (fb(n) and fb(n))at same time using matrix multiplication and binary lifting method
	 * use cacu_Fibonacci(n).first to get fb(n)
	 */
	std::pair<int, int> cacu_Fibonacci(int n)
	{

		if (n == 0) return std::pair<int,int>(0,1);
		auto p = cacu_Fibonacci(n / 2);
		int c = p.first * (2 * p.second - p.first);
		int d = p.first * p.first + p.second * p.second;
		if (n & 1)
			return std::pair<int,int>(d, c + d);
		else
			return std::pair<int,int>(c, d);
	}

	/**
	 * @attention 
	 * function will return -1 and throw exceptions while getting illegal input
	 * given a illegal input function is undefined behavior
	 * @brief
	 * Finding the minnum num of the input unimodal function at a given accuracy
	 * Usign segmentation interval method
	 */
	double find_mininum(
		double (*func)(double x),// inputed unimodal function
		double l,				 // left range
		double r,				 // right range
		double acc,				 // Search accuracy
		int mod 				 // Search mod
	) {
		if (l > r) {throw "Illegal Range Execption";return -1;}
		// if (l - r > acc) {throw "Too sm"}
		switch (mod)
		{
		
		case BINARY:
		{
			double inf = acc /INF_ACC_RATIO, //infinitesimal unit
				   x;					     //search index
			double cul = l,//current left range while searching
				   cur = r;//current right range while searching
			while(cur - cul > acc){
				double mid = ( cul + cur ) /2.0;
				if(func(mid + inf) > func(mid - inf)) cur = mid;//the mininum located at the left range of middle value
				else cul = mid;//otherwise
				x = cul;
			}
			return x;
		} break;

		case GOLDEN_RATIO:
		{
			double x; 	   										//search index
			double cul = l,										//current left range while searching
				   cur = r;										//current right range while searching
			double otl = func(r - GOLDEN_RATIO_VALUE * (r - l)),//overture point left
				   otr = func(l + GOLDEN_RATIO_VALUE * (r - l));//overture point right
			while(cur - cul > acc){
				if(otl > otr) //the mininum located at the right range of left overture point 
				{
					cul = cur - GOLDEN_RATIO_VALUE * (cur - cul);
					otl = otr;
					otr = func(cul + GOLDEN_RATIO_VALUE * (cur - cul));
				} else { 	  //otherwise
					cur = cul + GOLDEN_RATIO_VALUE * (cur - cul);
					otr = otl;
					otl = func(cur - GOLDEN_RATIO_VALUE * (cur - cul));
				}
				x = cul;
			}
			return x;
		} break;

		case FIBONACCI:
		{
			double x; 	   			   //search index
			double cul = l,			   //current left range while searching
				   cur = r;			   //current right range while searching
			double FN = (r - l) / acc; //inneed fibonacci value
			int N;					   //total caculate times

			std::vector<double> Fib(2,1); //Fibonacci array
			while(Fib[Fib.size()-1] < FN)
				Fib.push_back(Fib[Fib.size()-1] + Fib[Fib.size()-2]);		
			N = Fib.size() -1;
			
			double otl = func(l + Fib[N-2] / Fib[N] * (r - l)), //overture point left
				   otr = func(l + Fib[N-1] / Fib[N] * (r - l)); //overture point right
			
			for(int k = 0;k <= N - 2.0 ;k ++)
			{
				// std::cout << cul << " " << cur << " k:" << k << "\n";
				if(otl > otr) //the mininum located at the right range of left overture point 
				{
					cul = cul + Fib[N - k - 2] / Fib[N - k] * (cur - cul);
					//move left range to left overture point
					otl = otr;
					otr = func(cul + Fib[N - k - 1] / Fib[N - k] * (cur - cul));
				} else {
					cur = cul + Fib[N - k - 1] / Fib[N - k] * (cur - cul);
					otr = otl;
					otl = func(cul + Fib[N - k - 2] / Fib[N - k] * (cur - cul));
				}
				x = cul;
			}
			return x;
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
