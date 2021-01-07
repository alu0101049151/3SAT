#ifndef SAT_H
#define SAT_H
 
#include<string>
#include<vector>

class Sat {
  public:
    Sat(std::string instance);
  private:
    std::vector<int> clauses_;
  
};
#endif // SAT_H

