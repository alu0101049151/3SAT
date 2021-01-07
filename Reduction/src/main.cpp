
#include "sat.h"

const int ARG_REQUIRED = 2;
int main(int argc, char* argv[]) {
  if (argc == ARG_REQUIRED) {
    Sat sat(argv[1]);
    std::cout << sat; 
  } else {
    std::cout << "Modo de Uso: \n"
		    "./3Sat-Sat filename\n";
  }
}
