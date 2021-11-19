#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;
#define B(i,j) MM[i*n+j] //�������� �������
#define A(i,j) M[i*n+j] //���������� �������
#define E(i,j) ME[i*n+j] //��� ��������� �������
#define L(i,j) LL[i*n+j] //������ ��� ������� �������������� ��������
float *M, *MM, *ME, *LL, det = 1;
int n, m; //����������� � ����� ������������
int n1, n2;
void fine();
void select_Amax(int k);
void test();
int main()
{
	setlocale(LC_ALL, "");
	int i, j, c;
	char s[2];
	cout<<" *** ��������� ������� �������� ������� ������� ������-������� *** ";
		cout<<"\n������� ����������� �������� �������: ";
		cin >> n;
	M = (float *)malloc(n*n * sizeof(float)); //������� - A
	MM = (float *)malloc(n*n * sizeof(float)); //����� A - B
	ME = (float *)malloc(n*n * sizeof(float)); //��� ����� ��������� �������
	LL = (float *)malloc(2 * n * sizeof(float)); //������ ������ ��������
	n1 = n - 1; //����� ���������� � ����������� ������ A, B, L
	cout<<"������� 0/1 - ������ ������� ��������� ������� ��� ������� ";
	cin >> c;
	switch (c) {
	case 0:
		//������������� ������� �.�. ����� ������� ��������
		srand(time(NULL));
		for (i = 0; i < n; i++)for (j = 0; j < n; j++)B(i, j) = 0.5 - rand() / (RAND_MAX + 1.0); //[-0.5;0.5]
		break;
	default:
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				printf("������� A(%d,%d): ", i, j);
				cin >> B(i, j);
			}
		}
	}
	printf("��������� �������:\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%.5f ", B(i, j));
			A(i, j) = B(i, j);
		}
		printf("\n");
	}
	//printf("A(n-1,n-1) = %.3f\n",A(n1,n1));
	fine();
	printf("������������ ������� ������� = %.5f", det);
	if (fabs(det) < 1.E-10) {
		printf("\n������� ������� ����������� !");
	}
	else {
		printf("\n�������� �������:\n");
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				printf("%.5f ", A(i, j));
			}
			printf("\n");
		}
		printf("\n����� �������������� ����� - %d", m);
		test();
		printf("\n������������ �������� ������� �� ��������:\n");
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				printf("%.5f ", E(i, j));
			}
				printf("\n");
		}
	}
	printf("\n��� ���������� ��������� ������� ����� ������ � ENTER");
	cin >> s;
	return 0;
}
//��������� ������������ �������� ������� �� ��������
void test() {
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			E(i, j) = 0;
			for (k = 0; k < n; k++) {
				E(i, j) = E(i, j) + A(i, k)*B(k, j);
			}
		}
	}
}
//��������� ������ �������� �������� � �-�� ���������
void select_Amax(int k) {
	int i, kmax, j;
	float Amod, Amax, buf;
	if (k < (n - 1))
	{
		Amax = fabs(A(k, k)); kmax = k;
		for (j = (k + 1); j < n; j++)
		{
			Amod = fabs(A(k, j));
			if (Amod > Amax)
			{
				Amax = Amod; kmax = j;
			}
		}
		if (Amax < 1.E-10) // ������� �����������
		{
			det = 0;
			return;
		}
		if (kmax != k)
		{
			for (i = 0; i < n; i++) // ������������ �������
			{
				buf = A(i, k);
				A(i, k) = A(i, kmax);
				A(i, kmax) = buf;
			}
			det = -det;
			L(0, m) = k; //��������� ������ �������������� ��������
			L(1, m) = kmax;
			m++;
		}
	}
	det = det * A(k, k);
}
// ���������� �������� ������� ������� ������-�������
void fine()
{
	int i, j, k, m0, m1;
	float buf;
	det = 1; m = 0;
	for (k = 0; k < n; k++)
	{
		select_Amax(k); // ����� �������� ��������
		if (det == 0) return;
		for (i = 0; i < n; i++)
		{
			if (i != k)
			{
				A(i, k) = -A(i, k) / A(k, k);
				for (j = 0; j < n; j++)
				{
					if (j != k)
					{
						A(i, j) = A(i, j) + A(i, k)*A(k, j);
					}
				}
			}
		}
		for (j = 0; j < n; j++)
		{
			if (j != k)
			{
				A(k, j) = A(k, j) / A(k, k);
			}
		}
		A(k, k) = 1 / A(k, k);
	}
	if (m > 0) // ������������ ������ � �������� �������
	{
		for (i = (m - 1); i >= 0; i--)
		{
			m0 = L(0, i);
			m1 = L(1, i);
			for (j = 0; j < n; j++)
			{
				buf = A(m0, j);
				A(m0, j) = A(m1, j);
				A(m1, j) = buf;
			}
		}
	}
}