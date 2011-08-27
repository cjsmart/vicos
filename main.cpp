#include "RKMethod.h"
#include "Problem.h"
#include "VICOS.h"

using namespace std;
using namespace vicos;

#include <vector>
#include <cmath>

namespace vicos
{

class CMyProblem : public CProblem
{
public:
	// вычисляет значение $\frac{dx}{dt}$ для исходной задачи

	virtual timepoint CalculateDX(time t, const timepoint& x)
	{
		return timepoint();
	}

	// вычисляет значение $f(t)$ для исходной задачи

	virtual timepoint CalculateFt(time t)
	{
		return timepoint();
	}

	// вычисляет значение $\frac{dx}{dt}$ для задачи нахождения 
	// фундаментальной матрицы Коши

	virtual timepoint CalculateDXF(time t, const timepoint& x)
	{
		unsigned int cnt = x.size();
		timepoint dxdt(x);

		for (unsigned int i = 0; i < cnt; i++)
			dxdt[i] = cos(t);

		return dxdt;
	}

	// вычисляет значение $\frac{dx}{dt}$ для сопряжённой задачи 
	// нахождения обратной фундаментальной матрицы Коши

	virtual timepoint CalculateDXFT(time t, const timepoint& x)
	{
		return timepoint();
	}
};

} // end 'vicos' namespace


int main(int argc, char** argv)
{
	CVICOSSetup setup(2, new CMyProblem, 0, 100, true);
	CRungeKutta4Method rk;
	
	CVICOS vicos(&setup, &rk, NULL);
	
	vicos.Execute();

	return 0;
}

