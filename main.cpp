#include "RKMethod.h"
#include "Problem.h"
#include "VICOS.h"

using namespace std;
using namespace vicos;

#include <vector>
#include <cmath>

namespace vicos
{

class CSimpleExpProblem : public CProblem
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

	virtual timepoint CalculateDXF(time t, const timepoint& x, bool bInv)
	{
		unsigned int cnt = x.size();
		timepoint dxdt(x);

		if (!bInv)
		{
			for (unsigned int i = 0; i < cnt; i++)
				dxdt[i] = x[i];
		}
		else
		{
			for (unsigned int i = 0; i < cnt; i++)
				dxdt[i] = -x[i];
		}

		return dxdt;
	}

	// вычисляет значение $\frac{dx}{dt}$ для сопряжённой задачи 
	// нахождения обратной фундаментальной матрицы Коши

	virtual timepoint CalculateDXFT(time t, const timepoint& x)
	{
		// здесь нужно найти как решается сопряженная задача для
		// фундаментальной матрицы
		return timepoint();
	}
};

} // end of 'vicos' namespace


int main(int argc, char** argv)
{
	CVICOSContext setup(1, new CSimpleExpProblem, 0, 2, true);
	CRungeKutta4Method rk;
	
	CVICOS vicos(&setup, &rk, NULL);
	
	vicos.Execute();

	return 0;
}

