#include "sat.h"

const char OR = 'v';
const char AND = '^';
const char PARENTH_OPEN = '(';
const char PARENTH_CLOSE = ')';

Sat::Sat(std::string filename)
{
  reader(filename);
}

void Sat::reader(std::string filename)
{
  std::ifstream file_instance(filename);
  if (file_instance.is_open())
  {
    std::string instance;
    std::string aux;
    while (std::getline(file_instance, aux))
    {
      instance += aux;
    }
    aux = instance;
    aux.erase(remove_if(aux.begin(), aux.end(), isspace), aux.end());
    std::size_t pos = aux.find(AND);
    std::string clause = aux.substr(0, pos);
    while (pos != std::string::npos)
    {
      std::size_t ppos = aux.find(PARENTH_OPEN);
      if (ppos != std::string::npos)
      {
        aux.erase(ppos, 1);
        ppos = aux.find(PARENTH_CLOSE);
        aux.erase(ppos, 1);
      }
      clauses_.push_back(removeDisjunction(clause));
      aux.erase(0, pos + 1);
      pos = aux.find(AND);
      clause = aux.substr(0, pos);
    }
    clauses_.push_back(removeDisjunction(clause));
  }
}

std::vector<std::string> Sat::removeDisjunction(std::string clause)
{
  std::string aux = clause;
  std::size_t pos = aux.find(OR);
  std::vector<std::string> tokenizedClause;
  while (pos != std::string::npos)
  {
    tokenizedClause.push_back(aux.substr(0, pos));
    aux.erase(0, pos + 1);
    pos = aux.find(OR);
  }
  tokenizedClause.push_back(aux);
  return tokenizedClause;
}

std::ostream &operator<<(std::ostream &os, Sat sat)
{
  for (auto clause : sat.getClauses())
  {
    for (auto member : clause)
    {
      os << member << " ";
    }
    os << "\n";
  }
  return os;
}

Sat *Sat::to3Sat()
{
  return this;
}