#include "../include/clausula_t.hpp"

clausula_t::clausula_t(void):
  format_bitset_(),
  used_bitset_(),
  used_set_()
  {}

clausula_t::clausula_t(int size, const std::vector<int> &bits, const std::vector<bool> &format):
  format_bitset_(size),
  used_bitset_(size),
  used_set_()
  {
    for(unsigned int i = 0; i < bits.size(); i++)
    {
      used_set_.insert(bits[i]);
      used_bitset_.insert(bits[i]);
      //formato
      if(format[i])
        format_bitset_.insert(bits[i]);
    }
  }

clausula_t::clausula_t(const clausula_t &other):
  format_bitset_(other.format_bitset_),
  used_bitset_(other.used_bitset_),
  used_set_(other.used_set_)
  {}

clausula_t::~clausula_t(void)
{}

int clausula_t::size(void) const
{
  return(used_set_.size());
}

std::set<int> clausula_t::usados(void) const
{
  return(used_set_);
}

bool clausula_t::format(int index) const
{
  return(format_bitset_.contains(index));
}

bool clausula_t::verifica(const bitset_64_t &sol) const
{
  return((~(sol ^ format_bitset_)) & used_bitset_);
}

std::ostream& clausula_t::write(std::ostream &os) const
{
  for(const int &x : used_set_)
  {
    os << x << " " << format_bitset_.contains(x) << " ";
  }
  return(os);
}
