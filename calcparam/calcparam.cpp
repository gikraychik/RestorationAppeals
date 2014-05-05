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
void run(char *path, params_time *pt, params_addr *pa, params_fixed *psize, params_fixed *ptype)
{
	//progress->value = 50;
	/*pa->m = new double[1];
	pa->k = new double[1];
	pa->m[0] = 2.3; pa->k[0] = 7.9;
	psize->p[0] = 2.478;
	psize->p[3] = 1.35;
	ptype->p[0] = 0.4;
	ptype->p[1] = 0.6;*/
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
		// addressed
		Analysis::AddressAnalisys adAnalis(analis);
		adAnalis.calc_stack_dist();
		params_addr a = adAnalis.calc_params();
		pa->position = a.position;
		pa->k = a.k;
		pa->m = a.m;
		pa->n = a.n;
		// time
		params_time pt1 = Analysis::TimeAnalisys::calc_params(Analysis::TimeAnalisys::DISTR, analis);
		pt->lambda = pt1.lambda; pt->position = pt1.position; pt->n = pt1.n;
		// size
		const int MAGIC_NUMBER = 5;
		params_fixed s = Analysis::FixedAnalisys::calc_params_size(analis);
		for (int i = 0; i < MAGIC_NUMBER; ++i)
			psize->p[i] = s.p[i];
		// type
		params_fixed t = Analysis::FixedAnalisys::calc_params_type(analis);
		for (int i = 0; i < MAGIC_NUMBER; ++i)
			ptype->p[i] = t.p[i];
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