#include <iostream>
#include <vector>

using namespace std;

void CalculatePaths(int origin, int step,
                    vector<vector<int> >& matrix,
                    vector<int>& path) {
  path[step] = origin;
  if (step == 8) {
    for (int i = 0; i < 9; ++i) {
      cout << path[i] + 1;
    }
    cout << endl;
  }

  for (int i = 0; i < 5; ++i) {
    if (matrix[origin][i]) {
      matrix[origin][i] = matrix[i][origin] = 0;
      CalculatePaths(i, step + 1, matrix, path);
      matrix[origin][i] = matrix[i][origin] = 1;
    }
  }
}

int main() {
  vector<vector<int> > matrix(5, vector<int>(5, 0));
  vector<int> path(9, 0);
  // Initialize matrix
  matrix[0][1] = matrix[0][4] = matrix[0][2] = 1;
  matrix[1][0] = matrix[4][0] = matrix[2][0] = 1;
  matrix[1][4] = matrix[1][2] = 1;
  matrix[4][1] = matrix[2][1] = 1;
  matrix[2][4] = matrix[2][3] = 1;
  matrix[4][2] = matrix[3][2] = 1;
  matrix[4][3] = matrix[3][4] = 1;

  CalculatePaths(0, 0, matrix, path);
}
