#include <heat/bmi_heat.hxx>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void print_var_names (BmiHeat model);

int
main (void)
{
  int i;
  const int n_steps = 10;
  BmiHeat model;
  char name[2048];

  model.Initialize("");

  model.GetComponentName(name);
  std::cout << name << std::endl;

  print_var_names (model);

  model.Finalize();

  return EXIT_SUCCESS;
}

void
print_var_names (BmiHeat model)
{
  char **names;
  int number_of_names;

  model.GetInputVarNameCount(&number_of_names);
  fprintf (stdout, "Number of input names: %d\n", number_of_names);

  names = new char*[number_of_names];
  for (int i=0; i<number_of_names; i++) {
    names[i] = new char[2048];
  }

  model.GetInputVarNames(names);
  for (int i=0; i<number_of_names; i++)
    fprintf (stdout, "%s\n", names[i]);
  fprintf (stdout, "\n");

  model.GetOutputVarNameCount(&number_of_names);
  fprintf (stdout, "Number of output names: %d\n", number_of_names);

  names = new char*[number_of_names];
  for (int i=0; i<number_of_names; i++) {
    names[i] = new char[2048];
  }

  model.GetOutputVarNames(names);
  for (int i=0; i<number_of_names; i++)
    fprintf (stdout, "%s\n", names[i]);
  fprintf (stdout, "\n");
}
