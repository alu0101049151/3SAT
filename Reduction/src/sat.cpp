#include "sat.h"

const char OR = 'v';
const char AND = '^';
const char SPACE = ' ';
const char PARENTH_OPEN = '(';
const char PARENTH_CLOSE = ')';

Sat::Sat(std::string filename) { reader(filename); }

void Sat::reader(std::string filename) {
  std::ifstream file_instance(filename);
  std::vector<std::string> clause;
  std::string parsed, parsed2, input;
  if (file_instance.is_open()) {
    getline(file_instance, input);
    input = cleanUpString(input);
    std::stringstream ss(input);
    while (getline(ss, parsed, AND)) {
      std::stringstream ss2(parsed);
      while (getline(ss2, parsed2, OR)) clause.push_back(parsed2);
      clauses_.push_back(clause);
      clause.clear();
    }
  }
}

std::string Sat::cleanUpString(std::string input) {
  input.erase(std::remove(input.begin(), input.end(), PARENTH_OPEN),
              input.end());
  input.erase(std::remove(input.begin(), input.end(), PARENTH_CLOSE),
              input.end());
  input.erase(std::remove(input.begin(), input.end(), SPACE), input.end());
  return input;
}

std::ostream &Sat::print(std::ostream &os) {
  for (int clause = 0; clause < getClauses().size() - 1; clause++){
    os << "(";
    for (int member = 0; member < getClauses()[clause].size() - 1; member++) {
      os << getClauses()[clause][member] << " v ";
    }
    os << getClauses()[clause][getClauses()[clause].size() - 1];
    os << ") ^ ";
  }
  os << "(";
  std::vector<std::string> lastClause = getClauses()[getClauses().size() - 1];
  for(int member = 0; member < lastClause.size() - 1; member++) {
      os << lastClause[member] << " v ";
  }

  os << lastClause[lastClause.size() - 1];
  os << ")\n";
  return os;
}

std::ostream &operator<<(std::ostream &os, Sat sat) {
  sat.print(os);
  return os;
}

std::string Sat::genNewVar() {
  newVarCount++;
  return "z" + std::to_string(newVarCount - 1);
}

Sat *Sat::to3Sat() {
  Sat *threeSat = new Sat();
  std::vector<std::string> newClause;

  for (auto clause : clauses_) {
    threeSat->convertTo3Clause(clause);
  }
  return threeSat;
}

std::string changeSign(std::string var) {
  if (var[0] == '!') {
    return var.substr(1);
  } else
    return ("!" + var);
}

void Sat::convertTo3Clause(std::vector<std::string> oldClause) {
  std::vector<std::string> newClause;
  switch (oldClause.size()) {
    case 1: {
      std::string newVar1 = genNewVar();
      std::string newVar2 = genNewVar();
      newClause.push_back(oldClause[0]);
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          newClause.push_back(newVar1);
          newClause.push_back(newVar2);
          newVar2 = changeSign(newVar2);
          clauses_.push_back(newClause);
          newClause.clear();
          newClause.push_back(oldClause[0]);
        }
        newVar1 = changeSign(newVar1);
      }
    } break;
    case 2: {
      std::string newVar1 = genNewVar();
      newClause = oldClause;
      for (int i = 0; i < 2; i++) {
        newClause.push_back(newVar1);
        clauses_.push_back(newClause);
        newClause.clear();
        newClause = oldClause;
        newVar1 = changeSign(newVar1);
      }
    } break;
    case 3:
      clauses_.push_back(oldClause);
      break;
    default: {
      std::string lastVar = genNewVar();
      // hacer la primera
      newClause.push_back(oldClause[0]);
      newClause.push_back(oldClause[1]);
      newClause.push_back(lastVar);
      clauses_.push_back(newClause);
      // hacer el for
      for(int i = 2; i < oldClause.size() - 2; i++) {
        newClause.clear();
        lastVar = changeSign(lastVar);
        newClause.push_back(oldClause[i]);
        newClause.push_back(lastVar);
        lastVar = genNewVar();
        newClause.push_back(lastVar);
        clauses_.push_back(newClause);
      }
      // hacer la ultima
      newClause.clear();
      newClause.push_back(oldClause[oldClause.size() - 2]);
      newClause.push_back(oldClause[oldClause.size() - 1]);
      newClause.push_back(changeSign(lastVar));
      clauses_.push_back(newClause);
    }
    break;
  }
}
