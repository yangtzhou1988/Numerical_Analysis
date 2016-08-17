#include <iostream>
#include <math.h>

using namespace std;

#define EPS	0.0000000001

bool LUSolution(double A[], double b[], int n, double x[])
{
	if (A == NULL || b == NULL || n <= 0 || x == NULL)
		return false;

	double *L = new double[n*n];
	int id1 = 0;
	int id2 = 0;

	for (int i = 0; i < n; ++i, id1 += n) {
		if (fabs(A[id1+i]) < EPS) {
			delete[] L;
			return false;
		}

		L[id1+i] = 1;
		id2 = id1 + n;

		for (int j = i+1; j < n; ++j, id2 += n) {
			double mult = A[id2+i]/A[id1+i];
			L[id2+i] = mult;
			for (int k = i+1; k < n; ++k)
				A[id2+k] -= mult*A[id1+k];
		}
	}

	id1 = 0;
	for (int i = 0; i < n; ++i, id1 += n) {
		for (int j = 0; j < i; ++j)
			b[i] -= L[id1+j] * x[j];
		x[i] = b[i]/L[id1+i];
	}

	id1 = n*(n-1);
	for (int i = n-1; i >= 0; --i, id1 -= n) {
		for (int j = i+1; j < n; ++j)
			x[i] -= A[id1+j] * x[j];
		x[i] = x[i]/A[id1+i];
	}

	delete[] L;
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
		1,  1,
		3, -4
	};
	double b1[] = { 3, 2 };
	double x1[2] = {0};

	LUSolution(A1, b1, 2, x1);
	cout << "x1 = " << endl;
	print_matrix(x1, 1, 2);


	double A2[] = {
		1,  2, -1,
		2,  1, -2,
	   -3,  1,  1
	};
	double b2[] = { 3, 3, -6 };
	double x2[3] = { 0 };

	LUSolution(A2, b2, 3, x2);
	cout << "x2 = " << endl;
	print_matrix(x2, 1, 3);

	return 0;
}
