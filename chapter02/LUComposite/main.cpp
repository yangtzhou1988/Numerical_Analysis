#include <iostream>
#include <math.h>

using namespace std;

#define EPS	0.0000000001

bool LUComposite(double A[], int n, double L[], double U[])
{
	if (A == NULL || n <= 0 || L == NULL || U == NULL)
		return false;

	int id1 = 0;
	int id2 = 0;

	for (int i = 0; i < n*n; ++i)
		U[i] = A[i];

	for (int i = 0; i < n; ++i, id1 += n) {
		L[id1+i] = 1;
		for (int j = i+1; j < n; ++j) {
			L[id1+j] = 0;
		}
	}

	id1 = 0;

	for (int i = 0; i < n; ++i, id1 += n) {
		if (fabs(U[id1+i]) < EPS)
			return false;

		id2 = id1 + n;

		for (int j = i+1; j < n; ++j, id2 += n) {
			double mult = U[id2+i] / U[id1+i];
			U[id2+i] = 0;
			L[id2+i] = mult;
			for (int k = i+1; k < n; ++k)
				U[id2+k] -= mult*U[id1+k];
		}
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
					 1,  1,
				     3, -4
				  };
	double L1[4];
	double U1[4];

	LUComposite(A1, 2, L1, U1);
	cout << "A1 = " << endl;
	print_matrix(A1, 2, 2);
	cout << "L1 = " << endl;
	print_matrix(L1, 2, 2);
	cout << "U1 = " << endl;
	print_matrix(U1, 2, 2);


	double A2[] = {
		1,  2, -1,
		2,  1, -2,
	   -3,  1,  1
	};
	double L2[9];
	double U2[9];

	LUComposite(A2, 3, L2, U2);
	cout << "A1 = " << endl;
	print_matrix(A2, 3, 3);
	cout << "L1 = " << endl;
	print_matrix(L2, 3, 3);
	cout << "U1 = " << endl;
	print_matrix(U2, 3, 3);

	return 0;
}
