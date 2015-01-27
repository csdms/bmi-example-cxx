#ifndef BMI_HEAT_H_INCLUDED
#define BMI_HEAT_H_INCLUDED

#include <string>
#include <heat/heat.hxx>


class BmiHeat {
  public:
    BmiHeat() {
      const char *input_var_names[] = {
        "plate_surface__temperature",
        NULL
      };
      const char *output_var_names[] = {
        "plate_surface__temperature",
        NULL
      };
      input_var_name_count = 1;
      output_var_name_count = 1;
    };

    void Initialize (std::string config_file);
    void Update();
    void UpdateUntil(double);
    void UpdateFrac(double);
    void Finalize();

    void GetComponentName(char *name);
    void GetInputVarNameCount(int * count);
    void GetOutputVarNameCount(int * count);
    void GetInputVarNames(char** names);
    void GetOutputVarNames(char** names);

    void GetVarType(const char * name, char* type);
    void GetVarItemsize(const char * name, int* itemsize);
    void GetVarUnits(const char * name, char* units);
    void GetVarRank(const char * name, int* rank);
    void GetVarSize(const char * name, int* size);
    void GetVarNbytes(const char * name, int* nbytes);

    void GetCurrentTime(double *time);
    void GetStartTime(double *start);
    void GetEndTime(double *end);
    void GetTimeStep(double *dt);
    void GetTimeUnits(char *units);

    void GetValue(const char *, char *);
    void GetValuePtr(const char *, char **);
    void GetValueAtIndices(const char *, char *dest, int * inds, int len);

    void SetValue(const char *, char *);
    void SetValuePtr(const char *, char **);
    void SetValueAtIndices(const char * name, int * inds, int len, char *src);

    void GetGridType(const char *, char *);
    void GetGridShape(const char *, int *);
    void GetGridSpacing(const char *, double *);
    void GetGridOrigin(const char *, double *);

    void GetGridX(const char *, double *);
    void GetGridY(const char *, double *);

  private:
    heat::Heat _model;
    int input_var_name_count;
    int output_var_name_count;

    char** input_var_names;
    char** output_var_names;
};

#endif
