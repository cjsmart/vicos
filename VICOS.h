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
// CVICOSSetup - настройки решателя
class CVICOSContext
{
public:		// construction
	CVICOSContext(long iDim, CProblem* pProblem, 
		time tStart, time tFinish, bool bSeizeProblem = true);
	
	virtual ~CVICOSContext();
	
public:		// access
	time GetStart() const { return m_tStart; }
	void SetStart(time tValue) { m_tStart = tValue; }
	
	time GetFinish() const { return m_tFinish; }
	void SetFinish(time tValue) { m_tFinish = tValue; }
	
	time GetNStep() const { return m_tNStep; }
	void SetNStep(time tValue) { m_tNStep = tValue; }
	
	time GetVStep() const { return m_tVStep; }
	void SetVStep(time tValue) { m_tVStep = tValue; }
	
	CProblem* GetProblem() const { return m_pProblem; }
	
	long GetDim() const { return m_iDim; }
	
private:	// fields
	time m_tStart, m_tFinish;	// integration interval
	time 
		m_tNStep,				// non-validated integration step
		m_tVStep;				// maximum validated integration step
	
	long m_iDim;				// problem dimenstions count
	
	CProblem* m_pProblem;		// problem for VICOS
	
	bool m_bSeize;				// delete problem object in destructor
};


//////////////////////////////////////////////////////////
// CVICOS - класс общего решателя
class CVICOS
{
public:
	CVICOS(CVICOSContext* pSetup, CIVPMethod* pIVP, 
		COptimizationMethod* pOptim);
	
	void Execute();		// execute VICOS
	
protected:
	void CalculateCauchyMatrices();	// 1st step
	void FindStartPoint();			// 2nd step
	void CalculateValidated();		// 3rd step
	
private:
	CVICOSContext* m_pSetup;
	CIVPMethod* m_pIVPMethod; // first step method
	COptimizationMethod* m_pOptMethod; // second step method
};

}

#endif	/* VICOS_H */

