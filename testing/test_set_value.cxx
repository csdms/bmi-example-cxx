#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <heat.hxx>
#include <bmi.hxx>
#include <bmi_heat.hxx>


void print_matrix (double *m, int n_dims, int * shape);

int
main (void)
{
  int i;
  const int n_steps = 10;
  BmiHeat model;
  double *new_vals = NULL;
  int *shape = NULL;
  int size;
  std::string name;
  int rank;
  int grid;

  model.Initialize("config.txt");

  name = model.GetComponentName();
  std::cout << name << std::endl;

  grid = model.GetVarGrid("plate_surface__temperature");
  rank = model.GetGridRank(grid);

  shape = new int[rank];
  model.GetGridShape(grid, shape);

  new_vals = (double *)model.GetValuePtr("plate_surface__temperature");

  fprintf (stdout, "Values before set\n");
  fprintf (stdout, "=================\n");
  print_matrix (new_vals, rank, shape);

  new_vals[0] = -1;

  size = model.GetGridSize(grid);
  new_vals = new double[size];

  model.GetValue("plate_surface__temperature", new_vals);
  print_matrix (new_vals, rank, shape);

  new_vals[0] = 1.;

  model.SetValue("plate_surface__temperature", new_vals);

  fprintf (stdout, "Values after set\n");
  fprintf (stdout, "================\n");
  print_matrix (new_vals, rank, shape);


  delete shape;
  delete new_vals;

  model.Finalize ();

  return EXIT_SUCCESS;
}

void
print_matrix (double *m, int n_dims, int * shape)
{
  int i, j;

  fprintf (stdout, "Number of dimension: %d\n", n_dims);
  fprintf (stdout, "Shape: %d x %d\n", shape[0], shape[1]);
  fprintf (stdout, "================\n");

  for (i = 0; i < shape[0]; i++) {
    for (j = 0; j < shape[1]; j++)
      fprintf (stdout, "%f ", m[i*shape[1]+j]);
    fprintf (stdout, "\n");
  }
}
