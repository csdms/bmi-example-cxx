#ifndef HEAT_INCLUDED
#define HEAT_INCLUDED

#include <string>
#include <vector>

namespace heat {
  class Heat {
    private:
      double alpha;

      std::vector<double> temp_z;

      void _initialize_arrays(void);

    public:
      int shape[2];
      double spacing[2];
      double origin[2];
      double time;
      double t_end;
      double dt;
      // Row-major temperatures with shape[1] columns
      std::vector<double> z;

      Heat();
      Heat(std::string config_file);
      void finalize();
      void advance_in_time ();
  };
};

#endif
