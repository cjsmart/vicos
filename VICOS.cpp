#include "VICOS.h"

namespace vicos
{

CVICOS::CVICOS(CProblem* pProblem, CIVPMethod* pIVP, COptimizationMethod* pOptim) : 
	m_pIVPMethod(pIVP), m_pProblem(pProblem), m_pOptMethod(pOptim)
{
	
}

void CVICOS::Execute()
{
	CalculateCauchyMatrices();
	FindStartPoint();
	CalculateValidated();
}

void CVICOS::CalculateCauchyMatrices()	// 1st step
{
	
}

void CVICOS::FindStartPoint()			// 2nd step
{

}

void CVICOS::CalculateValidated()		// 3rd step
{
	
}

}
