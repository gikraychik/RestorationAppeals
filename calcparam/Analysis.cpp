#include "stdafx.h"
#include "Analysis.h"
#include "IO_Manager.h"
#include <limits>
#include <set>
#include <map>
#include <vector>
#include <fstream>
#include "AvlIntTree.h"
#include <list>
#undef max

Analysis::Analysis(void)
{
}

Analysis::Analysis(const char *filename)
{
	IO_Manager *m = new IO_Manager(std::string(filename));
	while (Req *req = m->read_next_req())
	{
		v.push_back(*req);
		delete req;
	}
	delete m;
}

Analysis::~Analysis(void)
{
}

void Analysis::calc_stack_dist(void)
{

}

int Analysis::len(void) const
{
	return v.size();
}
std::vector<Req> Analysis::requests(void) const
{
	return v;
}
Req Analysis::req(int i) const
{
	if ((i < 0) || (i >= v.size()))
	{
		std::cerr << "Req Analysis::req(int i) const : index out of range" << std::endl;
		//throw std::exception("Req Analysis::req(int i) const : index out of range");
	}
	return v[i];
}
Address Analysis::addr(int i) const
{
	return req(i).addr;
}
MyTime Analysis::time(int i) const
{
	return req(i).time;
}
req_size Analysis::size(int i) const
{
	return req(i).size;
}
req_type Analysis::type(int i) const
{
	return req(i).type;
}
Req Analysis::operator [] (int i) const
{
	return req(i);
}

Analysis::AddressAnalisys::AddressAnalisys(void) : v() {}
Analysis::AddressAnalisys::AddressAnalisys(const Analysis &analis)
{
	for (int i = 0; i < analis.requests().size(); i++)
	{
		v.push_back(analis.addr(i));
	}
}
std::vector<Address> Analysis::AddressAnalisys::addresses(void) const
{
	return v;
}

