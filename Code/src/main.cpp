#include "../include/SAT_t.hpp"
#define N_BITS 8  // número de variables del problema
#include <ctime>

// comprueba todas las combinaciones para el problema planteado
// las compara para SAT y 3SAT y muestra por pantalla las conclusiones
int main(void)
{
  clock_t start = clock(), stop;
  {
    int count_fail = 0, count = 0, other_count = 0, count_sol = 0;
    SAT_t sat;
    std::cin >> (SAT_t &) sat;
    std::cout << sat << std::endl;

    bitset_64_t sol, last;
    for(int i = 0; i < N_BITS; i++)
      last.insert(i);

    SAT_t sat3 = sat.SAT23SAT();
    std::cout << sat3 << std::endl;
    while(last != sol)
    {
      count++;
      if(sat.verifica(sol) != sat3.verifica(sol))
        ++count_fail;
      if(sat.verifica(sol))
        count_sol++;
      if(!sat3.verifica(sol) && sat.verifica(sol))
      {
        other_count++;
        --count_fail;
      }
      ++sol;
    }

    if(!sat3.verifica(sol) && sat.verifica(sol))
      --count_fail;
    if(sat.verifica(sol) != sat3.verifica(sol))
      ++count_fail;
    stop = clock();
    std::cout << (count_fail == 0 ? "TODO CORRECTO" : ("FALLOS: " + std::to_string(count_fail))) << std::endl;
    std::cout << "Número de iteraciones: " << count << std::endl;
    std::cout << "Soluciones del SAT pero no del 3SAT: " << other_count << std::endl;
    std::cout << "Soluciones del SAT: " << count_sol << std::endl;
    std::cout << "Time: " << (((float)(stop - start)) / CLOCKS_PER_SEC) << std::endl;
  }
}
