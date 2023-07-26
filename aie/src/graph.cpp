#include "graph.h"

TopGraph mult_graph;

#if defined(__AIESIM__) || defined(__X86SIM__)
   int main(int argc, char ** argv)
   {
      mult_graph.init();
      mult_graph.run(280);
      mult_graph.end();

      return 0;
   }
#endif
