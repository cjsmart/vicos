#include "VICOSSteps.h"
#include "VICOS.h"
#include "Externals.h"

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
	CProblem* pProb = pSetup->GetProblem();
	long iDim = pSetup->GetDim();
	time
		tStart = pSetup->GetStart(),
		tFinish = pSetup->GetFinish(),
		tStep = pSetup->GetNStep();
	
	long iStepCount = 
		long((tFinish - tStart) / tStep) + 1;
	
	m_X.Create(iStepCount + 1);
	
	for (long i = 0; i <= iStepCount; i++)
	{
		matrixpoint& Xt = m_X[i];
		
		Xt.Create(iDim, iDim);
	}
	
	// идем по столбцам $iCol$, фундаментальной матрицы
	for (long iCol = 0; iCol < iDim; iCol++)
	{	
		timepoint X0;
		X0.Create(iDim);

		for (long i = 0; i < iDim; i++)
		{
			X0[i] = (i == iCol) ? 1 : 0;
		}

		long i = 0;

		for (time tCur = tStart; tCur <= tFinish; tCur += tStep)
		{
			X0 = m_pMethod->CalculateStep(tCur, X0, tStep, pProb);
			
			matrixpoint& mpCurrent = m_X[i++];
			
			for (long iRow = 0; iRow < iDim; iRow++)
			{
				mpCurrent(iRow, iCol) = X0[iRow];
			}
		}
	}
	
	for (long i = 0; i <= iStepCount; i++)
	{
		std::cout << "t=" << (tStart + tStep * i) << std::endl;
		std::cout << "matrix=" << std::endl << m_X[i] << std::endl << std::endl;
	}
}

void CVICOSFirstStep::CalcInversedMatrix()
{
	CVICOSContext* pSetup = GetSetup();
	//CProblem* pProb = pSetup->GetProblem();
	long iDim = pSetup->GetDim();
	time
		tStart = pSetup->GetStart(),
		tFinish = pSetup->GetFinish(),
		tStep = pSetup->GetNStep();
	
	long iStepCount = 
		long((tFinish - tStart) / tStep) + 1;
	
	m_Xi.Create(m_X.GetCount());
	
	for (long i = 0; i <= iStepCount; i++)
	{
		matrixpoint 
			&dest = m_Xi[i],
			&src = m_X[i];
		
		dest.Create(iDim, iDim);
		
		if (iDim == 1)
		{
			dest(0, 0) = 1 / src(0, 0);
		}
		else
		{
			MatrixInversion(src.GetData(), iDim, dest.GetData());
		}
		
		std::cout << "t=" << (tStart + tStep * i) << std::endl;
		std::cout << "imatrix=" << std::endl << m_Xi[i] << std::endl << std::endl;
	}
}

const matrixseries& CVICOSFirstStep::GetX() const	// вернуть матрицу Коши
{
	return m_X;
}

const matrixseries& CVICOSFirstStep::GetInversedX() const	// вернуть обратную матрицу Коши
{
	return m_Xi;
}


//////////////////////////////////////////////////////////
// CVICOSSecondStep - нахождение начальной точки $c$
CVICOSSecondStep::CVICOSSecondStep(CVICOSContext* pSetup, CVICOSFirstStep* pFirstStep) : 
				CVICOSStep(pSetup), m_pFirstStep(pFirstStep)
{
	
}

void CVICOSSecondStep::Execute()
{
	// сделать структуру для хранения ограничений
}

const timepoint& GetStartPoint() const
{
	return m_StartPoint;
}

};