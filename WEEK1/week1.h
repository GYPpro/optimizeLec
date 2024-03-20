/**
 * @auther
 * JNU,Guo Yanpei,github@GYPpro
 * @brief
 * a functional lib solving linner search problem
 */



#ifndef _LINE_SEARCH_
#define _LINE_SEARCH_

#include <math.h>
#include <algorithm>

namespace lineSearch{

	const int _BINARY_ = 1;		  //binary search method
	const int _GOLDEN_RATIO_ = 2; //0.618 method
	const int _FIBONACCI_ = 3;	  //Fibonacci method

	double find_mininum(
			double (*func)(double x),// inputed unimodal function
			double l,				 // left range
			double r,				 // right range
			double acc,				 // Search accuracy
			int mod 				 // Search mod
		)
	/**
	 * @auther
	 * JNU,Guo Yanpei,github@GYPpro
	 * @attention 
	 * function will return -1 and throw exceptions while getting illegal input
	 * given a illegal input function is undefined behavior
	 * @brief
	 * Finding the minnum num of the input unimodal function at a given accuracy
	 */
	{
		if (l > r) {throw "Illegal Range Execption";return -1;}
		// if (l - r > acc) {throw "Too sm"}
		switch (mod)
		{
		case _BINARY_:
		{
			double inf = sqrt(acc) /10.0, //infinitesimal unit
				   x;				  	  //search index
			double cul = l,//current left range while searching
				   cur = r;//current right range while searching
			while(cur - cul > acc){
				double mid = ( cul + cur ) /2.0;
				x = mid;
				if(func(mid + inf) > func(mid - inf)) cur = mid;//the mininum located at the left range of middle value
				else cul = mid;//otherwise

			}

		
		} break;
		case _GOLDEN_RATIO_:
		{

		} break;
		case _FIBONACCI_:
		{

		} break;
		
		default:
		{
			throw "Unexpection Search Mod Exception";
		}
			break;
		}
	}
}

#endif
