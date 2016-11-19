#include <iostream>

#include "opt.hpp"

using std::cout;
using std::endl;

vector<double> line_search(vector<double> x,
		   vector<double> p,
		   function<double(vector<double>)> f,
		   vector<double> g,
		   double gamma,
		   double beta) {
  int dim = x.size();
  double t = 1;
  
  double ggp = 0;
  for (int i=0; i<dim; i++)
    ggp += g[i] * p[i];
  ggp *= gamma;
  
  vector<double> arg(dim);
  for (int i=0; i<dim; i++)
    arg[i] = x[i] + t*p[i];
  
  while (f(arg) >= f(x) + t*ggp) {
    t *= beta;
    for (int i=0; i<dim; i++)
      arg[i] = x[i] * t*p[i];
  }
  return arg;
}

vector<double> gd_ls(vector<double> x,
		     function<double(vector<double>)> f,
		     function<vector<double>(vector<double>)> g,
		     double tolerance) {
  int dim = x.size();
  vector<double> g_value = g(x);
  vector<double> p(dim);
  for (int i=0; i<dim; i++)
    p[i] = -g_value[i];
  
  double max_dim = 0;
  for (int i=1; i<dim; i++)
    if (abs(p[i]) > abs(p[max_dim]))
      max_dim = i;
  double m = abs(p[max_dim]);

  while(m > tolerance) {
    x = line_search(x, p, f, g_value);
    
    g_value = g(x);
    for (int i=0; i<dim; i++)
      p[i] = -g_value[i];
    
    max_dim = 0;
    for (int i=1; i<dim; i++)
      if (abs(p[i]) > abs(p[max_dim]))
	max_dim = i;
    m = abs(p[max_dim]);
  }
  return x;
}