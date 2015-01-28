#include <heat/bmi_heat.hxx>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void print_var_info (BmiHeat model, char *var);

int
main (void)
{
  BmiHeat model;
  char name[2048];

  model.Initialize("");

  model.GetComponentName(name);
  std::cout << name << std::endl;

  {
    int number_of_names;
    char **names;

    model.GetInputVarNameCount(&number_of_names);
    names = new char*[number_of_names];
    for (int i=0; i<number_of_names; i++) {
      names[i] = new char[2048];
    }

    model.GetInputVarNames(names);
    for (int i=0; i<number_of_names; i++)
      print_var_info(model, names[i]);

    model.GetOutputVarNameCount(&number_of_names);
    names = new char*[number_of_names];
    for (int i=0; i<number_of_names; i++) {
      names[i] = new char[2048];
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
  char type[2048];
  char units[2048];
  int rank;

  model.GetVarType(var, type);
  model.GetVarUnits(var, units);
  model.GetVarRank(var, &rank);

  shape = new int[rank];
  spacing = new double[rank];
  origin = new double[rank];

  model.GetGridShape(var, shape);
  model.GetGridSpacing(var, spacing);
  model.GetGridOrigin(var, origin);

  fprintf (stdout, "\n");
  fprintf (stdout, "Variable info\n");
  fprintf (stdout, "=============\n");
  fprintf (stdout, "Name: %s\n", var);
  fprintf (stdout, "Type: %s\n", type);
  fprintf (stdout, "Units: %s\n", units);
  fprintf (stdout, "Rank: %d\n", rank);
  fprintf (stdout, "Dimension: %d x %d\n", shape[0], shape[1]);
  fprintf (stdout, "Resolution: %f x %f\n", spacing[0], spacing[1]);
  fprintf (stdout, "Corner: %f x %f\n", origin[0], origin[1]);

  delete origin;
  delete spacing;
  delete shape;

  return;
}
