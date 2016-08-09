#include <iostream>
#include <math.h>

using namespace std;

#define _BISECT_DEBUG_

#ifdef _BISECT_DEBUG_
#include <iomanip>
#endif

inline static bool double_sign_opposite(double &a, double &b)
{
	if(((reinterpret_cast<unsigned long long&>(a))^(reinterpret_cast<unsigned long long&>(b)))>>63)
		return true;
	else
		return false;
}

double bisect(double (*f)(double), double low, double high, double tol)
{
	if(high < low) swap(low, high);

	double fl = f(low);
	double fh = f(high);

	if(fl == 0.0) return low;
	else if(fh == 0.0) return high;
	if(!double_sign_opposite(fl, fh)) throw range_error("");

#ifdef _BISECT_DEBUG_
	int loops = 0;
	cout << "i" << '\t';
	cout << "low" << "\t\t" << "f(low)" << "\t\t";
	cout << "mid" << "\t\t" << "f(mid)" << "\t\t";
	cout << "high" << "\t\t" << "f(high)" << endl;
#endif

	double tol2 = tol * 2;

	while(high-low > tol2) {
		double mid = (high+low)/2;
		double fm = f(mid);

#ifdef _BISECT_DEBUG_
		cout << loops << '\t';
		cout << fixed << setw(13) << setprecision(10) << setiosflags(ios::showpos);
		cout << low << "\t" << fl << "\t" << mid << "\t" << fm << "\t" << high << "\t" << fh << endl;
		loops++;
#endif

		if(fm == 0.0) return mid;

		if(double_sign_opposite(fl, fm)) {high = mid; fh = fm;}
		else {low = mid; fl = fm;}
	}

	return (high+low)/2;
}

double f1(double x)
{
	return x*x*x + x - 1;
}

double f2(double x)
{
	return cos(x) - x;
}

double f3(double x)
{
	return x*x*x - 9;
}

double f4(double x)
{
	return 3*x*x*x + x*x - x - 5;
}

double f5(double x)
{
	return cos(x)*cos(x) + 6 - x;
}

double f6(double x)
{
	return x*x*x*x - x*x*x - 10;
}

int main()
{
	double x1 = bisect(f1, 0, 1, 0.00051);
	cout << x1 << endl << endl;

	double x2 = bisect(f2, 0, 1, 0.0000005);
	cout << x2 << endl << endl;

	double x3 = bisect(f3, 2, 3, 0.125);
	cout << x3 << endl << endl;

	double x4 = bisect(f4, 1, 2, 0.125);
	cout << x4 << endl << endl;

	double x5 = bisect(f5, 6, 7, 0.125);
	cout << x5 << endl << endl;

	double x6 = bisect(f6, 2, 3, 0.0000000001);
	cout << x6 << endl << endl;

	return 0;
}
