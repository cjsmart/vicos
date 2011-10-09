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
	
	const matrixseries& GetX() const;			// вернуть матрицу Коши
	const matrixseries& GetInversedX() const;	// вернуть обратную матрицу Коши
	
protected:
	void CalcStraightMatrix();
	void CalcInversedMatrix();
	
private:
	
	CIVPMethod* m_pMethod;	// метод решения ОДУ
	matrixseries
		m_X,
		m_Xi;
};


//////////////////////////////////////////////////////////
// CVICOSSecondStep - нахождение начальной точки $c$
class CVICOSSecondStep : public CVICOSStep
{
public:
	CVICOSSecondStep(CVICOSContext* pSetup, CVICOSFirstStep* pFirstStep);
	
public:
	virtual void Execute();
	
	const timepoint& GetStartPoint() const;		// получить начальную точку
	
private:
	
	CVICOSFirstStep* m_pFirstStep;	// первый шаг с матрицами
	timepoint m_StartPoint;
};

};

#endif	/* VICOSSTEPS_H */

