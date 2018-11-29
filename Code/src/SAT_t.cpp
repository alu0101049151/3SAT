#include "../include/SAT_t.hpp"

SAT_t::SAT_t(void):
  clausulas_(),
  n_bits_(0)
  {}

SAT_t::SAT_t(int n_bits):
  clausulas_(),
  n_bits_(n_bits)
  {}


SAT_t::SAT_t(const SAT_t &other):
  clausulas_(other.clausulas_),
  n_bits_(other.n_bits_)
  {}

SAT_t::~SAT_t(void)
{}

bool SAT_t::verifica(const bitset_64_t &sol) const
{
  for(unsigned int i = 0; i < clausulas_.size(); i++)
    if(!clausulas_[i].verifica(sol))
      return(false);
  return(true);
}

SAT_t SAT_t::SAT23SAT(void) const
{
  //1 y las 4 combinaciones con otros 2
  //2 y las 2 combinaciones con un tercero
  //3 se deja igual
  //
  SAT_t _3sat(n_bits_);
  int iaux1, iaux2;
  std::vector<int> bits;
  std::vector<bool> format(3);
  if(n_bits_ < 3)
  {
    std::cerr << "ERROR: el número de variables del problema es menor que 3." << std::endl;
    return(_3sat);
  }
  for(const clausula_t &clausula : clausulas_)
  {
    bits.clear();

    if(clausula.size() <= 0)
    {
      std::cerr << "ERROR: el tamaño de una clausula es menor que 1." << std::endl;
      return(SAT_t());
    }
    else if(clausula.size() == 1)
    {
      iaux1 = *clausula.usados().begin();
      format[0] = clausula.format(iaux1);
      bits.push_back(iaux1);
      for(int i = 0; i < iaux1 && bits.size() < 3; i++)
        bits.push_back(i);
      for(int i = iaux1 + 1; i < n_bits_ && bits.size() < 3; i++)
        bits.push_back(i);

      format[1] = false; format[2] = false;
      _3sat.clausulas_.push_back(clausula_t(n_bits_, bits, format));

      format[1] = false; format[2] = true;
      _3sat.clausulas_.push_back(clausula_t(n_bits_, bits, format));

      format[1] = true; format[2] = false;
      _3sat.clausulas_.push_back(clausula_t(n_bits_, bits, format));

      format[1] = true; format[2] = true;
      _3sat.clausulas_.push_back(clausula_t(n_bits_, bits, format));

    }
    else if(clausula.size() == 2)
    {
      iaux1 = *clausula.usados().begin();
      iaux2 = *(++clausula.usados().begin());

      bits.push_back(iaux1);
      bits.push_back(iaux2);

      format[0] = clausula.format(iaux1);
      format[1] = clausula.format(iaux2);
      for(int i = 0; i < iaux1 && bits.size() < 3; i++)
        bits.push_back(i);
      for(int i = iaux1 + 1; i < iaux2 && bits.size() < 3; i++)
        bits.push_back(i);
      for(int i = iaux2 + 1; i < n_bits_ && bits.size() < 3; i++)
        bits.push_back(i);

      format[2] = false;
      _3sat.clausulas_.push_back(clausula_t(n_bits_, bits, format));

      format[2] = true;
      _3sat.clausulas_.push_back(clausula_t(n_bits_, bits, format));
    }
    else if(clausula.size() == 3)
    {
      _3sat.clausulas_.push_back(clausula);
    }
    else
    {
      std::vector<int> vector_u(clausula.size() - 3), vector_no_u(3);
      bits.resize(3);
      {
        std::set<int>::iterator it = clausula.usados().begin();
        for(int i = 0; i < 3; i++, it++)
          vector_no_u[i] = *it;
        for(unsigned int i = 0; i < vector_u.size(); i++, it++)
          vector_u[i] = *it;
      }
      //primera parte
      format[0] = clausula.format(vector_no_u[0]);
      format[1] = clausula.format(vector_no_u[1]);
      format[2] = clausula.format(vector_u[0]);

      bits[0] = vector_no_u[0];
      bits[1] = vector_no_u[1];
      bits[2] = vector_u[0];

      _3sat.clausulas_.push_back(clausula_t(n_bits_, bits, format));


//////////////////////////////

      for(int i = 0; i < clausula.size() - 4; i++)
      {
        format[0] = !clausula.format(vector_u[i]);

        iaux1 = (i == 2 ? vector_no_u[2] : ((unsigned int)(i + 2) >= vector_u.size() ? vector_no_u[(i + 2) % 3] : vector_u[i + 2]));
        //iaux1 = vector_no_u[(i + 2) % 3];
        format[1] = clausula.format(iaux1);
        format[2] = clausula.format(vector_u[i + 1]);

        bits[0] = vector_u[i];
        bits[1] = iaux1;
        bits[2] = vector_u[i + 1];

        _3sat.clausulas_.push_back(clausula_t(n_bits_, bits, format));

      }

//////////////////////////////

      //ultima parte
      format[0] = !clausula.format(vector_u[vector_u.size() - 1]);
      format[1] = clausula.format(vector_no_u[1]);
      format[2] = clausula.format(vector_no_u[2]);

      bits[0] = vector_u[vector_u.size() - 1];
      bits[1] = vector_no_u[1];
      bits[2] = vector_no_u[2];

      _3sat.clausulas_.push_back(clausula_t(n_bits_, bits, format));
    }
  }

  for(const clausula_t &clausula : _3sat.clausulas_)
    if(clausula.size() != 3)
      std::cerr << "ERROR CLAUSULA." << std::endl;
  return(_3sat);
}

std::ostream& SAT_t::write(std::ostream & os) const
{
  os << n_bits_ << std::endl;
  for(const clausula_t &clausula : clausulas_)
    os << clausula << std::endl;
  return(os);
}

std::istream& SAT_t::read(std::istream & is)
{
  int iaux1 = -1, iaux2 = -1;
  std::string line;
  is >> (int &) iaux1;
  if(iaux1 <= 0)
  {
    std::cerr << "ERROR: el número de bits no pueden ser menor o igual que 0." << std::endl;
    return(is);
  }
  n_bits_ = iaux1;
  clausulas_.clear();
  while(!is.eof())
  {
    std::getline(is, line);
    std::vector<int> bits;
    std::vector<bool> format;
    if(line != "")
    {
      std::istringstream buffer(line);
      while(!buffer.eof())
      {
        iaux1 = iaux2 = -1; //inicialización para que si en el fichero no hay nada de error
        ((std::istream &)(buffer)) >> (int &) iaux1 >> (int &) iaux2;
/*
        if(iaux1 <= 0)
        {
          std::cerr << "ERROR: el bit de la clausula no pueden ser menor o igual que 0." << std::endl;
          return(is);
        }
        */
        if(iaux2 != 0 && iaux2 != 1)
        {
          std::cerr << "ERROR: el formato del bit de la clausula debe ser 0 o 1." << std::endl;
          return(is);
        }
        bits.push_back(iaux1);
        format.push_back(iaux2);
      }
      clausulas_.push_back(clausula_t(n_bits_, bits, format));
    }
  }
  std::clog << clausulas_.size() << " clausulas leidas correctamente." << std::endl;
  return(is);
}
