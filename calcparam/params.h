#pragma once
struct params_time
{
	params_time(void);
	params_time(const int *pos, const double *value, int n)	;	// n = len(pos)
	~params_time(void);
	inline void operator =(const params_time par);
	/*void operator =(params_time par)
	{
		this->n = n;
		for (int i = 0; i < n; ++i)
		{
			position[i] = par.position[i];
			lambda[i] = par.lambda[i];
		}
	}*/
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