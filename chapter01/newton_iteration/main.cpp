#include <iostream>
#include <math.h>

#define _NEWTON_ITERATION_DEBUG_

#ifdef _NEWTON_ITERATION_DEBUG_
#include <iomanip>
#endif

using namespace std;

double newton_iteration(double (*f)(double), double (*fd)(double), double x, int loops)
{
#ifdef _NEWTON_ITERATION_DEBUG_
	cout << fixed << setw(17) << setprecision(14) << setiosflags(ios::showpos);
	cout << 0 << '\t' << x << endl;
#endif

	for(int i = 0; i < loops; ++i) {
		double fdx = fd(x);
		if(fdx == 0.0) break;
		x -= (f(x)/fdx);

#ifdef _NEWTON_ITERATION_DEBUG_
		cout << fixed << setw(17) << setprecision(14) << setiosflags(ios::showpos);
		cout << (i+1) << '\t' << x << endl;
#endif
	}

	return x;
}

double f1(double x)
{
	return x*x*x + x - 1;
}

double fd1(double x)
{
	return 3*x*x + 1;
}

double f2(double x)
{
	return x*x;
}

double fd2(double x)
{
	return 2*x;
}

double f3(double x)
{
	return sin(x) + x*x*cos(x) - x*x - x;
}

double fd3(double x)
{
	return cos(x) + 2*x*cos(x) - x*x*sin(x) - 2*x - 1;
}

int main()
{
	double x1 = newton_iteration(f1, fd1, -0.7, 7);
	cout << x1 << endl << endl;

	double x2 = newton_iteration(f2, fd2, 1, 10);
	cout << x1 << endl << endl;

	double x3 = newton_iteration(f3, fd3, 1, 19);
	cout << x3 << endl << endl;

	return 0;
}
