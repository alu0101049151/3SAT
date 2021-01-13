
#include "sat.h"

const int ARG_REQUIRED = 3;
int main(int argc, char *argv[])
{
  if (argc == ARG_REQUIRED)
  {
    Sat sat(argv[1]);
    std::cout << sat << std::endl;
    std::ofstream out_file(argv[2]);
    Sat *a = sat.to3Sat();
    a -> print(std::cout);
    a -> print(out_file);
  }
  else
  {
    std::cout << "Modo de Uso: \n"
                 "./3Sat-Sat filename out_filename\n";
  }
}
