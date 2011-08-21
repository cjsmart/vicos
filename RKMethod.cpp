#include "RKMethod.h"
#include "Problem.h"

namespace iode
{

// вычисляет один шаг численного метода решения задачи Коши

timepoint CRungeKutta4Method::CalculateStep(time t, const timepoint& x,
	time h, CProblem* pProblem)
{
	//	total number of elements in the vector
	int n = x.size();

	//	first step
	timepoint k1;
	k1 = pProblem->CalculateDXF(t, x);
	for (int i = 0; i < n; ++i)
	{
		k1[i] *= h;
	}

	//	second step
	timepoint k2(x);
	for (int i = 0; i < n; ++i)
	{
		k2[i] += k1[i] / 2.0;
	}
	k2 = pProblem->CalculateDXF(t + h / 2.0, k2);
	for (int i = 0; i < n; ++i)
	{
		k2[i] *= h;
	}

	//	third step
	timepoint k3(x);
	for (int i = 0; i < n; ++i)
	{
		k3[i] += k2[i] / 2.0;
	}
	k3 = pProblem->CalculateDXF(t + h / 2.0, k3);
	for (int i = 0; i < n; ++i)
	{
		k3[i] *= h;
	}


	//	fourth step
	timepoint k4(x);
	for (int i = 0; i < n; ++i)
	{
		k4[i] += k3[i];
	}
	k4 = pProblem->CalculateDXF(t + h, k4);
	for (int i = 0; i < n; ++i)
	{
		k4[i] *= h;
	}


	//	sum the weighted steps into yf and return the final y values
	timepoint yf(x);
	for (int i = 0; i < n; ++i)
	{
		yf[i] += (k1[i] / 6.0)+(k2[i] / 3.0)+(k3[i] / 3.0)+(k4[i] / 6.0);
	}

	return yf;
}



};
