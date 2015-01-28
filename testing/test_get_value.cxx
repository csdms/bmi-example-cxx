#include <heat/bmi_heat.hxx>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>


void print_var_values(BmiHeat model, const char *var_name);
void print_var_column(BmiHeat model, const char *var_name, int colno);

int
main (void)
{
  int i;
  const int n_steps = 10;
  BmiHeat model;
  int size;
  char name[2048];
  int rank;

  model.Initialize("");

  model.GetComponentName(name);
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
  int * shape;
  int rank;

  model.GetVarRank(name, &rank);

  shape = new int[rank];
  model.GetGridShape(name, shape);

  {
    int * inds = (int*)malloc(sizeof(int)*shape[0]);
    double * col = NULL;

    inds[0] = colno;
    for (int i=1; i<shape[0]; i++)
      inds[i] = inds[i-1] + shape[1];

    col = new double[shape[0]];
    model.GetValueAtIndices(name, (char*)col, inds, shape[0]);

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
  int * shape;
  int rank;
  int size;

  model.GetVarRank(var_name, &rank);

  shape = new int[rank];
  model.GetGridShape(var_name, shape);
  model.GetVarSize(var_name, &size);

  var = new double[size];
  model.GetValue(var_name, (char*)var);

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
