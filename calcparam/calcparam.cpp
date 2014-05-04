// calcparam.cpp : Defines the exported functions for the DLL application.
//
#pragma once
#include "stdafx.h"
#include <iostream>
#include "Address.h"
#include "Analysis.h"
#include <exception>
//#include "AvlTree.h"
#include <cstring>
#include <cstdlib>
#include "calcparam.h"
#include "params.h"
using namespace std;

int run(const char *path)
{
	try
	{
		Analysis analis(path);
		for (int i = 0; i < analis.requests().size(); i++)
		{
			cout << analis[i].addr << endl;
		}
		Analysis::AddressAnalisys adAnalis(analis);
		adAnalis.calc_stack_dist();
		params_time pt = Analysis::TimeAnalisys::calc_params(Analysis::TimeAnalisys::DISTR, analis);
		//params_time pt2 = Analysis::TimeAnalisys::calc_params(Analysis::TimeAnalisys::MOMENTS, analis);
		FILE *f = fopen("res.txt", "w");
		for (int i = 0; i < pt.n; ++i)
		{
			fprintf(f, "%d %g\n", pt.position[i], pt.lambda[i]);
			//fprintf(f, "%d %g\n", pt2.position[i], pt2.lambda[i]);
		}
		fclose(f);
	}
	catch (exception e)
	{
		cerr << e.what() << endl;
		cerr << "Program terminated." << endl;
		system("pause");
	}
	/*const int NUM = 1000;
	for (int i = 0; i < NUM; i++)
	{
		char str[20];
		itoa(i, str, 10);
		Analysis analis(str);
		Analysis::TimeAnalisys t_analis(analis);
	}*/
	//system("pause");
	return 8;
}