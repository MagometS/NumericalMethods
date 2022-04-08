#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double Lagrange(double* node, double (*f)(double x), int n, double x);
void Chebyshev(int n, double* node, double a, double b);
double Function(double x);
void GraphicPoly(int n, double* node, double a, double b, double (*f)(double x), double* y, int number);
void PrintToFile(double* array, const char* fileName, int number);


int main()
{
	int n = 3;//кол-во узлов
	double a = -4;//область функции
	double b = 5;
	int number = 1000;// кол-во точек в графике

	FILE* file = fopen("D:\\Code\\MATLAB_code\\NumMethLab5\\xArray.txt", "w");//массив точек на оси абсцисс
	double step = (b - a) / number;
	double xArray = a;
	for (int i = 0; i < number; i++)
	{
		fprintf(file, "%.16f ", xArray);
		xArray += step;
	}
	fclose(file);

	double* node = (double*)malloc(n * sizeof(double));
	if (node == NULL)
	{
		printf("error allocating node");
		return 0;
	}
	double* y = (double*)malloc(number * sizeof(double));
	if (y == NULL)
	{
		printf("error allocating y");
		free(node);
		return 0;
	}

	GraphicPoly(n, node, a, b, Function, y, number);// находим значения полинома для 3-х узлов

	const char* fileName1 = "D:\\Code\\MATLAB_code\\NumMethLab5\\poly1.txt";
	PrintToFile(y, fileName1, number);
	free(node);

	n = 5;//значения полинома для 5 узлов

	node = (double*)malloc(n * sizeof(double));
	if (node == NULL)
	{
		printf("error allocating node");
		free(y);
		return 0;
	}

	GraphicPoly(n, node, a, b, Function, y, number);

	const char* fileName2 = "D:\\Code\\MATLAB_code\\NumMethLab5\\poly2.txt";
	PrintToFile(y, fileName2, number);
	free(node);

	n = 7;//значения полинома для 7 узлов

	node = (double*)malloc(n * sizeof(double));
	if (node == NULL)
	{
		printf("error allocating node");
		free(y);
		return 0;
	}

	GraphicPoly(n, node, a, b, Function, y, number);

	const char* filename3 = "D:\\Code\\MATLAB_code\\NumMethLab5\\poly3.txt";
	PrintToFile(y, filename3, number);
	free(node);

	free(y);

	return 0;
}


void PrintToFile(double* array, const char* fileName, int number)//печатает содержимое массива в файл
{
	FILE* file = fopen(fileName, "w");
	for (int i = 0; i < number; i++)
	{
		fprintf(file, "%.16f ", *(array + i));
	}
	fclose(file);

}


//Находит значения(y) полинома Лагранжа, от функции f с n узлов Чебышева(node), на интервале [a,b], кол-во точек = number
void GraphicPoly(int n, double* node, double a, double b, double (*f)(double x), double* y, int number)
{
	double step = (b - a) / number;
	double x = a;
	Chebyshev(n, node, a, b);

	for (int i = 0; i < number; i++)
	{
		*(y + i) = Lagrange(node, f, n, x);
		x += step;
	}
}


double Function( double x)
{
	return (x * x + 4 * sin(x) - 2);
}


//Находит значение полинома Лагранжа с узлами node для функции f в (.)x. 
double Lagrange(double* node, double (*f)(double x), int n, double x)
{
	double resLagrange = 0;
	double sumPoly = 1;
	double* y = (double*)malloc(n * sizeof(double));
	if (y == NULL)
	{
		printf("error allocating y");
	}
	for (int i = 0; i < n; i++)
	{
		*(y + i) = f(*(node + i));
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				continue;
			}
			sumPoly *= (x - *(node + j)) / (*(node + i) - *(node + j));
		}
		resLagrange += *(y + i) * sumPoly;
		sumPoly = 1;
	}
	free(y);

	return resLagrange;
}


void Chebyshev(int n, double* node, double a, double b)//находит узлы Чебышева
{
	for (int i = 0; i < n; i++)
	{
		*(node + i) = (a + b) / 2 + (b - a) / 2 * cos((2 * (double)i + 1) * M_PI / (2 * (double)n));
	}

}

