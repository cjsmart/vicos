#include "RKMethod.h"
#include "Problem.h"

using namespace std;
using namespace iode;

#include <vector>
#include <cmath>

timepoint dydtcos(double x, const timepoint& y) 
{
    unsigned int cnt = y.size();
    timepoint dydt(y);
    
    for (unsigned int i = 0; i < cnt; i++)
        dydt[i] = cos(x);
    
    return dydt;
}

namespace iode
{
class CMyProblem : public CProblem
{
public:
	// вычисляет значение $\frac{dx}{dt}$ для исходной задачи
    virtual timepoint CalculateDX(time t, const timepoint& x)
	{ return timepoint(); }
    
	// вычисляет значение $f(t)$ для исходной задачи
    virtual timepoint CalculateFt(time t)
	{ return timepoint(); }
    
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
	{ return timepoint(); }
};
};

/*
 * 
 */
int main(int argc, char** argv) 
{
    timepoint yi(1,0.0);
    
    double x=0.0, dx=0.10;
	
	CMyProblem prob;
	CRungeKutta4Method rk;
     
    while (x<10.0)
	{
         yi= rk.CalculateStep(x, yi, dx, &prob);
		 
		 std::cout << yi << std::endl;
		 
         x+=dx;
    }
    
    return 0;
}

