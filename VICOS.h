/* 
 * File:   VICOS.h
 * Author: cjsmart <alexey.pozin@gmail.com>
 *
 * Created on 23 Август 2011 г., 23:57
 */

#ifndef VICOS_H
#define	VICOS_H

#include "Problem.h"
#include "NumericMethods.h"

namespace vicos
{


//////////////////////////////////////////////////////////
// CVICOS - класс общего решателя
class CVICOS
{
public:
	CVICOS(CProblem* pProblem, CIVPMethod* pIVP, 
		COptimizationMethod* pOptim);
	
	void Execute();		// execute VICOS
	
protected:
	void CalculateCauchyMatrices();	// 1st step
	void FindStartPoint();			// 2nd step
	void CalculateValidated();		// 3rd step
	
private:
	CProblem* m_pProblem;
	CIVPMethod* m_pIVPMethod; // first step method
	COptimizationMethod* m_pOptMethod; // second step method
};

}

#endif	/* VICOS_H */

