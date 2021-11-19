#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <math.h>
#include <time.h>
#define B(i,j) MM[i*(n+1)+j] //�������� �������
#define A(i,j) M[i*(n+1)+j] //���������� �������
using namespace std;
float *M, *MM, *sol, det;
int n, m; //����������� � ����� ������������
int n1, n2; //��������������� ����������
void metod_G();
void select_Amax(int k);
void b_Ax();
int main()
{
	int i, j, c;
	char s[2];
	setlocale(LC_ALL, "");
	cout << "*** ��������� ������� ������� ������� Ax=b ������� ������ ***";
	cout << "\n������� ����������� �������: ";
	cin >> n; n1 = n - 1; n2 = n + 1;
	M = new float[n*(n + 1)]; //����������� ������� - (A+b)
	MM = new float[n*(n + 1)];
	cout << "������� 0/1 - ������ ������� ��������� ������� ��� ������� ";
	cin >> c;
	switch (c) {
	case 0:
		//������������� ������� �.�. ����� ������� ��������
		srand(time(NULL));
		for (i = 0; i < n; i++)for (j = 0; j < n + 1; j++)B(i, j) = 0.5 - rand() / (RAND_MAX + 1.0); //[-0.5;0.5]
		break;
	default:
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				cout << "������� A(" << i << ", " << j << "): ";
				cin >> B(i, j);
			}
			cout << "������� b(" << i << "): ";
			cin >> B(i, n);
		}
	}
	cout << "��������� �������:\n";
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%.5f ", B(i, j));
			A(i, j) = B(i, j);
		}
		printf("%.5f\n", B(i, n));
		A(i, n) = B(i, n);
	}
	metod_G();
	printf("������������ ������� ������� = %.5f", det);
	if (fabs(det) < 1.E-10) {
		printf("\n������� ������� ����������� !");
	}
	else {
		printf("\n������� �������:\n");
		sol = new float[n];
		for (i = n - 1; i >= 0; i--) {
			sol[i] = A(i, n);
			for (j = n - 1; j > i; j--) {
				sol[i] -= A(i, j) * sol[j];
			}
		}
		for (i = 0; i < n; i++) {
			printf("%.5f ", sol[i]);
		}
		printf("\n����� �������������� ����� - %d", m);
		b_Ax();
		printf("\n������� ��� ����������� �������:\n");
		for (i = 0; i < n; i++) {
			printf("%.5f ", B(i, n));
		}
	}
	printf("\n��� ���������� ��������� ������� ����� ������ � ENTER");
	cin >> s;
	return 0;
}
//�/� ��������� ������� ��� ����������� �������
void b_Ax() {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) B(i, n) = B(i, n) - B(i, j) * sol[j];
	}
}
//�/� ��������� ����� ������
void metod_G() {
	int i, j, k, t;
	det = 1; m = 0;
	//�������� ������� � ������������� ����
	for (k = 0; k < n; k++) //���� �� ���������������
	{
		select_Amax(k);
		if (fabs(det) < 1.E-10) { return; }
		for (j = n; j > k - 1; j--) {
			A(k, j) = A(k, j) / A(k, k);
		}
		/*
		buf=A(k,k); //����� � ���
		for (j=k;j<n+1;j++) A(k,j)=A(k,j)/buf;
		*/
		for (i = k + 1; i < n; i++) {
			for (j = n; j > k - 1; j--) {
				A(i, j) = A(i, j) - A(i, k)*A(k, j);
			}
		}
	}
	printf("������� ������������� � ����; \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%.5f ", A(i, j));
		}
		printf("%.5f\n", A(i, n));
	}
}
//��������� ������ �������� �������� � �-�� ����������
void select_Amax(int k) {
	int i, kmax, j, k1 = k + 1;
	float Amod, Amax, buf;
	Amax = fabs(A(k, k)); kmax = k;
	if (k < n - 1) {
		for (i = k1; i < n; i++) {
			Amod = fabs(A(i, k));
			if (Amod > Amax) { Amax = Amod; kmax = i; }
		}
	}
	if (Amax < 1.E-10) { //������� ������� �����������
		det = 0; return;
	}
	if (kmax != k) {
		for (j = k; j < n + 1; j++) { //����������� ������
			buf = A(k, j);
			A(k, j) = A(kmax, j);
			A(kmax, j) = buf;
		}
		//printf("���� => A(k,k), A(k,n) = %.3f %.3f\n",A(k,k),A(k,n));
		det = -det;
		m++; //����� ������������ �����
	}
	det = det * A(k, k);
}