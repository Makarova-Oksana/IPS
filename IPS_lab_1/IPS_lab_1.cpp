// IPS_lab_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <math.h>
#include <locale.h>
#include <chrono>
#include <thread>
# define M_PI 3.14159265358979323846 
using namespace std::chrono;
using namespace std;
double method_simpsona_18(int n)
{ 
	double a = -1.0;
	double b = 1.0;
	double c = 5.0 / 2.0;
	double integral = 0;
	double h = 0.0;
	double y_odd = 0.0; // нечетный
	double y_even = 0.0; // нечетный
	double y0, yn = 0.0;
	double analitics = (5 / 4)*M_PI;//3.9270;
	h = (b - a) / n;
	y0 = c / sqrt(2 - a*a);
	yn = c / sqrt(2 - b*b);
	double x = a + h;
	for (int i = 1; i < n - 1; i++)
	{
		
		if (i % 2 == 0)  
		{
			y_even = y_even + c / sqrt(2 - x*x);
		}
		else
		{
			y_odd = y_odd + c / sqrt(2 - x*x);
		}
		x = x + h;
	}
	integral = h / 3 * (y0 + yn + 4 * y_odd + 2 * y_even);

	cout << " n = " <<n << " integral = " << integral << endl;
	cout << " Ошибка по отношению к аналитическому решению равна " << (analitics - integral) << endl;
	return integral;
}

int main()
{
	setlocale(0,"Rus");
	int array_n[5] = { 100, 1000, 10000, 100000, 1000000 };
	double answer = 0;
	int length = size(array_n);
	double analitics = 3.9270;
   //
	

   // без распараллеливания
   //	#pragma loop(no_vector) //отключение векторизации

   // #pragma loop(ivdep) // параллелизация
   // #pragma loop(hint_parallel(5)) 
   /*
	for (int k = 0;k <length; k++) 
	{
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		answer = method_simpsona_18(array_n[k]);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> duration = (t2 - t1);
		cout << " Duration is: " << duration.count() << " seconds" << endl;
		cout << " n = " << array_n[k] << " integral = " << answer << endl;
		cout <<" Ошибка по отношению к аналитическому решению равна " << (analitics - answer) << endl << endl;
	}
	*/

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	thread first(method_simpsona_18, array_n[0]);
	first.join();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> duration = (t2 - t1);
	cout << " Duration is: " << duration.count() << " seconds" << endl << endl;
	
	

	t1 = high_resolution_clock::now();
	thread second(method_simpsona_18, array_n[1]);
	second.join();
	t2 = high_resolution_clock::now();
	duration = (t2 - t1);
	cout << " Duration is: " << duration.count() << " seconds" << endl << endl;
	


	t1 = high_resolution_clock::now();
	thread third(method_simpsona_18, array_n[2]);
	third.join();
	t2 = high_resolution_clock::now();
	duration = (t2 - t1);
	cout << " Duration is: " << duration.count() << " seconds" << endl << endl;


	t1 = high_resolution_clock::now();
	thread fourth(method_simpsona_18, array_n[3]);
	fourth.join();
	duration = (t2 - t1);
	cout << " Duration is: " << duration.count() << " seconds" << endl << endl;
	

	t1 = high_resolution_clock::now();
	thread fifth(method_simpsona_18, array_n[4]);
	fifth.join();
	duration = (t2 - t1);
	cout << " Duration is: " << duration.count() << " seconds" << endl << endl;

	system("pause");
    return 0;
}

