#ifndef SAT_H
#define SAT_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Sat {
 private:
  std::vector<std::vector<std::string>> clauses_;
  int newVarCount = 1;

 public:
  Sat() {}
  Sat *to3Sat();
  std::string genNewVar();
  Sat(std::string filename);
  void reader(std::string filename);
  std::ostream& print(std::ostream &os);
  std::string cleanUpString(std::string input);
  friend std::ostream &operator<<(std::ostream &os, Sat sat);
  void convertTo3Clause(std::vector<std::string>);
  /*inline void addClause(std::vector<std::string> newClause) {
    clauses_.push_back(newClause);
  }*/
  inline std::vector<std::vector<std::string>> getClauses() { return clauses_; }
};

#endif  // SAT_H