// OpenMP Basics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <omp.h>


using namespace std;

//number of loops  = 999
const int loopSize = 99999999;

void main(int argc, char** argv)
{
	volatile float result;

	LARGE_INTEGER ticksPerSecond;

	LARGE_INTEGER endTime;
	LARGE_INTEGER startTime;
	LARGE_INTEGER performanceTime;


#ifdef _OPENMP
	cout<<"OpenMP enabled"<<endl;
	//omp_set_num_threads(4);
#endif
	

	//get the high resolution counter's accury
	QueryPerformanceFrequency(&ticksPerSecond);

	//whta the time is it
	QueryPerformanceCounter(&startTime);

	//calculation process used by openmp
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

	
	
	cout<<"Exercise5 Finished result = "<<result<<endl;
	//cout<<"Consume Time = 
	cout<<"Time counsumed ms= "<<timeConsumed<<endl;

	//==
	int pause;
	cin>> pause;
}




