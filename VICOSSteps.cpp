#include "VICOSSteps.h"
#include "VICOS.h"

namespace vicos
{


//////////////////////////////////////////////////////////
// CVICOSStep - общий класс для шагов метода
CVICOSStep::CVICOSStep(CVICOSContext* pSetup) : 
	m_pSetup(pSetup)
{
	
}

CVICOSContext* CVICOSStep::GetSetup() const 
{ 
	return m_pSetup;
}


/* ==========================================================
 * класс для первого шага - нахождения матриц КОШИ
 * он должен настраиваться на уравнение и метод расчета,
 * вообще надо настраивать так любой метод
 * ==========================================================
 */

CVICOSFirstStep::CVICOSFirstStep(CVICOSContext* pSetup, CIVPMethod* pMethod) : 
	CVICOSStep(pSetup), m_pMethod(pMethod)
{
	
}

void CVICOSFirstStep::Execute()
{
	CalcStraightMatrix();
	CalcInversedMatrix();
}

void CVICOSFirstStep::CalcStraightMatrix()
{	
	CVICOSContext* pSetup = GetSetup();
	long iDim = pSetup->GetDim();
	
	m_X.resize(iDim);
	
	for (long k = 0; k < iDim; k++)
	{	
		timepoint X0;
		X0.resize(iDim);

		for (timepoint::iterator itt = X0.begin(); itt != X0.end(); ++itt)
		{
			*itt = itt.index() == k ? 1 : 0;
		}

		time
			tStart = pSetup->GetStart(),
			tFinish = pSetup->GetFinish(),
			tStep = pSetup->GetNStep();

		CProblem* pProb = pSetup->GetProblem();

		m_X[k].resize(long((tFinish - tStart) / tStep) + 1, true);
		long i = 0;

		for (time tCur = tStart; tCur <= tFinish; tCur += tStep)
		{
			X0 = m_pMethod->CalculateStep(tCur, X0, tStep, pProb);

			m_X[k][i++] = X0;

			// FIXME: debug output
			std::cout << "col=" << k << ", step=" << tCur << ": " 
				<< m_X[k][i-1] << std::endl;
		}
	}
}

void CVICOSFirstStep::CalcInversedMatrix()
{
	/*timepoint X0;
	
	CVICOSContext* pSetup = GetSetup();
	
	X0.resize(pSetup->GetDim());
	
	for (timepoint::iterator itt = X0.begin(); itt != X0.end(); ++itt)
	{
		*itt = 1;
	}
	
	time
		tStart = pSetup->GetStart(),
		tFinish = pSetup->GetFinish(),
		tStep = pSetup->GetNStep();
	
	CProblem* pProb = pSetup->GetProblem();
	
	m_X.resize(long((tFinish - tStart) / tStep) + 1, true);
	long i = 0;

	for (time tCur = tStart; tCur <= tFinish; tCur += tStep)
	{
		X0 = m_pMethod->CalculateStep(tCur, X0, tStep, pProb);
		
		m_X[i++] = X0;
		
		// FIXME: debug output
		std::cout << "i_step " << tCur << ": " << m_X[i-1] << std::endl;
	}*/
}

seriesmatrix CVICOSFirstStep::GetX()	// вернуть матрицу Коши
{
	return m_X;
}
seriesmatrix CVICOSFirstStep::GetInversedX()	// вернуть обратную матрицу Коши
{
	return m_Xi;
}

};