#pragma once

#include <cmath>
#include <cstdio>

#include <cassert>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdint>

// constantes para el formateo
#define IT_PER_LINE 8
#define WIDE_OUTPUT 9

using namespace std;

extern "C" void set_bit_64  (int64_t*, int i);
extern "C" void reset_bit_64(int64_t*, int i);
extern "C" bool test_bit_64 (int64_t*, int i);
extern "C" bool find_bit_64 (int64_t*, int* pos);


#define BITSET_BLOCK_SIZE 64	// tamaño del bloque
#define ONE_MASK 0x01					// máscara que contiene el número 1
#define ZERO_MASK 0x0					// máscara que solo contiene ceros

typedef int64_t block_t;

class bitset	_64_t {
  public:
		block_t* block_; // array de bloques que contendrán los bits
		int sz_;				 // tamaño del array de bloques

  public:
		// constructor por defecto
  	bitset_64_t(void);
		// constructor al que se le indica el número máximo de elementos
  	bitset_64_t(int max);
		// constructor de copia
  	bitset_64_t(const bitset_64_t& bs);

  	~bitset_64_t(void);

		// pone a 1 el indicado
  	void insert(int i);
		// pone a 1 todos los bits del bitset indicado
  	void insert(const bitset_64_t& bs);

		// pone a 0 el indicado
  	void remove(int i);
		// pone a 0 todos los bits del bitset indicado
  	void remove(const bitset_64_t& bs);

  	bool contains(int i) const;
  	bool contains(const bitset_64_t& a) const;

		// resetea todo el bitset
  	void clear(void);

		//** OPERADORES ALGEBRAICOS **//
		void op_intersec(const bitset_64_t& bsj, bitset_64_t& result) const;
  	void op_union   (const bitset_64_t& bsj, bitset_64_t& result) const;
  	void op_minus   (const bitset_64_t& bsj, bitset_64_t& result) const;

		// retorna un entero que indica cuantos elementos hay en el bitset
  	int cardinality(void);

		// función que vuelca los elementos del bitset en un flujo de salida
  	std::ostream& write(std::ostream&) const;

		/** OPERATORES DE IGUALDAD **/
  	bool operator==(bitset_64_t& bs) const;
    bool operator!=(bitset_64_t& bs) const;

		// operador de asignación
  	const bitset_64_t& operator=(const bitset_64_t& bs);

		/** OPERADORES LOGICOS **/
		//	and
    bitset_64_t operator&(const bitset_64_t &other) const;
		// or
    bitset_64_t operator|(const bitset_64_t &other) const;
		// xor
    bitset_64_t operator^(const bitset_64_t &other) const;

		/** OPERADORES LOGICOS DE ASIGNACIÓN **/
		// and igual
    bitset_64_t& operator&=(const bitset_64_t &other);
		// or igual
		bitset_64_t& operator|=(const bitset_64_t &other);
		// xor igual
		bitset_64_t& operator^=(const bitset_64_t &other);

		// operador que invierte todos los elementos del bitset
    bitset_64_t operator~(void) const;

		bitset_64_t& operator++(void);
		bitset_64_t operator++(int);

		// retorna true si el bitset contiene algun bit a 1
    operator bool() const;

		// sobrecarga del operador que formatea por el flujo de salida
    inline friend std::ostream& operator<<(std::ostream &os, const bitset_64_t &bitset)
    {
      return(bitset.write(os));
    }

  private:
		// reserva la memoria requerida por el bitset
  	void build(void);
		// libera la memoria del bitset
  	void clean(void);
};
