
#include "sat.h"

const int ARG_REQUIRED = 2;
int main(int argc, char *argv[])
{
  if (argc == ARG_REQUIRED)
  {
    Sat sat(argv[1]);
    std::cout << sat << std::endl;
    Sat *a = sat.to3Sat();
    a -> print(std::cout);
  }
  else
  {
    std::cout << "Modo de Uso: \n"
                 "./3Sat-Sat filename\n";
  }
}
