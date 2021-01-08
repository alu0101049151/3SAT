#include "sat.h"

Sat::Sat(std::string filename) {
  reader(filename);
}

void Sat::reader(std::string filename) {
 std::ifstream file_instance(filename);
 if (file_instance.is_open()) {
  std::string instance;
  std::string aux;
  while (std::getline(file_instance, aux)) {
    instance += aux;
  }
  aux = instance;
aux.erase(remove_if(aux.begin(), aux.end(), isspace), aux.end());
  std::size_t pos = aux.find("^");
  std::string clause = aux.substr(0, pos);
  while (pos != std::string::npos) {
    std::size_t ppos = aux.find("(");
    if (ppos != std::string::npos) {
      aux.erase(ppos, 1);
      ppos = aux.find(")");
      aux.erase(ppos, 1);
    }
    clause = removeDisjunction(clause);
    clauses_.push_back(clause);
    aux.erase(0, pos + 1);
    pos = aux.find("^");
    clause = aux.substr(0, pos);
  }
  clauses_.push_back(aux);
 }
}

std::string Sat::removeDisjunction(std::string clause) {
  std::string aux = clause;
  std::size_t pos = aux.find('v');
  while(pos != std::string::npos) {
    aux.erase(pos, 1);
    pos = aux.find('v');
  }
  return aux;
}

std::ostream& operator<<(std::ostream& os, Sat sat) {
  for (std::string clause : sat.getClauses()) {
    os << clause << "\n";
  }
  os << "\n";
  return os;
}

 Sat* Sat::to3Sat() {
  return this;
 }

