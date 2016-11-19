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
  cout << "initial value of x: " << endl;
  for (auto i: x)
    cout << i << "\t";
  cout << endl;
  
  vector<double> g_value = toy_grad(x);
  
  // test line search
  vector<double> p(2);
  for (int i=0; i<2; i++)
    p[i] = -g_value[i];
  vector<double> x2 = line_search(x, p, toy_func, g_value);
  cout << "\nvalue of x in the second iteration:" << endl;
  for (auto i: x2)
    cout << i << "\t";
  cout << endl;
  
  // test gradient descent with line search
  vector<double> x_min = gd_ls(x, toy_func, toy_grad);
  cout  << "\noptimal value of x: " << endl;
  for (auto i: x_min)
    cout << i << "\t";
  cout << endl;
  
  return 0;
}
