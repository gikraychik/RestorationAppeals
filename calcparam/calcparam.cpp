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

void testing(my_test *t)
{
	//t->x = 23;
	//t->y = 'A';
	t->n = 10;
	t->arr = new int[t->n];
	for (int i = 0; i < t->n; ++i)
	{
		t->arr[i] = i;
	}
}
void run(char *path, params_time *pt)
{
	try
	{
		FILE *r = fopen("file.txt", "w");
		fprintf(r, path);
		fclose(r);
		Analysis analis(path);
		for (int i = 0; i < analis.requests().size(); i++)
		{
			cout << analis[i].addr << endl;
		}
		Analysis::AddressAnalisys adAnalis(analis);
		adAnalis.calc_stack_dist();
		params_time pt1 = Analysis::TimeAnalisys::calc_params(Analysis::TimeAnalisys::DISTR, analis);
		pt->lambda = pt1.lambda; pt->position = pt1.position; pt->n = pt1.n;
		FILE *f = fopen("res.txt", "w");
		for (int i = 0; i < pt->n; ++i)
		{
			fprintf(f, "%d %g\n", pt->position[i], pt->lambda[i]);
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
	//params_time pt;
	//return pt;
}