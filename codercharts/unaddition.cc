// http://codercharts.com/puzzle/unaddition

#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

typedef unsigned long long uint64;

using namespace std;

struct BitOperation {
  bool previous_carry;
  uint64 summand1;
  uint64 summand2;
};

bool IsThisValid(int bit_summand1, int bit_summand2, int new_carry,
                 int bit_dad, int bit_daughter, bool previous_carry) {
  return (bit_summand1 + bit_summand2 + new_carry) % 2 == (bit_dad != 0) &&
      (bit_summand1 ^ bit_summand2) == (bit_daughter != 0) &&
      ((previous_carry && bit_summand1 + bit_summand2 + new_carry > 1) ||
       (!previous_carry && bit_summand1 + bit_summand2 + new_carry < 2));
}

void UpdateValues(uint64 tmp_value, int bit_dad, int bit_daughter,
                  vector<BitOperation>* bitOperations) {
  vector<BitOperation> newBitOperations;
  BitOperation tmp;
  for (int i = 0; i < static_cast<int>(bitOperations->size()); ++i) {
    const BitOperation& bit = (*bitOperations)[i];
    for (int j = 0; j <= 1; ++j) {
      for (int k = 0; k <= 1; ++k) {
        for (int l = 0; l <= 1; ++l) {
          if (IsThisValid(j, k, l, bit_dad, bit_daughter, bit.previous_carry)) {
            tmp.previous_carry = l;
            tmp.summand1 = bit.summand1 + tmp_value * j;
            tmp.summand2 = bit.summand2 + tmp_value * k;
            newBitOperations.push_back(tmp);
          }
        }
      }
    }
  }

  uint64 min_value_no_carry = 0xFFFFFFFFFFFFFFFF;
  uint64 min_value_carry = 0xFFFFFFFFFFFFFFFF;
  BitOperation min_no_carry;
  BitOperation min_carry;
  vector<BitOperation> tmp_result;
  for (int i = 0; i < static_cast<int>(newBitOperations.size()); ++i) {
    uint64 max_value = max(newBitOperations[i].summand1,
                           newBitOperations[i].summand2);
    uint64 min_value = min(newBitOperations[i].summand1,
                           newBitOperations[i].summand2);
    newBitOperations[i].summand1 = max_value;
    newBitOperations[i].summand2 = min_value;
    uint64 difference = max_value - min_value;
    if (newBitOperations[i].previous_carry && difference < min_value_no_carry) {
      min_value_no_carry = max_value - min_value;
      min_no_carry = newBitOperations[i];
    } else if (!newBitOperations[i].previous_carry &&
               difference < min_value_carry) {
      min_value_carry = max_value - min_value;
      min_carry = newBitOperations[i];
    }
  }
  if (min_value_no_carry < 0xFFFFFFFFFFFFFFFF) {
    tmp_result.push_back(min_no_carry);
  }
  if (min_value_carry < 0xFFFFFFFFFFFFFFFF) {
    tmp_result.push_back(min_carry);
  }
  *bitOperations = tmp_result;
}

int log_2(uint64 a) {
  int p = 0;
  while (a) {
    a /= 2;
    ++p;
  }
  return p;
}

BitOperation CalculateSolution(uint64 a, uint64 b) {
  int power = log_2(a) - 1;
  vector<BitOperation> bitOperations;
  uint64 tmp_value = (1ull << power);
  int bit_a, bit_b;
  BitOperation bit;
  bit.previous_carry = 0;
  bit.summand1 = 0;
  bit.summand2 = 0;
  bitOperations.push_back(bit);
  for (int i = power; i >= 0; --i) {
    tmp_value = (1ull << i);
    UpdateValues(tmp_value, (a & tmp_value) != 0,
                 (b & tmp_value) != 0, &bitOperations);
  }
  BitOperation min;
  for (int i = 0; i < static_cast<int>(bitOperations.size()); ++i) {
    if (!bitOperations[i].previous_carry) {
      min = bitOperations[i];
    }
  }
  return min;
}

void PrintResult(uint64 dad_value, uint64 daughter_value) {
  BitOperation solution = CalculateSolution(dad_value, daughter_value);
  cout << solution.summand1 << " " << solution.summand2 << endl;
}

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  int lines;
  file >> lines;
  while (lines--) {
    uint64 dad_value, daughter_value;
    file >> dad_value >> daughter_value;
    PrintResult(dad_value, daughter_value);
  }
}
