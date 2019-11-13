#include <bmi_heat.hxx>

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
  std::string name;

  model.Initialize("");

  name = model.GetComponentName();
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

  number_of_names = model.GetInputItemCount();
  fprintf (stdout, "Number of input names: %d\n", number_of_names);

  names = new char*[number_of_names];
  for (int i=0; i<number_of_names; i++) {
    names[i] = new char[bmi::MAX_VAR_NAME];
  }

  model.GetInputVarNames(names);
  for (int i=0; i<number_of_names; i++)
    fprintf (stdout, "%s\n", names[i]);
  fprintf (stdout, "\n");

  number_of_names = model.GetOutputItemCount();
  fprintf (stdout, "Number of output names: %d\n", number_of_names);

  names = new char*[number_of_names];
  for (int i=0; i<number_of_names; i++) {
    names[i] = new char[bmi::MAX_VAR_NAME];
  }

  model.GetOutputVarNames(names);
  for (int i=0; i<number_of_names; i++)
    fprintf (stdout, "%s\n", names[i]);
  fprintf (stdout, "\n");
}
