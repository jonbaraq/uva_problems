#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// O(n^3) + O(n^2)
int GetMaxSum(const vector<vector<int> >& square) {
  int dimension = static_cast<int>(square.size());
  int possible_sums_per_row = dimension * (dimension + 1) / 2;
  // Calculate sums per row.
  // O(n^3)
  vector<vector<int> > row_sums(dimension, vector<int>(possible_sums_per_row));
  for (int row = 0; row < dimension; ++row) {
    int row_sum_index = 0;
    for (int origin = 0; origin < dimension; ++origin) {
      int sum = 0;
      for (int destination = origin; destination < dimension; ++destination) {
        sum += square[row][destination];
        row_sums[row][row_sum_index] = sum;
        ++row_sum_index;
      }
    }
  }

  int max_value = row_sums[0][0];
  // O(n^2)
  for (int index = 0; index < possible_sums_per_row; ++index) {
    int local_sum = 0;
    // O(n)
    for (int row = 0; row < dimension; ++row) {
      local_sum += row_sums[row][index];
      max_value = max(local_sum, max_value);
      if (local_sum < 0) {
        local_sum = 0;
      }
    }
  }
  return max_value;
}

int main() {
  int dimension;
  while (cin >> dimension, dimension) {
    vector<vector<int> > square(dimension, vector<int>(dimension));
    // Populate the square values.
    for (int i = 0; i < dimension; ++i) {
      for (int j = 0; j < dimension; ++j) {
        cin >> square[i][j];
      }
    }
    cout << GetMaxSum(square) << endl;
  }
}