void Analysis::AddressAnalisys::calc_stack_dist(void)
{
	const unsigned int M = 1000;		// size of stack
	const unsigned int inf = std::numeric_limits<unsigned int>::max();
	const unsigned int cache_size = v.size();			// amount of links in stack
	//std::set<Address> cache;
	//std::map<Address, int> index;						// for each address there is an index of it's last use
	AvlIntTree avl(AvlKey(0, cache_size - 1), 0);		// in the beginning avl tree contains only one node	
	avl.par = NULL;
	//AvlIntTree avl;
	/*for (int i = 0; i < cache_size; i++)
	{
		std::set<Address>::iterator itr = cache.find(v[i]);
		if (cache.size() < M)
		{
			if (itr == cache.end())				// v[i] is not in the stack
			{
 				cache.insert(v[i]);
				index[v[i]] = i;
				int delta = 0;
				avl.add_new_elem(i, delta);
				v[i].dist = inf;
			}
			else								// v[i] is already in the stack
			{
				int prev_index = index[*itr];
				v[i].dist = avl.calc_stack_dist(prev_index, i, cache_size);
				int delt = 0;
				if (i == v.size() - 1) { break; }
				avl.add_new_elem(i, delt);
				unsigned int delta = 0;
				avl.restore(prev_index, delta);		// removes prev_index from the avl tree
				index[*itr] = i;
			}
		}
		else
		{
			if (itr == cache.end())
			{

			}
		}
	}*/
	std::list<Address> l;
	std::set<Address> cache;
	std::map<Address, std::list<Address>::const_iterator> index; 
	for (int i = 0; i < cache_size; ++i)
	{
		//std::list<Address>::iterator itr;
		std::set<Address>::iterator itr;
		int dist = 0;
		/*for (itr = l.begin(); itr != l.end(); itr++)
		{
			if (itr->get_val() == v[i].get_val())
			{
				break;
			}
			dist++;
		}*/
		//bool wasFound = (itr != l.end());
		itr = cache.find(v[i]);
		bool wasFound = (itr == cache.end());
		if (l.size() < M)
		{
			if (!wasFound)		// not found in stack
			{
				l.push_front(v[i]);
				cache.insert(v[i]);
				index[v[i]] = l.begin();
			}
			else					// found in stack
			{
				l.erase(index[*itr]);
				l.push_front(v[i]);
				cache.insert(v[i]);
				cache.erase(*itr);
				index[v[i]] = l.begin();
				index.erase(*itr);
			}
		}
		else						// if stack is fullfilled
		{
			if (!wasFound)		// not found in stack
			{
				cache.erase(l.back());
				index.erase(l.back());
				l.pop_back();
				l.push_front(v[i]);
				cache.insert(v[i]);
				index[v[i]] = l.begin();
			}
			else					// found in stack
			{
				l.erase(index[*itr]);
				l.push_front(v[i]);
				index[v[i]] = l.begin();
			}
		}
		v[i].dist = (wasFound) ? dist : inf;
	}
}
// allocates memory but doesn't free it
params_addr Analysis::AddressAnalisys::calc_params(void)
{
	int len = v.size();
	double sum1 = 0.0;
	double sum2 = 0.0;
	for (int i = 0; i < len; ++i)
	{
		sum1 += v[i].get_dist();
		sum2 += v[i].get_dist() * v[i].get_dist();
	}
	double E = sum1 / len;										// ���. ��������
	double D = sum2 / len - (sum1 / len) * (sum1 / len);		// ���������
	double k = (MyMath::solve_square_equation(D, -2*D, -E*E)).second;			// �������� ���������� �� ������
	if (k == 0) throw -1;										// division by zero
	double a = E * (k - 1) / k;
	
	int *pos = new int[1];
	double *kk = new double[1];
	double *mm = new double[1];
	pos[0] = 0; kk[0] = k; mm[0] = a;
	params_addr *pa = new params_addr();
	pa->position = pos;
	pa->k = kk;
	pa->m = mm;
	pa->n = 1;
	return *pa;
}
params_time Analysis::TimeAnalisys::calc_params(method mode, const Analysis &analis)
{
	int len = analis.len();
	unsigned int *data = new unsigned int[len-1];
	int *pos = new int[1];
	double *l = new double[1];
	for (int i = 1; i < len; ++i)
	{
		data[i-1] = analis.time(i).get_val() - analis.time(i-1).get_val();
	}
	double lambda = 0.0;
	lambda = (mode == MOMENTS) ? calc_lambda_moments(data, len) : calc_lambda_distr(data, len, 0.000001, 0.09);
	pos[0] = 2; l[0] = lambda;
	params_time result(pos, l, 1);
	delete[] data;
	delete[] pos;
	delete[] l;
	return result;
}
params_fixed Analysis::FixedAnalisys::calc_params_size(const Analysis &analis)
{
	const int MAGIC_NUMBER = 5;
	double p[MAGIC_NUMBER] = {0.0, 0.0, 0.0, 0.0, 0.0};		// magic number see in params.h params_fixed
	int len = analis.len();
	for (int i = 0; i < len; ++i)
	{
		unsigned short x = analis[i].size;
		if (x >= MAGIC_NUMBER) continue;
		p[x]++;
	}
	params_fixed *psize = new params_fixed();
	for (int i = 0; i < MAGIC_NUMBER; ++i)
		psize->p[i] = p[i] / len;
	return *psize;
}
// must be the same as calc_params_size
params_fixed Analysis::FixedAnalisys::calc_params_type(const Analysis &analis)
{
	const int MAGIC_NUMBER = 5;
	double p[MAGIC_NUMBER] = {0.0, 0.0, 0.0, 0.0, 0.0};		// magic number see in params.h params_fixed
	int len = analis.len();
	for (int i = 0; i < len; ++i)
	{
		req_type x = analis[i].type;
		if (x == read) { p[0]++; }
		else if (x == write) { p[1]++; }
	}
	params_fixed *ptype = new params_fixed();
	for (int i = 0; i < MAGIC_NUMBER; ++i)
		ptype->p[i] = p[i] / len;
	return *ptype;
}
Analysis::TimeAnalisys::TimeAnalisys(void)
{
	/*std::vector <unsigned int> data(analis.len()-1, 0);
	for (int i = 1; i < analis.len(); i++)
	{
		data[i-1] = analis.time(i).get_val() - analis.time(i-1).get_val();
	}
	double lambda0 = calc_lambda_moments(data);
	double delta = 0.07;  // 0.05
	double lambda = calc_lambda_distr(data, lambda0 - delta, lambda0 + delta);
	FILE *f = fopen("data7_mixed.txt", "a");
	fprintf(f, "%g\n", lambda);
	std::cout << lambda << std::endl;
	fclose(f);
	//std::cout << lambda << std::endl;
	//calc_lambda_distr(data);
	*/
}
double Analysis::TimeAnalisys::calc_lambda_moments(unsigned int *data, int len)
{
	double sum = 0.0;
	for (int i = 0; i < len; ++i)
		sum += data[i];
	return (double)len / (double)sum;
}
double Analysis::TimeAnalisys::calc_lambda_distr(unsigned int *data, int len, double a, double b)
{
	double sum = 0.0;
	//const double a = 0.0000001;			// must be configured
	//const double b = 0.09;				// must be configured
	const double n = len;
	for (int i = 0; i < n; i++)
		sum += data[i];
	//std::cout << (a*sum*n)/(2 + sum*n) << std::endl;
	std::pair<double, double> res = MyMath::solve_square_equation(sum, -(n + 2 + a*sum), a*n);
	//if ((res.first >= a) && (res.first <= b)) { std::cout << res.first; }
	//else if ((res.second >= a) && (res.second <= b)) { std::cout << res.second; }
	//else { std::cout << -1; }
	//std::cout << res.first << " " << res.second << std::endl;
	//std::cout << std::endl;
	return res.second;
}
std::pair<double, double> MyMath::solve_square_equation(double a, double b, double c)
{
	double d = b*b - 4*a*c;
	if (d < 0) { throw 1; }
	return std::pair<double, double>((-b - sqrt(d)) / (2*a), (-b + sqrt(d)) / (2*a));
}
/*
	Definition of class AvlKey is over.
*/