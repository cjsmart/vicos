/* 
 * File:   Problem.h
 * Author: cjsmart <alexey.pozin@gmail.com>
 *
 * Created on 15 Август 2011 г., 16:54
 */

#ifndef PROBLEM_H
#define	PROBLEM_H

#include "Series.h"

namespace vicos
{

class CProblem
{
public:
	// вычисляет значение $\frac{dx}{dt}$ для исходной задачи
	virtual timepoint CalculateDX(time t, const timepoint& x) = 0;

	// вычисляет значение $f(t)$ для исходной задачи
	virtual timepoint CalculateFt(time t) = 0;

	// вычисляет значение $\frac{dx}{dt}$ для задачи нахождения 
	// фундаментальной матрицы Коши, если bInv == true, то
	// посчитает выражение для обратной матрицы
	virtual timepoint CalculateDXF(time t, const timepoint& x, bool bInv = false) = 0;
};

}

#endif	/* PROBLEM_H */

