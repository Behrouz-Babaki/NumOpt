#include "opt.hpp"

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