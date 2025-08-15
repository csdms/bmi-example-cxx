#include <iostream>
#include <stdlib.h>
#include <vector>
#include <assert.h>
#include <math.h>

#include <heat.hxx>
#include <bmi.hxx>
#include <bmi_heat.hxx>


int
main(void)
{
  BmiHeat model;
  double time_expected = 0.0;
  double tolerance = 0.01;

  {
    double time;

    model.Initialize("");
    fprintf(stdout, "Model initialized\n");
    time = model.GetCurrentTime();
    model.Finalize();
    fprintf(stdout, "Model finalized\n");

    fprintf(stdout, "time = %f\n", time);
    assert(fabs(time - time_expected) <= tolerance && "Unexpected current time value");
  }

  {
    double time;

    model.Initialize("config.txt");
    fprintf(stdout, "Model initialized\n");
    time = model.GetCurrentTime();
    model.Finalize();
    fprintf(stdout, "Model finalized\n");

    fprintf(stdout, "time = %f\n", time);
    assert(fabs(time - time_expected) <= tolerance && "Unexpected current time value");
  }
}
