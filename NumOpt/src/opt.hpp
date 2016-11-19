#pragma once

#include <vector>
#include <functional>

using std::vector;
using std::function;

vector<double> line_search(vector<double> x,
			   vector<double> p,
			   function<double(vector<double>)> f,
			   vector<double> g,
			   double gamma=0.01,
			   double beta=0.6);