#include <iostream>
#include <math.h>

using namespace std;

#define EPS	0.0000000001

bool PALUSolution(double A[], double b[], int n, double x[])
{
	if (A == NULL || b == NULL || n <= 0 || x == NULL)
		return false;

	int id1 = 0;

	for (int i = 0; i < n-1; ++i, id1 += n) {
		double pmax = fabs(A[id1+i]);
		int imax = i;
		int id2 = id1+i+n;

		for (int j = i+1; j < n; ++j, id2 += n) {
			if (pmax < fabs(A[id2])) {
				imax = j;
				pmax = fabs(A[id2]);
			}
		}

		if (pmax < EPS) return false;

		if (imax != i) {
			id2 = imax*n;
			swap(b[i], b[imax]);
			for (int j = 0; j < n; ++j)
				swap(A[id1+j], A[id2+j]);
		}

		id2 = id1+n;
		for (int j = i+1; j < n; ++j, id2 += n) {
			double mult = A[id2+i] / A[id1+i];
			A[id2+i] = mult;
			for (int k = i+1; k < n; ++k)
				A[id2+k] -= mult*A[id1+k];
		}
	}

	id1 = n;
	for (int i = 1; i < n; ++i, id1 += n) {
		for (int j = 0; j < i; ++j)
			b[i] -= A[id1+j]*b[j];
	}

	id1 = n*(n-1);
	for (int i = n-1; i >= 0; --i, id1 -= n) {
		for (int j = i+1; j < n; ++j)
			b[i] -= A[id1+j]*x[j];
		x[i] = b[i] / A[id1+i];
	}

	return true;
}

void print_matrix(double a[], int m, int n)
{
	int k = 0;

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j)
			cout << a[k++] << '\t';
		cout << endl;
	}
	cout << endl;
}

int main()
{
	double A1[] = {
		2,  1,  5,
		4,  4, -4,
		1,  3,  1
	};
	double b1[] = { 5, 0, 6 };
	double x1[3] = { 0 };

	PALUSolution(A1, b1, 3, x1);
	cout << "x1 = " << endl;
	print_matrix(x1, 1, 3);


	double A2[] = {
		2,  3,
		3,  2,
	};
	double b2[] = { 4, 1 };
	double x2[2] = { 0 };

	PALUSolution(A2, b2, 2, x2);
	cout << "x2 = " << endl;
	print_matrix(x2, 1, 2);

	return 0;
}
