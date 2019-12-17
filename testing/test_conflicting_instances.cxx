#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <heat.hxx>
#include <bmi.hxx>
#include <bmi_heat.hxx>


int
main (void)
{
  BmiHeat model1;
  BmiHeat model2;

  model1.Initialize("");
  std::cout << "Model 1 initialized" << std::endl;

  model2.Initialize("");
  std::cout << "Model 2 initialized" << std::endl;

  /* Does changing values in model1 change them in model2? */
  {
    std::string name = "plate_surface__temperature";
    int i;
    int inds[5] = {11, 22, 44, 88, 176};
    double vals[5] = {1, 2, 4, 8, 16};
    double *p1, *p2;

    p1 = (double *)model1.GetValuePtr(name);
    fprintf(stdout, "Model 1 temperatures, initial...\n");
    for (i=0; i<5; i++) {
      fprintf (stdout, "%8.2f ", p1[inds[i]]);
    }
    fprintf (stdout, "\n");

    model1.SetValueAtIndices(name, inds, 5, vals);
    fprintf(stdout, "Model 1 temperatures, changed...\n");
    for (i=0; i<5; i++) {
      fprintf (stdout, "%8.2f ", p1[inds[i]]);
    }
    fprintf (stdout, "\n");

    p2 = (double *)model2.GetValuePtr(name);
    fprintf(stdout, "Model 2 temperatures...\n");
    for (i=0; i<5; i++) {
      fprintf (stdout, "%8.2f ", p2[inds[i]]);
    }
    fprintf (stdout, "\n");

    for (i=0; i<5; i++) {
      if (p1[inds[i]] != p2[inds[i]])
        fprintf (stdout, "%d:PASS ", i+1);
    }
    fprintf (stdout, "\n");
  }

  model1.Finalize();
  std::cout << "Model 1 finalized" << std::endl;

  model2.Finalize();
  std::cout << "Model 2 finalized" << std::endl;

  return bmi::BMI_SUCCESS;
}
