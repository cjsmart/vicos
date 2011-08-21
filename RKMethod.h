/* 
 * File:   RKMethod.h
 * Author: pozin
 *
 * Created on 15 Август 2011 г., 15:18
 */

#ifndef RKMETHOD_H
#define	RKMETHOD_H

#include "Series.h"
#include "NumericMethods.h"

namespace iode
{

class CRungeKutta4Method : public CIVPMethod
{
public:
	// вычисляет один шаг численного метода решения задачи Коши
	virtual timepoint CalculateStep(time t, const timepoint& x, 
		time h, CProblem* pProblem);
};

};

#endif	/* RKMETHOD_H */

