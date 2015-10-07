#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Position {
  int x;
  int y;
  Position(int x, int y) : x(x), y(y) {}
};

int GetDistance(const Position& a, const Position& b) {
  return max(abs(a.x - b.x), abs(a.y - b.y));
}

int CalculateDistance(const vector<Position>& nuts,
                      int position, int visited, vector<vector<int> >* cache) {
  // If all nuts have been visited return the distance to larry.
  if (visited == ((1 << cache->size()) - 1)) {
    return GetDistance(nuts[position], nuts[0]);
  }

  // If the result is contained on the cache. Just return.
  if ((*cache)[position][visited] < 10000) {
    return (*cache)[position][visited];
  }

  int minimum_distance = 10000;
  for (int i = 0; i < cache->size(); ++i) {
    // If not visited.
    if (((visited >> i) & 1) == 0) {
      minimum_distance = min(minimum_distance,
          GetDistance(nuts[position], nuts[i]) +
          CalculateDistance(nuts, i, visited | (1 << i), cache));
    }
  }

  (*cache)[position][visited] = minimum_distance;
  return minimum_distance;
}

void SolveProblem(const vector<Position>& nuts) {
  vector<vector<int> > cache(nuts.size(), vector<int>(pow(2, nuts.size()), 10000));
  cout << CalculateDistance(nuts, 0, 0, &cache) << endl;
}

int main() {
  int rows, columns;
  while (cin >> rows >> columns) {
    vector<Position> nuts;
    Position larry(0, 0);
    // Put larry on the first position of the vector.
    nuts.push_back(larry);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        char tmp;
        cin >> tmp;
        if (tmp == '#') {
          Position nut(i, j);
          nuts.push_back(nut);
        } else if (tmp == 'L') {
          Position tmp_larry(i, j);
          larry = tmp_larry;
        }
      }
    }
    // Override larry with the right position.
    nuts[0] = larry;
    SolveProblem(nuts);
  }
  return 0;
}
