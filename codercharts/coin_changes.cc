// http://codercharts.com/puzzle/coin-changes

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int GetNumberWays(vector<vector<int> >* table, const vector<int>& coins,
                  const int number) {
  int number_coins = static_cast<int>(coins.size());
  if (number == 0) {
    return 1;
  }
  if (number < 0) {
    return 0;
  }
  int size = static_cast<int>(table->size());
  while (number >= size) {
    table->push_back(vector<int>(4, 0));
    for (int j = 0; j < number_coins; ++j) {
      if (size - coins[j] >= 0) {
        (*table)[size][j] += (*table)[size - coins[j]][j];
      }
      if (j - 1 >= 0) {
        (*table)[size][j] += (*table)[size][j - 1];
      }
    }
    ++size;
  }
  return (*table)[number][number_coins - 1];
}

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  int number;
  vector<int> coins(4);
  coins[0] = 1;
  coins[1] = 5;
  coins[2] = 10;
  coins[3] = 25;
  vector<vector<int> > table(1, vector<int>(4, 1));
  while (file >> number) {
    cout << GetNumberWays(&table, coins, number) << endl;
  }
}
