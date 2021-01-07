#ifndef SAT_H
#define SAT_H
 
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

class Sat
{
   public:
      Sat(std::string filename);
      void reader(std::string filename);
      friend std::ostream& operator<<(std::ostream& os, Sat sat);
      std::vector<std::string> getClauses() { return clauses_; };
   private:
      std::vector<std::string> clauses_;
};
#endif // SAT_H

