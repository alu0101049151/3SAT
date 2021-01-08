#ifndef SAT_H
#define SAT_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

class Sat
{
private:
   std::vector<std::vector<std::string>> clauses_;

public:
   Sat(std::string filename);
   void reader(std::string filename);
   friend std::ostream &operator<<(std::ostream &os, Sat sat);
   std::vector<std::vector<std::string>> getClauses() { return clauses_; };
   std::vector<std::string> removeDisjunction(std::string clause);
   Sat *to3Sat();
};

#endif // SAT_H