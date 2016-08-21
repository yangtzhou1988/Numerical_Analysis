#include <iostream>
#include <math.h>

using namespace std;

#define EPS	0.0000000001

bool PALU(double A[], int n, double P[], double L[], double U[])
{
	if (A == NULL || n <= 0 || P == NULL || L == NULL || U == NULL)
		return false;

	int id1 = 0;
	int id2;
	int *exchange_list = new int[n];

	for (int i = 0; i < n; ++i)
		exchange_list[i] = i;

	for (int i = 0; i < n*n; ++i)
		P[i] = 0;

	for (int i = 0; i < n*n; ++i)
		U[i] = A[i];

	for (int i = 0; i < n; ++i, id1 += n) {
		L[id1 + i] = 1;
		for (int j = i + 1; j < n; ++j)
			L[id1 + j] = 0;
	}

	id1 = 0;
	for (int i = 0; i < n - 1; ++i, id1 += n) {
		double pmax = fabs(U[id1 + i]);
		int imax = i;
		id2 = id1 + i + n;

		for (int j = i + 1; j < n; ++j, id2 += n) {
			if (pmax < fabs(U[id2])) {
				imax = j;
				pmax = fabs(U[id2]);
			}
		}

		if (pmax < EPS) {
			delete[] exchange_list;
			return false;
		}

		if (imax != i) {
			id2 = imax*n;
			swap(exchange_list[i], exchange_list[imax]);
			for (int j = 0; j < n; ++j)
				swap(U[id1+j], U[id2+j]);
		}

		id2 = id1 + n;
		for (int j = i + 1; j < n; ++j, id2 += n) {
			double mult = U[id2 + i] / U[id1 + i];
			U[id2 + i] = mult;
			for (int k = i + 1; k < n; ++k)
				U[id2 + k] -= mult*U[id1 + k];
		}
	}

	id1 = 0;
	for (int i = 0; i < n; ++i, id1 += n) {
		for (int j = 0; j < i; ++j) {
			L[id1 + j] = U[id1 + j];
			U[id1 + j] = 0;
		}
	}

	id1 = 0;
	for (int i = 0; i < n; ++i, id1 += n)
		P[id1+exchange_list[i]] = 1;

	delete[] exchange_list;
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
	double P1[4];
	double L1[4];
	double U1[4];

	PALU(A1, 2, P1, L1, U1);
	cout << "A1 = " << endl;
	print_matrix(A1, 2, 2);
	cout << "P1 = " << endl;
	print_matrix(P1, 2, 2);
	cout << "L1 = " << endl;
	print_matrix(L1, 2, 2);
	cout << "U1 = " << endl;
	print_matrix(U1, 2, 2);
	cout << endl;

	double A2[] = {
		 1, -1,  3,
		-1,  0, -2,
		 2,  2,  4
	};
	double P2[9];
	double L2[9];
	double U2[9];

	PALU(A2, 3, P2, L2, U2);
	cout << "A2 = " << endl;
	print_matrix(A2, 3, 3);
	cout << "P2 = " << endl;
	print_matrix(P2, 3, 3);
	cout << "L2 = " << endl;
	print_matrix(L2, 3, 3);
	cout << "U2 = " << endl;
	print_matrix(U2, 3, 3);
	cout << endl;

	double A3[] = {
		 2,  1,  5,
		 4,  4, -4,
		 1,  3,  1
	};
	double P3[9];
	double L3[9];
	double U3[9];

	PALU(A3, 3, P3, L3, U3);
	cout << "A3 = " << endl;
	print_matrix(A3, 3, 3);
	cout << "P3 = " << endl;
	print_matrix(P3, 3, 3);
	cout << "L3 = " << endl;
	print_matrix(L3, 3, 3);
	cout << "U3 = " << endl;
	print_matrix(U3, 3, 3);
	cout << endl;

	return 0;
}
