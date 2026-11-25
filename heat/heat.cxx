#include <algorithm>
#include <cstddef>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include "heat.hxx"


void heat::Heat::
advance_in_time ()
{
  const int n_y = this->shape[0];
  const int n_x = this->shape[1];
  const double dx2 = this->spacing[1] * this->spacing[1];
  const double dy2 = this->spacing[0] * this->spacing[0];
  const double rx = this->alpha * this->dt / dx2;
  const double ry = this->alpha * this->dt / dy2;

  // Update the interior of the work grid and keep its boundaries at zero
  for (int i = 1; i < n_y - 1; i++) {
    for (int j = 1; j < n_x - 1; j++) {
      const std::size_t k = static_cast<std::size_t>(i) * n_x + j;
      temp_z[k] = z[k] + rx * (z[k - 1] - 2. * z[k] + z[k + 1])
                       + ry * (z[k - n_x] - 2. * z[k] + z[k + n_x]);
    }
  }

  // Keep the temperature pointer returned by BMI valid across time steps
  std::copy(temp_z.begin(), temp_z.end(), z.begin());
  this->time += this->dt;
}


heat::Heat::
Heat(std::string config_file)
{
  FILE * fp;
  double alpha = 1.;
  double t_end = 0.;
  int n_x = 0;
  int n_y = 0;

  fp = fopen (config_file.c_str (), "r");
  if (fp == NULL)
    throw std::runtime_error("Could not open configuration file: " + config_file);

  fscanf (fp, "%lf, %lf, %d, %d", &alpha, &t_end, &n_x, &n_y);

  fclose (fp);

  this->alpha = alpha;
  this->dt = 1. / (4. * alpha);
  this->t_end = t_end;
  this->time = 0.;
  this->shape[0] = n_y;
  this->shape[1] = n_x;
  this->spacing[0] = 1.;
  this->spacing[1] = 1.;
  this->origin[0] = 0.;
  this->origin[1] = 0.;

  this->_initialize_arrays();
}


void heat::Heat::
_initialize_arrays(void)
{
  const int n_y = this->shape[0];
  const int n_x = this->shape[1];
  const double top_x = n_x - 1;

  z.resize(static_cast<std::size_t>(n_y) * n_x);
  temp_z.resize(z.size(), 0.);

  for (std::size_t k = 0; k < z.size(); k++)
    z[k] = rand() * 1. / RAND_MAX * top_x * top_x * .5 - top_x * top_x * .25;

  for (int i = 0; i < n_y; i++) {
    const std::size_t row = static_cast<std::size_t>(i) * n_x;
    z[row] = 0.;
    z[row + n_x - 1] = 0.;
  }
  std::fill_n(z.begin(), n_x, 0.);
  std::fill_n(z.end() - n_x, n_x, 0.);
}


heat::Heat::
Heat()
{
  this->alpha = 1.;
  this->t_end = 10.;
  this->time = 0.;
  this->shape[0] = 10;
  this->shape[1] = 20;
  this->spacing[0] = 1.;
  this->spacing[1] = 1.;
  this->origin[0] = 0.;
  this->origin[1] = 0.;
  this->dt = 1. / (4. * this->alpha);

  this->_initialize_arrays();
}


void heat::Heat::
finalize()
{
  // Immediately release the memory used by the solution arrays
  std::vector<double>().swap(z);
  std::vector<double>().swap(temp_z);
  this->time = 0.;
}
