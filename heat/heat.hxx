#ifndef HEAT_INCLUDED
#define HEAT_INCLUDED

#include <string>

namespace heat {
  class Heat {
    private:
      double alpha;

      double **temp_z;

      void _allocate_arrays();
      void _initialize_arrays(void);
      void _copy_metadata(const Heat &other);

    public:
      int shape[2];
      double spacing[2];
      double origin[2];
      double time;
      double t_end;
      double dt;
      double **z;

      Heat();
      Heat(std::string config_file);
      Heat(const Heat &other);
      Heat &operator=(Heat other);
      ~Heat();
      void finalize();
      void advance_in_time ();
  };
};

#endif
