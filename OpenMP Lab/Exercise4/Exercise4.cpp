// OpenMP Basics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <omp.h>




using namespace std;

//number of loops  = 999
const int loopSize =999999999;

void main(int argc, char** argv)
{
	float result;

	LARGE_INTEGER ticksPerSecond;

	LARGE_INTEGER endTime;
	LARGE_INTEGER startTime;
	LARGE_INTEGER performanceTime;



	//get the high resolution counter's accury
	QueryPerformanceFrequency(&ticksPerSecond);

	//whta the time is it
	QueryPerformanceCounter(&startTime);

	//calculation process used by openmp
#ifdef _OPENMP
	cout<<"OpenMP enabled"<<endl;
#endif

#pragma omp parallel for
	for(int index = 0; index < loopSize; index++)
	{
		result = sqrt((float)index);
	}

	QueryPerformanceCounter(&endTime);

	performanceTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
	//time.QuadPart = performanceTime.QuadPart / ticksPerSecond.QuadPart;
	float ticksPerMs = float(ticksPerSecond.QuadPart / 1000);


	float timeConsumed = float(performanceTime.QuadPart / ticksPerMs);

	
	
	cout<<"Exercise4 Finished result = "<<result<<endl;
	//cout<<"Consume Time = 
	cout<<"Time counsumed s= "<<timeConsumed<<endl;

	//==
	int pause;
	cin>> pause;
}




