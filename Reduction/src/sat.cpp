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
  while (pos != std::string::npos) {
    pos = aux.find("^");
    std::size_t ppos = aux.find("(");
    if (ppos != std::string::npos) {
      aux.erase(ppos, 1);
      ppos = aux.find(")");
      aux.erase(ppos, 1);
    }
    clauses_.push_back(aux.substr(0,pos));
    aux.erase(0, pos + 1);
  }
 }
}

std::ostream& operator<<(std::ostream& os, Sat sat) {
  for (std::string clause : sat.getClauses()) {
    os << clause << "\n";
  }
  os << "\n";
  return os;
}


