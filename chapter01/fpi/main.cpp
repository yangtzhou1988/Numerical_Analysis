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
		cout << fixed << setw(12) << setprecision(9) << setiosflags(ios::showpos);
		cout << i << '\t' << x0 << endl;
#endif
		x0 = f(x0);
	}

#ifdef _FPI_DEBUG_
	cout << fixed << setw(12) << setprecision(9) << setiosflags(ios::showpos);
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

double f4(double x)
{
	return x + cos(x) - sin(x);
}

double f5(double x)
{
	return 2.8*x - x*x;
}

double f6(double x)
{
	return (x + 2/x) / 2;
}

int main()
{
	double x1 = fpi(f1, 0.5, 12);
	cout << x1 << endl << endl;

	double x2 = fpi(f2, 0.5, 25);
	cout << x2 << endl << endl;

	double x3 = fpi(f3, 0.5, 7);
	cout << x3 << endl << endl;

	double x4 = fpi(f4, 0, 20);
	cout << x4 << endl << endl;

	double x5 = fpi(f5, 0.1, 10);
	cout << x5 << endl << endl;

	double x6 = fpi(f6, 1, 20);
	cout << x6 << endl << endl;

	return 0;
}
