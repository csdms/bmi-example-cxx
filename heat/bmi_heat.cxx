#include <stdio.h>

#include <string>
#include <cstring>
#include <cstdlib>

#include "bmi_heat.hxx"
#include "heat.hxx"


void BmiHeat::
Initialize (std::string config_file)
{
  if (config_file.compare("") != 0 )
    this->_model = heat::Heat(config_file);
}


void BmiHeat::
Update()
{
  this->_model.advance_in_time();
}


void BmiHeat::
UpdateUntil(double t)
{
  double time;
  double dt;

  time = this->GetCurrentTime();
  dt = this->GetTimeStep();

  {
    const int n_steps = (t - time) / dt;
    double frac;

    for (int n=0; n<n_steps; n++)
      this->Update();

    frac = n_steps - int(n_steps);
    this->_model.dt = frac * dt;
    this->_model.advance_in_time();
    this->_model.dt = dt;
  }
}


void BmiHeat::
Finalize()
{
  this->_model.~Heat();
}


int BmiHeat::
GetVarGrid(const char * name)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    return 0;
  else
    return -1;
}


void BmiHeat::
GetVarType(const char * name, char * type)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    strncpy(type, "double", bmi::MAX_TYPE_NAME);
  else
    strncpy(type, "", bmi::MAX_TYPE_NAME);
}


int BmiHeat::
GetVarItemsize(const char *name)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    return sizeof(double);
  else
    return 0;
}


void BmiHeat::
GetVarUnits(const char * name, char * units)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    strncpy(units, "meters", bmi::MAX_UNITS_NAME);
  else
    strncpy(units, "", bmi::MAX_UNITS_NAME);
}


int BmiHeat::
GetVarNbytes(const char * name)
{
  int itemsize;
  int gridsize;

  itemsize = this->GetVarItemsize(name);
  gridsize = this->GetGridSize(this->GetVarGrid(name));
  
  return itemsize * gridsize;
}


void BmiHeat::
GetVarLocation(const char *name, char *location)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    strncpy(location, "node", bmi::MAX_UNITS_NAME);
  else
    strncpy(location, "", bmi::MAX_UNITS_NAME);
}


void BmiHeat::
GetGridShape(const int grid, int *shape)
{
  if (grid == 0) {
    shape[0] = this->_model.shape[0];
    shape[1] = this->_model.shape[1];
  }
}


void BmiHeat::
GetGridSpacing (const int grid, double * spacing)
{
  if (grid == 0) {
    spacing[0] = this->_model.spacing[0];
    spacing[1] = this->_model.spacing[1];
  }
}


void BmiHeat::
GetGridOrigin (const int grid, double *origin)
{
  if (grid == 0) {
    origin[0] = this->_model.origin[0];
    origin[1] = this->_model.origin[1];
  }
}


int BmiHeat::
GetGridRank(const int grid)
{
  if (grid == 0)
    return 2;
  else
    return -1;
}


int BmiHeat::
GetGridSize(const int grid)
{
  int shape[2];

  if (grid == 0) {
    this->GetGridShape(grid, shape);
    return shape[0] * shape[1];
  }
  else
    return -1;

}


void BmiHeat::
GetGridType (const int grid, char * type)
{
  if (grid == 0)
    strncpy(type, "uniform_rectilinear", bmi::MAX_VAR_NAME);
  else
    strncpy(type, "", bmi::MAX_VAR_NAME);
}


void BmiHeat::
GetGridX(const int grid, double *x)
{
  throw "Not implemented";
}


void BmiHeat::
GetGridY(const int grid, double *y)
{
  throw "Not implemented";
}


void BmiHeat::
GetGridZ(const int grid, double *z)
{
  throw "Not implemented";
}


int BmiHeat::
GetGridNodeCount(const int grid)
{
  throw "Not implemented";
}


int BmiHeat::
GetGridEdgeCount(const int grid)
{
  throw "Not implemented";
}


int BmiHeat::
GetGridFaceCount(const int grid)
{
  throw "Not implemented";
}


void BmiHeat::
GetGridEdgeNodes(const int grid, int *edge_nodes)
{
  throw "Not implemented";
}


void BmiHeat::
GetGridFaceEdges(const int grid, int *face_edges)
{
  throw "Not implemented";
}


void BmiHeat::
GetGridFaceNodes(const int grid, int *face_nodes)
{
  throw "Not implemented";
}


void BmiHeat::
GetGridNodesPerFace(const int grid, int *nodes_per_face)
{
  throw "Not implemented";
}


void BmiHeat::
GetValue (const char * name, void *dest)
{
  void * src = NULL;
  int nbytes = 0;

  src = this->GetValuePtr(name);
  nbytes = this->GetVarNbytes(name);

  memcpy (dest, src, nbytes);
}


void *BmiHeat::
GetValuePtr (const char * name)
{
  if (strcmp(name, "plate_surface__temperature") == 0)
    return (void*)this->_model.z[0];
  else
    return NULL;
}


void BmiHeat::
GetValueAtIndices (const char *name, void *dest, int *inds, int len)
{
  void * src = NULL;

  src = this->GetValuePtr(name);

  if (src) {
    int i;
    int itemsize = 0;
    int offset;
    char *ptr;

    itemsize = this->GetVarItemsize(name);

    for (i=0, ptr=(char *)dest; i<len; i++, ptr+=itemsize) {
      offset = inds[i] * itemsize;
      memcpy(ptr, (char *)src + offset, itemsize);
    }
  }
}


void BmiHeat::
SetValue (const char * name, void *src)
{
  void * dest = NULL;

  dest = this->GetValuePtr(name);

  if (dest) {
    int nbytes = 0;
    nbytes = this->GetVarNbytes(name);
    memcpy(dest, src, nbytes);
  }
}


void BmiHeat::
SetValueAtIndices (const char * name, int * inds, int len, void *src)
{
  void * dest = NULL;

  dest = this->GetValuePtr(name);

  if (dest) {
    int i;
    int itemsize = 0;
    int offset;
    char *ptr;

    itemsize = this->GetVarItemsize(name);

    for (i=0, ptr=(char *)src; i<len; i++, ptr+=itemsize) {
      offset = inds[i] * itemsize;
      memcpy((char *)dest + offset, ptr, itemsize);
    }
  }
}


void BmiHeat::
GetComponentName (char * name)
{
  strncpy(name, "The 2D Heat Equation", bmi::MAX_COMPONENT_NAME);
}


int BmiHeat::
GetInputItemCount()
{
  return this->input_var_name_count;
}


int BmiHeat::
GetOutputItemCount()
{
  return this->output_var_name_count;
}


void BmiHeat::
GetInputVarNames (char **names)
{
  for (int i=0; i<this->input_var_name_count; i++) {
    strncpy(names[i], (const char *)this->input_var_names[i], bmi::MAX_VAR_NAME);
  }
}


void BmiHeat::
GetOutputVarNames (char **names)
{
  for (int i=0; i<this->input_var_name_count; i++) {
    strncpy(names[i], (const char *)this->output_var_names[i], bmi::MAX_VAR_NAME);
  }
}


double BmiHeat::
GetStartTime () {
  return 0.;
}


double BmiHeat::
GetEndTime () {
  return this->_model.t_end;
}


double BmiHeat::
GetCurrentTime () {
  return this->_model.time;
}


void BmiHeat::
GetTimeUnits (char * units) {
  strncpy(units, "d", bmi::MAX_UNITS_NAME);
}


double BmiHeat::
GetTimeStep () {
  return this->_model.dt;
}
