#include <stdio.h>

#include <string>
#include <cstring>
#include <cstdlib>
#include <bmi_heat.hxx>
#include <heat.hxx>


void BmiHeat::
Initialize (std::string config_file)
{
  if (config_file.compare("") != 0 )
    this->_model = heat::Heat(config_file);
}


void BmiHeat::
Update()
{
  this->UpdateFrac(1.);
}


void BmiHeat::
UpdateUntil(double t)
{
  double time;
  double dt;

  this->GetCurrentTime(&time);
  this->GetTimeStep(&dt);

  {
    const int n_steps = (t - time) / dt;

    for (int n=0; n<n_steps; n++)
      this->Update();

    this->UpdateFrac(n_steps - int(n_steps));
  }
}


void BmiHeat::
UpdateFrac(double time_frac)
{
  double dt = 0.;

  this->GetTimeStep(&dt);
  this->_model.dt = time_frac * dt;
  this->_model.advance_in_time();
  this->_model.dt = dt;
}


void BmiHeat::
Finalize()
{
  this->_model.~Heat();
}


void BmiHeat::
GetVarType(const char * name, char * type)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    strncpy(type, "double", 2048);
  else
    strncpy(type, "", 2048);
}


void BmiHeat::
GetVarItemsize(const char *name, int * itemsize)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    *itemsize = sizeof(double);
  else
    *itemsize = 0;
}


void BmiHeat::
GetVarUnits(const char * name, char * units)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    strncpy(units, "meter", 2048);
  else
    strncpy(units, "", 2048);
}


void BmiHeat::
GetVarRank(const char *name, int * rank)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    *rank = 2;
  else
    *rank = -1;
}


void BmiHeat::
GetVarSize(const char * name, int* size)
{
  int shape[2];
  this->GetGridShape(name, shape);
  *size = shape[0] * shape[1];
}


void BmiHeat::
GetVarNbytes(const char * name, int* nbytes)
{
  int itemsize;
  int size;

  this->GetVarItemsize(name, &itemsize);
  this->GetVarSize(name, &size);
  *nbytes = itemsize * size;
}


void BmiHeat::
GetGridShape(const char * name, int *shape)
{
  if (strcmp(name, "plate_surface__temperature") == 0) {
    shape[0] = this->_model.shape[0];
    shape[1] = this->_model.shape[1];
  }
}


void BmiHeat::
GetGridSpacing (const char *name, double * spacing)
{
  if (strcmp(name, "plate_surface__temperature") == 0) {
    spacing[0] = this->_model.spacing[0];
    spacing[1] = this->_model.spacing[1];
  }

  return;
}


void BmiHeat::
GetGridOrigin (const char * name, double *origin)
{
  if (strcmp(name, "plate_surface__temperature") == 0) {
    origin[0] = this->_model.origin[0];
    origin[1] = this->_model.origin[1];
  }
}


void BmiHeat::
GetGridType (const char * name, char * type)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    strncpy(type, "uniform_rectilinear", 2048);
  else
    strncpy(type, "", 2048);
}


void BmiHeat::
GetValue (const char * name, char *dest)
{
  char * src = NULL;
  int nbytes = 0;

  this->GetValuePtr(name, &src);
  this->GetVarNbytes(name, &nbytes);
  
  memcpy (dest, src, nbytes);
}


void BmiHeat::
GetValuePtr (const char * name, char **dest)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    *dest = (char*)this->_model.z[0];
  else
    *dest = NULL;
}


void BmiHeat::
GetValueAtIndices (const char *name, char *dest, int * inds, int len)
{
  char * src = NULL;

  this->GetValuePtr(name, &src);

  if (src) {
    int i;
    int itemsize = 0;
    int offset;
    char *ptr;

    this->GetVarItemsize(name, &itemsize);

    for (i=0, ptr=dest; i<len; i++, ptr+=itemsize) {
      offset = inds[i] * itemsize;
      memcpy(ptr, src + offset, itemsize);
    }
  }
}


void BmiHeat::
SetValue (const char * name, char *src)
{
  char * dest = NULL;

  this->GetValuePtr(name, &dest);

  if (dest) {
    int nbytes = 0;
    this->GetVarNbytes(name, &nbytes);
    memcpy(dest, src, nbytes);
  }
}


void BmiHeat::
SetValueAtIndices (const char * name, int * inds, int len, char *src)
{
  char * dest = NULL;

  this->GetValuePtr(name, &dest);

  if (dest) {
    int i;
    int itemsize = 0;
    int offset;
    char *ptr;

    this->GetVarItemsize(name, &itemsize);

    for (i=0, ptr=src; i<len; i++, ptr+=itemsize) {
      offset = inds[i] * itemsize;
      memcpy(dest + offset, ptr, itemsize);
    }
  }
}


void BmiHeat::
GetComponentName (char * name)
{
  strncpy(name, "The 2D Heat Equation", 2048);
}


void BmiHeat::
GetInputVarNameCount(int * count)
{
  *count = this->input_var_name_count;
}


void BmiHeat::
GetOutputVarNameCount(int * count)
{
  *count = this->output_var_name_count;
}


void BmiHeat::
GetInputVarNames (char **names)
{
  for (int i=0; i<this->input_var_name_count; i++) {
    strncpy(names[i], (const char *)this->input_var_names[i], 2048);
  }
}


void BmiHeat::
GetOutputVarNames (char **names)
{
  for (int i=0; i<this->input_var_name_count; i++) {
    strncpy(names[i], (const char *)this->output_var_names[i], 2048);
  }
}


void BmiHeat::
GetStartTime (double * start) {
  *start = 0.;
}


void BmiHeat::
GetEndTime (double *end) {
  *end = this->_model.t_end;
}


void BmiHeat::
GetCurrentTime (double * time) {
  *time = this->_model.time;
}


void BmiHeat::
GetTimeUnits (char * units) {
  strncpy(units, "d", 2048);
}


void BmiHeat::
GetTimeStep (double * dt) {
  *dt = this->_model.dt;
}
