#pragma once
#include "stdafx.h"
#include "params.h"
params_time::params_time(void) : position(0), lambda(0), n(0) {}
params_time::params_time(const int *pos, const double *value, int n)
{
	position = new int[n];
	lambda = new double[n];
	for (int i = 0; i < n; ++i)
	{
		position[i] = pos[i];
		lambda[i] = value[i];
	}
	this->n = n;
}
/*params_time::~params_time()
{
	delete[] position;
	delete[] lambda;
}*/
/*
	does not copy memory!
	copies only links!
*/
void params_time::operator =(const params_time par)
{
	this->position = par.position;
	this->lambda = par.lambda;
	this->n = n;
}

// Addresses
params_addr::params_addr(void) : position(0), m(0), k(0), n(0) {}
params_addr::params_addr(const int *pos, const double *m, const double *k, int n) : n(n)
{
	for (int i = 0; i < n; ++i)
	{
		this->position[i] = pos[i];
		this->m[i] = m[i];
		this->k[i] = k[i];
	}
}
void params_addr::operator =(const params_addr par)
{
	this->n = par.n;
	this->position = par.position;
	this->m = par.m;
	this->k = par.k;
}