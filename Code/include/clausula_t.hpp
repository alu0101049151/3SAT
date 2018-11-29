#pragma once

#include "bitset_64_t.hpp"
#include <set>
#include <vector>

class clausula_t
{
  private:
    bitset_64_t format_bitset_; // indica si las variables de la cláusula estan en formato directo o negadas (1 es directo y 0 inverso)
    bitset_64_t used_bitset_;   // indica las variables usadas en la cláusula (en formato bitset)
    std::set<int> used_set_;    // contiene las posiciones de los bits usados (las variables de la cláusula)
  public:
    // constructor por defecto de la cláusula
    clausula_t(void);
    // constructor al que se le indica el número de variables utilizadas (en el problema), las variables utilizadas en la cláusula y el formato
    clausula_t(int size, const std::vector<int> &bits, const std::vector<bool> &format);
    // constructor de copia
    clausula_t(const clausula_t &other);

    // destructor
    ~clausula_t(void);

    // retorna el número de variables de la cláusula
    int size(void) const;
    // retorna un vector que las posiciones de las variables utilizadas en la cláusula
    std::set<int> usados(void) const;
    // retorna el valor del bit situado en la posición indicada
    bool format(int index) const;
    // retorna true si la solución satisface la cláusula
    bool verifica(const bitset_64_t &sol) const;

    // escribe en el flujo de salida la clausula formateada
    std::ostream& write(std::ostream &os) const;

    // sobrecarga del operador del flujo de salida
    inline friend std::ostream& operator<<(std::ostream &os, const clausula_t &clausula)
    {
      return(clausula.write(os));
    }
};
