#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <heat.hxx>
#include <bmi.hxx>
#include <bmi_heat.hxx>


void print_var_info (BmiHeat model, std::string var);

int
main (void)
{
  BmiHeat model;
  std::string name;

  model.Initialize("");

  name = model.GetComponentName();
  std::cout << name << std::endl;

  {
    int number_of_names;
    std::vector<std::string> names;

    number_of_names = model.GetInputItemCount();
    names = model.GetInputVarNames();
    for (int i=0; i<number_of_names; i++)
      print_var_info(model, names[i]);

    number_of_names = model.GetOutputItemCount();
    names = model.GetOutputVarNames();
    for (int i=0; i<number_of_names; i++)
      print_var_info(model, names[i]);
  }

  model.Finalize();

  return EXIT_SUCCESS;
}

void
print_var_info(BmiHeat model, std::string var)
{
  int grid;
  std::string type;
  std::string units;
  int rank;
  int size;
  int nbytes;
  std::string grid_type;

  type = model.GetVarType(var);
  units = model.GetVarUnits(var);
  nbytes = model.GetVarNbytes(var);
  grid = model.GetVarGrid(var);
  rank = model.GetGridRank(grid);
  size = model.GetGridSize(grid);
  grid_type = model.GetGridType(grid);

  std::vector<int> shape(rank);
  std::vector<double> spacing(rank);
  std::vector<double> origin(rank);

  model.GetGridShape(grid, shape.data());
  model.GetGridSpacing(grid, spacing.data());
  model.GetGridOrigin(grid, origin.data());

  fprintf (stdout, "\n");
  fprintf (stdout, "Variable info\n");
  fprintf (stdout, "=============\n");
  fprintf (stdout, "Name: %s\n", var.c_str());
  fprintf (stdout, "Type: %s\n", type.c_str());
  fprintf (stdout, "Units: %s\n", units.c_str());
  fprintf (stdout, "Rank: %d\n", rank);
  fprintf (stdout, "Size: %d\n", size);
  fprintf (stdout, "Nbytes: %d\n", nbytes);
  fprintf (stdout, "Grid: %s\n", grid_type.c_str());
  fprintf (stdout, "Dimension: %d x %d\n", shape[0], shape[1]);
  fprintf (stdout, "Resolution: %f x %f\n", spacing[0], spacing[1]);
  fprintf (stdout, "Corner: (%f, %f)\n", origin[0], origin[1]);
}
