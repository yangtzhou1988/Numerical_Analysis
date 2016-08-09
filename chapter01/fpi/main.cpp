#include <iostream>
#include <math.h>

#define _FPI_DEBUG_

#ifdef _FPI_DEBUG_
#include <iomanip>
#endif

using namespace std;

double fpi(double (*f)(double), double x0, double loops)
{
	int i;

	for(i = 0; i < loops; ++i) {
#ifdef _FPI_DEBUG_
		cout << fixed << setw(11) << setprecision(8) << setiosflags(ios::showpos);
		cout << i << '\t' << x0 << endl;
#endif
		x0 = f(x0);
	}

#ifdef _FPI_DEBUG_
	cout << fixed << setw(11) << setprecision(8) << setiosflags(ios::showpos);
	cout << i << '\t' << x0 << endl;
#endif

	return x0;
}

double f1(double x)
{
	return 1 - x*x*x;
}

double f2(double x)
{
	return pow(1-x, 1.0/3.0);
}

double f3(double x)
{
	return (1 + 2*x*x*x) / (1 + 3*x*x);
}

int main()
{
	double x1 = fpi(f1, 0.5, 12);
	cout << x1 << endl << endl;

	double x2 = fpi(f2, 0.5, 25);
	cout << x2 << endl << endl;

	double x3 = fpi(f3, 0.5, 7);
	cout << x3 << endl << endl;

	return 0;
}
