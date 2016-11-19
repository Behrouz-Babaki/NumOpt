#include <iostream>
#include <vector>

#include "opt.hpp"

using std::cout;
using std::endl;
using std::vector;

// x^2 + 2y^2
double toy_func (vector<double> arg) {
  return arg[0]*arg[0] + 2*arg[1]*arg[1];
}

// (2x, 4y)
vector<double> toy_grad(vector<double> arg) {
  vector<double> g(2);
  g[0] = 2*arg[0];
  g[1] = 4*arg[1];
  return g;
}

int main(void) {
  vector<double> x {14.5, 15.5};
  vector<double> g = toy_grad(x);
  vector<double> p(2);
  for (int i=0; i<2; i++)
    p[i] = -g[i];
  vector<double> x2 = line_search(x, p, toy_func, g);
  vector<double> x_min = gd_ls(x, toy_func, toy_grad);
  for (auto i: x_min)
    cout << i << "\t";
  cout << endl;
  return 0;
}
