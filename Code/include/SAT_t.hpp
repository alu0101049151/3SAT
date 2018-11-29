#pragma once
#include <sstream>
#include <iterator>
#include "clausula_t.hpp"

class SAT_t
{
  private:
    // vector que contendrá las cláusulas del problema
    std::vector<clausula_t> clausulas_;
    // número de bits de los bitsets de las cláusulas (el número de variables diferentes utilizables en el problema)
    int n_bits_;
  public:
    // constructor por defecto que construye un problema sin cláusulas y con 0 variables
    SAT_t(void);
    // constructor al que se le indica el número de variables que tiene el problema
    SAT_t(int n_bits);
    // constructor de copia (construye un problema exactamente igual a otro pasado por referencia)
    SAT_t(const SAT_t &other);
    // destructor
    ~SAT_t(void);

    // funcion que retorna true si la solucion pasada por referencia satisface el problema planteado
    bool verifica(const bitset_64_t &sol) const;

    // función que retorna un problema 3SAT basandose en un SAT
    SAT_t SAT23SAT(void) const;

    // función que lee del flujo de entrada un problema SAT correctamente formateado
    std::istream& read(std::istream & is);

    // función que escribe en el flujo de salida un problema SAT correctamente formateado
    std::ostream& write(std::ostream & os) const;

    // sobrecarga del operador del flujo de entrada
    inline friend std::istream& operator>>(std::istream &is, SAT_t &problem)
    {
      return(problem.read(is));
    }

    // sobrecarga del operador del flujo de salida
    inline friend std::ostream& operator<<(std::ostream &os, const SAT_t &problem)
    {
      return(problem.write(os));
    }

};
