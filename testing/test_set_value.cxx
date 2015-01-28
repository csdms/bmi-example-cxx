#include <heat/bmi_heat.hxx>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void print_matrix (double *m, int n_dims, int * shape);
void print_var_values (BmiHeat model, const char *var_name);

int
main (void)
{
  int i;
  const int n_steps = 10;
  BmiHeat model;
  double *new_vals = NULL;
  int *shape = NULL;
  int size;
  char name[2048];
  int rank;

  model.Initialize("");

  model.GetComponentName(name);
  std::cout << name << std::endl;

  model.GetVarRank("plate_surface__temperature", &rank);

  shape = new int[rank];
  model.GetGridShape("plate_surface__temperature", shape);

  model.GetValuePtr("plate_surface__temperature", (char**)(&new_vals));

  fprintf (stdout, "Values before set\n");
  fprintf (stdout, "=================\n");
  print_matrix (new_vals, rank, shape);

  new_vals[0] = -1;

  model.GetVarSize("plate_surface__temperature", &size);
  new_vals = new double[size];

  model.GetValue("plate_surface__temperature", (char*)new_vals);
  print_matrix (new_vals, rank, shape);

  new_vals[0] = 1.;

  model.SetValue("plate_surface__temperature", (char*)new_vals);

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

void
print_var_values(BmiHeat model, const char *var_name)
{
  int rank;
  int *shape;
  double *var = NULL;
  int i, j;

  model.GetVarRank(var_name, &rank);
  shape = new int[rank];

  model.GetGridShape(var_name, shape);

  var = new double[shape[0]*shape[1]];

  model.GetValue(var_name, (char*)var);

  fprintf (stdout, "Variable: %s\n", var_name);

  print_matrix (var, rank, shape);

  delete var;
  delete shape;

  return;
}
