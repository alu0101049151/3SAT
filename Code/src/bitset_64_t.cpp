#include "../include/bitset_64_t.hpp"



 /* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }


/* itoa:  convert n to characters in s */
 void itoa(unsigned long n, char s[],int base)
 {
     long i;

     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % base + '0';   /* get next digit */
     } while ((n /= base) > 0);     /* delete it */
     s[i] = '\0';
     reverse(s);
 }

	void bitset_64_t::build(void)
	{
		block_ = new block_t [sz_];
		memset(block_, ZERO_MASK, sz_ * sizeof(block_t));
	}

	void bitset_64_t::clean(void)
	{
		if (block_){
			delete [] block_;
			block_ = NULL;
		}
	}

	bitset_64_t::bitset_64_t(void) :
	block_(NULL),
	sz_(1)
	{
		build();
	}


	bitset_64_t::bitset_64_t(int sz) :
	block_(NULL),
	sz_((int) (ceil((double) (sz) / BITSET_BLOCK_SIZE)))
	{
		build();
	}


	bitset_64_t::bitset_64_t(const bitset_64_t& bs) :
	block_(NULL),
	sz_(bs.sz_)
	{
		block_ = new block_t [sz_];

		memcpy(block_, bs.block_, sz_ * sizeof(block_t));
	}


	int bitset_64_t::cardinality(void)
	{
		int card = 0;

		for(int i = 0; i < sz_; i++)
			card += __builtin_popcount(block_[i]);

		return card;
	}

	inline void bitset_64_t::clear(void) {
		memset(block_, ZERO_MASK, sz_ * sizeof(block_t));
	}

	bitset_64_t::~bitset_64_t(void) {
		clean();
	}

	void bitset_64_t::insert(int i) {
    //cambiar
    int n_bloque = i / BITSET_BLOCK_SIZE;
    int64_t mascara = ONE_MASK;
    if(n_bloque >= sz_)
    {
      std::cerr << "ERROR insert" << std::endl;
      return;
    }
    block_[n_bloque] |= mascara << (i % BITSET_BLOCK_SIZE);
    //set_bit_64(block_, i);
	}

	void bitset_64_t::insert(const bitset_64_t& bs) {

		block_t* b   = block_;
		block_t* bsb = bs.block_;

		for (int i = 0; i < sz_; i++){
			(*b) |= (*bsb);
			b ++;
			bsb ++;
		}
	}


	void bitset_64_t::remove(const bitset_64_t& bs) {

		block_t* b   = block_;
		block_t* bsb = bs.block_;

		for (int i = 0; i < sz_; i++){

			(*b) &= ~(*bsb);
			b ++;
			bsb ++;
		}
	}

	void bitset_64_t::remove(int i) {
    int n_bloque = i / BITSET_BLOCK_SIZE;
    int64_t mascara = ONE_MASK;
    if(n_bloque >= sz_)
    {
      std::cerr << "ERROR remove" << std::endl;
      return;
    }
    block_[n_bloque] &= ~(mascara << (i % BITSET_BLOCK_SIZE));
		//reset_bit_64(block_, i);
	}

	bool bitset_64_t::contains(int i) const{

    int n_bloque = i / BITSET_BLOCK_SIZE;
    int64_t mascara = ONE_MASK;
    if(n_bloque >= sz_)
    {
      std::cerr << "ERROR contains" << std::endl;
      return(false);
    }
    return block_[n_bloque] & (mascara << (i % BITSET_BLOCK_SIZE));
		//return test_bit_64(block_, i);
	}

	bool bitset_64_t::contains(const bitset_64_t& bs) const{

		block_t* b   = block_;
		block_t* bsb = bs.block_;

		bool contenido = true;

		for (int i = 0; (i < sz_) && (contenido); i++){

			contenido = (((*b) & (*bsb)) == (*bsb));
			b ++;
			bsb ++;
		}

		return contenido;
	}


	void bitset_64_t::op_intersec(const bitset_64_t& bs, bitset_64_t& result) const{

		result.clear();

		block_t* b   = block_;
		block_t* bsb = bs.block_;
		block_t* res = result.block_;

		for (int i = 0; i < sz_; i++){

			(*res) = (*b) & (*bsb);
			b ++;
			bsb ++;
			res ++;
		}
	}

	void bitset_64_t::op_union(const bitset_64_t& bs, bitset_64_t& result) const{

		result.clear();

		block_t* b   = block_;
		block_t* bsb = bs.block_;
		block_t* res = result.block_;

		for (int i = 0; i < sz_; i++){

			(*res) = (*b) | (*bsb);
			b ++;
			bsb ++;
			res ++;
		}
	}

	void bitset_64_t::op_minus(const bitset_64_t& bsj, bitset_64_t& result) const{
		result.clear();
		block_t aux;
		for (int i = 0; i < sz_; i++){

			aux = ~bsj.block_[i];
			result.block_[i] = (block_[i] & aux);
		}
	}

	//#ifdef _DEBUG
	std::ostream& bitset_64_t::write(ostream& os) const
  {
		const int bsz = sizeof(block_t) * 8;
		for (int i = 0; i < sz_; i++)
    {
			block_t aux = block_[i];
			for (int j = 0; (j < bsz) && (aux != 0); j++)
      {
				if ((aux & ONE_MASK) == ONE_MASK)
        {
					os << i * bsz + j;
					os << " ";
				}
				aux = aux >> 1;
			}
		}
    return(os);
	}
	//#endif

	bool bitset_64_t::operator==(bitset_64_t& bs) const{

		for (int i = 0; i < sz_; i++)
			if (block_[i] != bs.block_[i])
				return false;

		return true;
	}

  bool bitset_64_t::operator!=(bitset_64_t& bs) const{

		for (int i = 0; i < sz_; i++)
			if (block_[i] != bs.block_[i])
				return true;

		return false;
	}

	  const bitset_64_t& bitset_64_t::operator=(const bitset_64_t& bs) {

			sz_=bs.sz_;

			block_ = new block_t [sz_];
			memcpy(block_, bs.block_, sz_ * sizeof(block_t));

			return bs;
		}


    bitset_64_t bitset_64_t::operator&(const bitset_64_t &other) const
  	{
  		if(sz_ != other.sz_)
        std::cerr << "ERROR." << std::endl;

      bitset_64_t aux(sz_ * BITSET_BLOCK_SIZE);
      op_intersec(other, aux);
      return(aux);
  	}

    bitset_64_t bitset_64_t::operator|(const bitset_64_t &other) const
  	{
  		if(sz_ != other.sz_)
        std::cerr << "ERROR." << std::endl;

      bitset_64_t aux(sz_ * BITSET_BLOCK_SIZE);
      op_union(other, aux);
      return(aux);
  	}

    bitset_64_t bitset_64_t::operator^(const bitset_64_t &other) const
    {
      if(sz_ != other.sz_)
        std::cerr << "ERROR." << std::endl;

      bitset_64_t aux(sz_ * BITSET_BLOCK_SIZE);

      block_t* b   = block_;
      block_t* bsb = other.block_;
      block_t* res = aux.block_;

      for(int i = 0; i < sz_; i++)
      {
        (*res) = (*b) ^ (*bsb);
        b ++;
        bsb ++;
        res ++;
      }
      return(aux);
    }

    bitset_64_t& bitset_64_t::operator&=(const bitset_64_t &other)
    {
      (*this) = (*this) & other;
      return(*this);
    }

    bitset_64_t& bitset_64_t::operator|=(const bitset_64_t &other)
    {
      (*this) = (*this) | other;
      return(*this);
    }

    bitset_64_t& bitset_64_t::operator^=(const bitset_64_t &other)
    {
      (*this) = (*this) ^ other;
      return(*this);
    }

    bitset_64_t bitset_64_t::operator~(void) const
    {
      bitset_64_t aux(*this);

      block_t* res = aux.block_;

      for(int i = 0; i < sz_; i++)
      {
        (*res) = ~(*res);
        res ++;
      }

      return(aux);
    }

    bitset_64_t& bitset_64_t::operator++(void)
    {
      int index = 0;
      while(index < sz_ && ++block_[index++] == ZERO_MASK);
      return(*this);
    }

		bitset_64_t bitset_64_t::operator++(int)
    {
      bitset_64_t temp = *this;
      ++*this;
      return(temp);
    }

    bitset_64_t::operator bool() const
    {
      for(int i = 0; i < sz_; i++)
        if(block_[i])
          return(true);
      return(false);
    }
