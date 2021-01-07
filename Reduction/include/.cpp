#include sat.h
 
Sat::Sat(std::string filename): {
  reader(filename);
}

void Sat::reader(std::string filename) {
 std::string aux = instance;
 std::size_t pos = aux.find("^");
 while (pos != std::string::npos) {
   pos = aux.find("^");
   clauses_.push_back(aux.substr(0,pos));
   instance.erase(0, pos);
 }
}

std::ostream& operator<<(std::ostream& os, Sat sat) {
  for (std::string clause : clasuses_) {
    std::cout << clause << " ^ ";
  }
  std::cout << "\n";
}

