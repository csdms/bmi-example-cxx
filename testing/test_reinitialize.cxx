#include <bmi_heat.hxx>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int
main (void)
{
  int i;
  const int n_steps = 3;
  BmiHeat model;
  char name[2048];

  for (int i=0; i<n_steps; i++) {
    fprintf (stdout, "Reinitialize %d\n", i+1);

    model.Initialize("");

    model.GetComponentName(name);
    std::cout << name << std::endl;

    model.Finalize();
  }

  return EXIT_SUCCESS;
}
