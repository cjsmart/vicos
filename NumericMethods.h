/* 
 * File:   NumericMethods.h
 * Author: cjsmart <alexey.pozin@gmail.com>
 *
 * Created on 15 Август 2011 г., 19:53
 */

#ifndef NUMERICMETHODS_H
#define	NUMERICMETHODS_H

#include "Series.h"

namespace vicos
{

class CProblem;

class CIVPMethod
{
public:
	// вычисляет один шаг численного метода решения задачи Коши
	virtual timepoint CalculateStep(time t, const timepoint& x,
		time h, CProblem* pProblem) = 0;
};

class COptimizationMethod
{
public:
	virtual timepoint Execute() = 0;
};

}


#endif	/* NUMERICMETHODS_H */

