#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <iomanip>
#define B(i, j) MM[i * (n + 2) + j]
#define A(i, j) M[i * (n + 2) + j]
using namespace std;

float *M, *MM, eps, epst, t;
int n, iter, it;
int iter_Up();
void var_M();
void Ax_b();
int main() {
	setlocale(LC_ALL, "");
	int i, j, code, fl = 0, c;
	int fl1 = 0, iopt;
	float topt, dt = 0.05;
	char s[2];
	cout << "***��������� ������� ������� ";
	cout << "������� ������� ������� ����������***\n";
	cout << "������� ����������� �������: ";
	cin >> n;
	M = new float[n * (n + 2)];
	MM = new float[n * (n + 2)];
	cout << "������� 0/1 - ������ ������� ��������� ������� ��� ������� ";
	cin >> c;
	switch (c) {
		case 0:
			srand(time(NULL));
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++)
					B(i, j) = 0.5 - rand() / (RAND_MAX + 1.0);
			}
			break;
		default:
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					cout << "������� B(" << i << ", " << j << "): ";
					cin >> B(i, j);
				}
				cout << "������� b(" << i << "): ";
				cin >> B(i, n);
			}

	}
	cout << "�������� �������:\n";
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << B(i, j) << " ";
		}
		cout << B(i, n) << "\n";
	}
	var_M();
	cout << "��������������� �������:\n";
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << A(i, j) << " ";
		}
		cout << A(i, n) << "\n";
	}
	while (fl == 0) {
		cout << "����� ��������, �������� � �������� t: ";
		cin >> iter >> eps >> t;
		var_M();
		code = iter_Up();
		switch (code) {
			case 0:
				cout << "��� = " << code << ", ����� �������������� ��������";
				cout << " = " << it << ", �������� = " << setprecision(8) << epst;
				cout << "\n�������\n";
				for (i = 0; i < n; i++)cout << A(i, n + 1) << " ";
				Ax_b();
				cout << "\n�������\n";
				for (i = 0; i < n; i++)cout << B(i, n + 2) << " ";
				/*cout << "����� ����������� t -> ������� 0, ����� 1 - ���� ����� ";
				cout << "����������, 2 - �����: ";
				cin >> fl1;
				if (fl == 1) break;
				if (fl == 2) {
					fl = 1; 
					break;
				}
				if (fl == 0) {
					iopt = iter;
					t = 0;
					for (i = 0, i < 40; i++) {
						t += dt;
						var_M();
						code = iter_Up();
						if((!code)&&(it < iopt))
					}
				}
				cout << "\n�������� ��������� ����������� �������� t � iter: ";
				cout << setprecision(3) << topt << "; " << iopt;
				cout << "��������� ���������� ��� ����� ���������� ������������� ";
				cout << "�������� - ������� 0, ����� - 1: ";
				cin >> fl;
				*/
				break;
			case 1:
				cout << "\n� ������� ������� ���� ������������ ��������� = 0";
				fl = 1;
				break;
			case 2:
				cout << "����� ���������!";
				fl = 1;
				break;
		}
	}
	cout << "\n��� ���������� ��������� ������� ����� ������� � ENTER";
	cin >> s[0];
	system("pause>nul");
	return 0;
}
int iter_Up() {
	int i, j, k, fl = 0;
	float nt, buf, norm, norm_old = 0, t1 = 1 - t;
	for (i = 0; i < n; i++) {
		A(i, n + 1) = A(i, n);
		if (abs(A(i, i)) < 1.e-30)return 1;
		A(i, n) = t * A(i, n) / A(i, i);
		for (j = 0; j < n; j++)if (i != j)A(i, j) = t * A(i, j) / A(i, i);
	}
	it = 0;
	for (k = 1; k <= iter; k++) {
		it += 1; norm = 0;
		for (i = 0; i < n; i++) {
			buf = t1 * A(i, n + 1) + A(i, n);
			for (j = 0; j < n; j++) {
				if (i != j) buf = buf - A(i, j)*A(j, n + 1);
			}
			nt = abs(buf - A(i, n + 1));
			A(i, n + 1) = buf;
			if (nt > norm) norm = nt;
		}
		epst = norm;
		if (norm <= eps) return 0;
		if (norm > norm_old)fl = fl + 1;
		else fl = 0;
		if (fl > 5) return 2;
		norm_old = norm;
	}
	return 0;
}
void var_M() {
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A(i, j) = 0;
			for (k = 0; k < n; k++) {
				A(i, j) += B(k, i)*B(k, j);
			}
		}
	}
}
void Ax_b() {
	int i, j;
	for (i = 0; i < n; i++) {
		B(i, n + 1) = B(i, n);
		for (j = 0; j < n; j++) {
			B(i, n + 1) -= B(i, j)*A(j, n + 1);
		}
	}
}