#include <heat/bmi_heat.hxx>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int
main (void)
{
  BmiHeat model;
  char name[2048];

  fprintf (stdout, "Initializing... ");
  model.Initialize ("");
  fprintf (stdout, "Done\n");

  model.GetComponentName(name);
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
      model.GetCurrentTime(&now);

      fprintf (stdout, "Time: %f\n", now);
    }
    model.GetEndTime(&then);
    model.UpdateUntil(then);
    model.GetCurrentTime(&now);

    fprintf (stdout, "Time: %f\n", now);
    fprintf (stdout, "Done\n");
  }

  fprintf (stdout, "Finalizing... ");
  model.Finalize ();
  fprintf (stdout, "Done\n");

  return EXIT_SUCCESS;
}
