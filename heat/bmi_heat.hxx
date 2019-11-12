#ifndef BMI_HEAT_H_INCLUDED
#define BMI_HEAT_H_INCLUDED

#include <string>

#include <bmi.hxx>
#include "heat.hxx"


class BmiHeat : public bmi::Bmi {
  public:
    BmiHeat() {
      this->input_var_names[0] = "plate_surface__temperature";
      this->output_var_names[0] = "plate_surface__temperature";
    };

    void Initialize (std::string config_file);
    void Update();
    void UpdateUntil(double time);
    void Finalize();

    void GetComponentName(char *name);
    int GetInputItemCount();
    int GetOutputItemCount();
    void GetInputVarNames(char **names);
    void GetOutputVarNames(char **names);

    int GetVarGrid(const char *name);
    void GetVarType(const char *name, char *type);
    int GetVarItemsize(const char *name);
    void GetVarUnits(const char *name, char *units);
    int GetVarNbytes(const char *name);
    void GetVarLocation(const char *name, char *location);

    double GetCurrentTime();
    double GetStartTime();
    double GetEndTime();
    void GetTimeUnits(char *units);
    double GetTimeStep();

    void GetValue(const char *name, void *dest);
    void *GetValuePtr(const char *name);
    void GetValueAtIndices(const char *name, void *dest, int *inds, int count);

    void SetValue(const char *name, void *src);
    void SetValueAtIndices(const char *name, int *inds, int len, void *src);

    int GetGridRank(const int grid);
    int GetGridSize(const int grid);
    void GetGridType(const int grid, char *type);

    void GetGridShape(const int grid, int *shape);
    void GetGridSpacing(const int grid, double *spacing);
    void GetGridOrigin(const int grid, double *origin);

    void GetGridX(const int grid, double *x);
    void GetGridY(const int grid, double *y);
    void GetGridZ(const int grid, double *z);

    int GetGridNodeCount(const int grid);
    int GetGridEdgeCount(const int grid);
    int GetGridFaceCount(const int grid);

    void GetGridEdgeNodes(const int grid, int *edge_nodes);
    void GetGridFaceEdges(const int grid, int *face_edges);
    void GetGridFaceNodes(const int grid, int *face_nodes);
    void GetGridNodesPerFace(const int grid, int *nodes_per_face);

  private:
    heat::Heat _model;
    static const int input_var_name_count = 1;
    static const int output_var_name_count = 1;

    const char* input_var_names[2];
    const char* output_var_names[2];
};

#endif
