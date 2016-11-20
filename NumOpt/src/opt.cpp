#include <cmath>

#include "opt.hpp"
#include "util.hpp"

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

double get_largest_dimension(const vector<double>& p) {
  int dim = p.size();
  int max_dim = 0;
  for (int i=1; i<dim; i++)
    if (fabs(p[i]) > fabs(p[max_dim]))
      max_dim = i;
  return fabs(p[max_dim]);
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
  
  double m = get_largest_dimension(p);

  while(m > tolerance) {
    x = line_search(x, p, f, g_value);
    
    g_value = g(x);
    for (int i=0; i<dim; i++)
      p[i] = -g_value[i];
    
    m = get_largest_dimension(p);
  }
  return x;
}

vector<double> newton(vector<double> x,
		      function<vector<double>(vector<double>)> g,
		      function<vector< vector<double> >(vector<double>)> h,
		      double tolerance) {
  int dim = x.size();
  vector<double> h_inv_g(dim);
  
  vector<double> g_value = g(x);
  double m = get_largest_dimension(g_value);
  while (m > tolerance) {
    vector<vector<double> > h_value = h(x);
    vector<vector<double> > h_inv = inverse(h_value);
    for (int i=0; i<dim; i++) {
      double entry = 0;
      for (int j=0; j<dim; j++)
	entry += h_inv[i][j] * g_value[j];
      h_inv_g[i] = entry;
    }
    
    for (int i=0; i<dim; i++)
      x[i] -= h_inv_g[i];
    m = get_largest_dimension(x);
  }
  
  return x;
}