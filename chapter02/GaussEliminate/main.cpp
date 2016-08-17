#include <iostream>
#include <math.h>

using namespace std;

#define EPS	0.0000000001

bool gauss_eleminate(double a[], double b[], int n, double x[])
{
	if (a == NULL || b == NULL || n <= 0 || x == NULL)
		return false;

	int id1 = 0;
	int id2 = 0;

	for (int i = 0; i < n; ++i, id1 += n) {
		if (fabs(a[id1+i]) < EPS)
			return false;

		id2 = id1 + n;

		for (int j = i+1; j < n; ++j, id2 += n) {
			double mult = a[id2+i] / a[id1+i];
			for (int k = i+1; k < n; ++k)
				a[id2+k] -= mult*a[id1+k];
			b[j] -= mult*b[i];
		}
	}

	id1 = n*(n-1);

	for (int i = n-1; i >= 0; --i, id1 -= n) {
		for (int j = i+1; j < n; ++j) {
			b[i] -= a[id1+j]*x[j];
		}
		x[i] = b[i]/a[id1+i];
	}

	return true;
}

int main()
{
	double a[] = { 1, 2, -1, 2, 1, -2, -3, 1, 1 };
	double b[] = { 3, 3, -6 };
	double x[3] = { 0 };

	gauss_eleminate(a, b, 3, x);

	return 0;
}
