#pragma once
struct params_time
{
	params_time(void);
	params_time(const int *pos, const double *value, int n)	;	// n = len(pos)
	//~params_time(void);
	inline void operator =(const params_time par);
	/*
		specifies numbers where switching accured
		always start from 0
	*/
	int *position;
	/*
		specifies parameter lambda in each interval
		len (position) = len (lambda)
	*/
	double *lambda;
	int n;		// length of each array
};
struct my_test
{
	my_test(int *x, int n) : arr(x), n(n) {}
	int sum(void) { return *arr + n; }
	int *arr;
	int n;
};