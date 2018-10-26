#include <iostream>
#include <stdio.h>
#include "conio.h"
#include <omp.h>
#include <time.h>
#define len 100
using namespace std;
float integeration(float starte, float ende)
{
	float x = starte, y = 0, Area = 0;
	for (; x <= ende; x += .0001)
	{
		y = 3 * x*x;
		Area += y * .0001;
	}
	return Area;
}

int main()
{
	float area1, area2, area3, area4;
	int t1 = clock();
	float area=integeration(0, len);
	int t2 = clock();
	cout << "time = " << t2 - t1 << "\n Area = " << area<<"\n";
	t1 = clock();
#pragma omp parallel num_threads(4)	
	{
		int thr = omp_get_thread_num();
		if (thr == 0)
		{
			 area1 = integeration(0, len/4);
		}
		else if (thr == 1)
		{
			 area2 = integeration(len/4, len/2);
		}
		else if (thr == 2)
		{
			 area3 = integeration(len / 2, 3*len / 4);
		}
		else
		{
			 area4 = integeration(3*len / 4, len);
		}
	}
	t2 = clock();
	float Area = area1 + area2 + area3 + area4;
	cout << "time = " << t2 - t1 << "\n Area = " << Area << "\n";
	_getch();


	return 0;
		
}
