#pragma once

#include <unordered_map>
#include "cube.hpp"
#include "keyhasher.hpp"

// unordered map representing a chain of cubes.
// recall that a chain is c = a_1C_1 + a_2C_1 + ... + a_nC_n,
// where a_i are integers and C_i is a representation of a
// cube.
// so if K_i is the geometric cube that C_i represents, we have
// C_i(K_i) = 1, and C_i(K_j) = 0 for j != i. 
// the chain then stores the coefficients a_i as values.
typedef std::unordered_map<Cube, int, KeyHasher> Chain;
