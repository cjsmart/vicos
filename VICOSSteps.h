/* 
 * File:   VICOSSteps.h
 * Author: cjsmart <alexey.pozin@gmail.com>
 *
 * Created on 18 Сентябрь 2011 г., 13:07
 */

#ifndef VICOSSTEPS_H
#define	VICOSSTEPS_H

#include "NumericMethods.h"

namespace vicos
{

class CVICOSContext;

//////////////////////////////////////////////////////////
// CVICOSStep - общий класс для шагов метода
class CVICOSStep
{
public:
	CVICOSStep(CVICOSContext* pSetup);
	
public:
	virtual void Execute() = 0;
	CVICOSContext* GetSetup() const;
	
private:
	CVICOSContext* m_pSetup;
};

//////////////////////////////////////////////////////////
// CVICOSFirstStep - нахождение матриц коши $X(t)$, $X^{-1}(t)$
class CVICOSFirstStep : public CVICOSStep
{
public:
	CVICOSFirstStep(CVICOSContext* pSetup, CIVPMethod* pMethod);
	
public:
	virtual void Execute();
	
	seriesmatrix GetX();			// вернуть матрицу Коши
	seriesmatrix GetInversedX();	// вернуть обратную матрицу Коши
	
protected:
	void CalcStraightMatrix();
	void CalcInversedMatrix();
	
private:
	
	CIVPMethod* m_pMethod;	// метод решения ОДУ
	seriesmatrix
		m_X,
		m_Xi;
};

};

#endif	/* VICOSSTEPS_H */

