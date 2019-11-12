#include "bmi_heat.hxx"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>


void print_var_info (BmiHeat model, char *var);

int
main (void)
{
  BmiHeat model;
  char name[bmi::MAX_COMPONENT_NAME];

  model.Initialize("");

  model.GetComponentName(name);
  std::cout << name << std::endl;

  {
    int number_of_names;
    char **names;

    number_of_names = model.GetInputItemCount();
    names = new char*[number_of_names];
    for (int i=0; i<number_of_names; i++) {
      names[i] = new char[bmi::MAX_VAR_NAME];
    }

    model.GetInputVarNames(names);
    for (int i=0; i<number_of_names; i++)
      print_var_info(model, names[i]);

    number_of_names = model.GetOutputItemCount();
    names = new char*[number_of_names];
    for (int i=0; i<number_of_names; i++) {
      names[i] = new char[bmi::MAX_VAR_NAME];
    }

    model.GetOutputVarNames(names);
    for (int i=0; i<number_of_names; i++)
      print_var_info(model, names[i]);

  }

  model.Finalize();

  return EXIT_SUCCESS;
}

void
print_var_info(BmiHeat model, char *var)
{
  int *shape;
  double *spacing;
  double *origin;
  int grid;
  char type[bmi::MAX_TYPE_NAME];
  char units[bmi::MAX_UNITS_NAME];
  int rank;
  int size;
  int nbytes;
  char grid_type[bmi::MAX_TYPE_NAME];

  model.GetVarType(var, type);
  model.GetVarUnits(var, units);
  nbytes = model.GetVarNbytes(var);
  grid = model.GetVarGrid(var);
  rank = model.GetGridRank(grid);
  size = model.GetGridSize(grid);
  model.GetGridType(grid, grid_type);

  shape = new int[rank];
  spacing = new double[rank];
  origin = new double[rank];

  model.GetGridShape(grid, shape);
  model.GetGridSpacing(grid, spacing);
  model.GetGridOrigin(grid, origin);

  fprintf (stdout, "\n");
  fprintf (stdout, "Variable info\n");
  fprintf (stdout, "=============\n");
  fprintf (stdout, "Name: %s\n", var);
  fprintf (stdout, "Type: %s\n", type);
  fprintf (stdout, "Units: %s\n", units);
  fprintf (stdout, "Rank: %d\n", rank);
  fprintf (stdout, "Size: %d\n", size);
  fprintf (stdout, "Nbytes: %d\n", nbytes);
  fprintf (stdout, "Grid: %s\n", grid_type);
  fprintf (stdout, "Dimension: %d x %d\n", shape[0], shape[1]);
  fprintf (stdout, "Resolution: %f x %f\n", spacing[0], spacing[1]);
  fprintf (stdout, "Corner: (%f, %f)\n", origin[0], origin[1]);

  delete origin;
  delete spacing;
  delete shape;
}
