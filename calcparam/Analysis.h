#pragma once
#include <exception>
#include "Req.h"
#include <vector>
#include "IO_Manager.h"
#include <set>
#include "params.h"
//#include "AvlTree.h"

class Analysis
{
public:
	Analysis(void);
	Analysis(const char *filename);
	~Analysis(void);

	void calc_stack_dist(void);

	/* Access to array elements */
	inline std::vector<Req> requests(void) const;
	Req req(int i) const;
	inline Address addr(int i) const;
	inline MyTime time(int i) const;
	inline req_size size(int i) const;
	inline req_type type(int i) const;
	inline int len(void) const;

	Req operator [] (int i) const;  // acceses a request at index i

	class AddressAnalisys
	{
	public:
		AddressAnalisys(void);
		AddressAnalisys(const Analysis &analis);
		void calc_stack_dist(void);
		params_addr calc_params(void);
		inline std::vector<Address> addresses(void) const;
	protected:
		std::vector<Address> v;		// represents stack distances
	private:

	};
	class TimeAnalisys
	{
	public:
		TimeAnalisys(void);
		enum method { MOMENTS, DISTR };
		static params_time calc_params(method mode, const Analysis &analis);
	private:
		static double calc_lambda_moments(unsigned int *data, int len);
		static double calc_lambda_distr(unsigned int *data, int len, double a, double b);
	};
	// analises size and type
	// as they're descreate values
	class FixedAnalisys
	{
	public:
		FixedAnalisys(void);
		static params_fixed calc_params_size(const Analysis &analis);
		static params_fixed calc_params_type(const Analysis &analis);
	};
private:
	std::fstream input;
	std::vector<Req> v;
};

class MyMath
{
public:
	MyMath(void);
	static std::pair<double, double> solve_square_equation(double a, double b, double c);
};

