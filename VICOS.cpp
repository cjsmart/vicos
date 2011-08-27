#include "VICOS.h"

namespace vicos
{


//////////////////////////////////////////////////////////
// CVICOS - класс общего решателя
CVICOS::CVICOS(CVICOSSetup* pSetup, CIVPMethod* pIVP, COptimizationMethod* pOptim) : 
	m_pSetup(pSetup), m_pIVPMethod(pIVP), m_pOptMethod(pOptim)
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
	// 1.1 Calculate straight matrix
	timepoint X0;
	
	X0.resize(m_pSetup->GetDim());
	
	for (timepoint::iterator itt = X0.begin(); itt != X0.end(); ++itt)
	{
		*itt = 1;
	}
	
	time
		tStart = m_pSetup->GetStart(),
		tFinish = m_pSetup->GetFinish(),
		tStep = m_pSetup->GetNStep();
	
	CProblem* pProb = m_pSetup->GetProblem();

	for (time tCur = tStart; tCur <= tFinish; tCur += tStep)
	{
		X0 = m_pIVPMethod->CalculateStep(tCur, X0, tStep, pProb);

		// FIXME: debug output
		std::cout << X0 << std::endl;
	}
	
	// 1.2 Calculate reverse matrix
}

void CVICOS::FindStartPoint()			// 2nd step
{

}

void CVICOS::CalculateValidated()		// 3rd step
{
	
}


//////////////////////////////////////////////////////////
// CVICOSSetup - настройки решателя
CVICOSSetup::CVICOSSetup(long iDim, CProblem* pProblem, 
	time tStart, time tFinish, bool bSeizeProblem /*= true*/) : 
	m_iDim(iDim), m_pProblem(pProblem), m_tStart(tStart), 
	m_tFinish(tFinish), m_bSeize(bSeizeProblem)
{
	m_tNStep = m_tVStep = (tFinish - tStart) / 100;
}
	
CVICOSSetup::~CVICOSSetup()
{
	if (m_bSeize && m_pProblem != NULL)
	{
		delete m_pProblem;
		m_pProblem = NULL;
	}
}

}
