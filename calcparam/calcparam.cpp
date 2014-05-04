// calcparam.cpp : Defines the exported functions for the DLL application.
//
#pragma once
#include "stdafx.h"
#include <iostream>
#include "Address.h"
#include "Analysis.h"
#include <exception>
#include "AvlTree.h"
#include <cstring>
#include <cstdlib>
#include "calcparam.h"
using namespace std;

void run()
{
	try
	{
		Analysis analis("100records");
		for (int i = 0; i < analis.requests().size(); i++)
		{
			cout << analis[i].addr << endl;
		}
		Analysis::AddressAnalisys adAnalis(analis);
		adAnalis.calc_stack_dist();
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
	system("pause");
}