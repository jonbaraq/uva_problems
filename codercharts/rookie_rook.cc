// http://www.codercharts.com/puzzle/rookie-rook

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

typedef long long int64;


int main(int argc, char** argv) {
  ifstream file(argv[1]);
  int number_cases;
  file >> number_cases;
  while (number_cases--) {
    map<int64, int> columns;
    map<int64, int> rows;
    int64 dimension, rooks;
    file >> dimension >> rooks;
    while (rooks--) {
      int64 x, y;
      file >> x >> y;
      rows[x] = 1;
      columns[y] = 1;
    }
    int64 rows_size = static_cast<int>(rows.size());
    int64 columns_size = static_cast<int>(columns.size());
    int64 number_squares = rows_size * dimension + (dimension - rows_size)
        * columns_size; 
    cout << number_squares << endl;
  }
}
