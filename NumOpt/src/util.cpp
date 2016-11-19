#include <Eigen/Dense>
#include "util.hpp"

using Eigen::MatrixXf;

vector<vector<double> > inverse(vector<vector<double> > m) {
  int dim = m.size();
  MatrixXf m_(dim, dim);
  for (int i=0; i<dim; i++)
    for (int j=0; j<dim; j++)
      m_(i, j) = m[i][j];
  MatrixXf inv_ = m_.inverse();
  vector<vector<double> > inv(dim, vector<double>(dim));
  for (int i=0; i<dim; i++)
    for (int j=0; j<dim; j++)
      inv[i][j] = inv_(i, j);
  return inv;
}

vector<vector<double> > pseudo_inv(vector<vector<double> > m) {
  int dim = m.size();
  MatrixXf m_(dim, dim);
  for (int i=0; i<dim; i++)
    for (int j=0; j<dim; j++)
      m_(i, j) = m[i][j];
  MatrixXf inv_ = m_.partialPivLu().solve(MatrixXf::Identity(dim, dim));
  vector<vector<double> > inv(dim, vector<double>(dim));
  for (int i=0; i<dim; i++)
    for (int j=0; j<dim; j++)
      inv[i][j] = inv_(i, j);
  return inv;  
}