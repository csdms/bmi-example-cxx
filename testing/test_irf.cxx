#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <heat.hxx>
#include <bmi.hxx>
#include <bmi_heat.hxx>


int
main (void)
{
  BmiHeat model;
  std::string name;

  fprintf (stdout, "Initializing... ");
  model.Initialize ("");
  fprintf (stdout, "Done\n");

  name = model.GetComponentName();
  std::cout << name << std::endl;

  {
    const int n_steps = 10;
    double now;
    double then;

    fprintf (stdout, "Running...\n");
    for (int i = 0; i < n_steps; i++) {
      fprintf(stderr, "Updating\n"); fflush(stderr);
      model.Update();
      fprintf(stderr, "Updated\n"); fflush(stderr);
      now = model.GetCurrentTime();

      fprintf (stdout, "Time: %f\n", now);
    }
    then = model.GetEndTime();
    model.UpdateUntil(then);
    now = model.GetCurrentTime();

    fprintf (stdout, "Time: %f\n", now);
    fprintf (stdout, "Done\n");
  }

  fprintf (stdout, "Finalizing... ");
  model.Finalize ();
  fprintf (stdout, "Done\n");

  return EXIT_SUCCESS;
}
