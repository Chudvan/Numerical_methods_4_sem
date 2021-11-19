#include <iostream>
#include <windows.h>
#include <cmath>
using namespace std;

float nKub(int n, float v[]);
float nOkt(int n, float v[]);
float nSp(int n, float v[]);

int main()
{
	int n, i;
	float *v, normKub, normOkt, normSp;
	char s[2];
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "*** Программа вычисляет кубическую, октаэдрическую и сферическую нормы вектора ***" << endl;
	cout << "Введите размерность вектора n: ";
	cin >> n;
	v = new float[n];
	for (i = 0; i < n; i++) {
		cout << "Введите v" << i << ": ";
		cin >> v[i];
	}
	normKub = nKub(n, v);
	normOkt = nOkt(n, v);
	normSp = nSp(n, v);
	cout << "Кубическая, октаэдрическая и сферическая нормы вектора равны: ";
	cout.precision(2);
	cout << fixed << normKub << ", " << fixed << normOkt;
	cout << ", " << fixed << normSp << endl;
	cout << "Для завершения работы программы введите любую клавишу и нажмите Enter.";
	cin >> s;
	return 0;
}

float nKub(int n, float v[]) {
	float norm = 0, buf;
	for(int i = 0; i < n; i++) {
		buf = abs(v[i]);
		if (norm < buf) norm = buf;
	}
	return norm;
}
float nOkt(int n, float v[]) {
	float norm = 0;
	for(int i = 0; i < n; i++)norm += abs(v[i]);
	return norm;
}
float nSp(int n, float v[]) {
	float norm = 0;
	for (int i = 0; i < n; i++) {
		norm += v[i] * v[i];
	}
	return sqrt(norm);
}
