#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <heat.hxx>
#include <bmi.hxx>
#include <bmi_heat.hxx>


void print_var_values(BmiHeat model, const char *var_name);
void print_var_column(BmiHeat model, const char *var_name, int colno);

int
main (void)
{
  int i;
  const int n_steps = 10;
  BmiHeat model;
  int size;
  std::string name;
  int rank;

  model.Initialize("");

  name = model.GetComponentName();
  std::cout << name << std::endl;

  for (i = 0; i<n_steps; i++)
  {
    fprintf (stdout, "Values at time %d\n", i);
    fprintf (stdout, "==============\n");
    print_var_values(model, "plate_surface__temperature");

    model.UpdateUntil(i);
  }

  fprintf(stdout, "Values at time %d\n", i);
  fprintf(stdout, "==============\n");
  print_var_values(model, "plate_surface__temperature");

  model.Finalize();

  return EXIT_SUCCESS;
}

void
print_var_column(BmiHeat model, const char *name, int colno)
{
  int grid;
  int * shape;
  int rank;

  grid = model.GetVarGrid(name);
  rank = model.GetGridRank(grid);

  shape = new int[rank];
  model.GetGridShape(grid, shape);

  {
    int * inds = (int*)malloc(sizeof(int)*shape[0]);
    double * col = NULL;

    inds[0] = colno;
    for (int i=1; i<shape[0]; i++)
      inds[i] = inds[i-1] + shape[1];

    col = new double[shape[0]];
    model.GetValueAtIndices(name, col, inds, shape[0]);

    fprintf (stdout, "Column %d: ", colno);
    for (int i=0; i<shape[0]; i++)
      fprintf (stdout, "%f ", col[i]);
    fprintf (stdout, "\n");

    free(col);
    free(inds);
  }

  delete shape;

  return;
}

void
print_var_values(BmiHeat model, const char *var_name)
{
  double *var = NULL;
  int i, j;
  int grid;
  int * shape;
  int rank;
  int size;

  grid = model.GetVarGrid(var_name);
  rank = model.GetGridRank(grid);
  size = model.GetGridSize(grid);

  shape = new int[rank];
  model.GetGridShape(grid, shape);

  var = new double[size];
  model.GetValue(var_name, var);

  fprintf (stdout, "Variable: %s\n", var_name);
  fprintf (stdout, "Number of dimension: %d\n", rank);
  fprintf (stdout, "Shape: %d x %d\n", shape[0], shape[1]);
  fprintf (stdout, "================\n");

  for (i=0; i<shape[0]; i++) {
    for (j=0; j<shape[1]; j++)
      fprintf (stdout, "%f ", var[i * shape[1] + j]);
    fprintf (stdout, "\n");
  }

  print_var_column(model, var_name, 1);
  print_var_column(model, var_name, shape[1] - 2);

  delete shape;

  return;
}
