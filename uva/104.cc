#include <iostream>
#include <string>
#include <vector>

using namespace std;

void SolveProblem(vector<vector<vector<double> > >& currency_table,
    vector<vector<vector<int> > >& path_table) {
  // Floyd algorithm. O(N^4).
  for (int trades = 1; trades < currency_table.size(); ++trades) {
    for (int i = 0; i < currency_table.size(); ++i) {
      for (int j = 0; j < currency_table.size(); ++j) {
        for (int k = 0; k < currency_table.size(); ++k) {
          double value = currency_table[i][k][trades - 1] * 
            currency_table[k][j][0];
          if (value > currency_table[i][j][trades]) {
            // Update the value and path followed to get that value.
            currency_table[i][j][trades] = value;
            path_table[i][j][trades] = k;
          }
        }
      }
    }
  }

  double minimum_profit = 1.01;
  for (int trades = 1; trades < currency_table.size(); ++trades) {
    // We want to look for paths that go from origin to the same currency that 
    // has a profit larger than 1.01.
    for (int i = 0; i < currency_table.size(); ++i) {
      if (currency_table[i][i][trades] > minimum_profit) {
        // Now we need to reconstruct the path.
        vector<int> solution(trades + 1);
        solution[trades] = path_table[i][i][trades];
        for (int j = trades - 1; j >= 0; j--) {
          solution[j] = path_table[i][solution[j + 1]][j];
        }
        for (int j = 0; j < solution.size(); ++j) {
          cout << solution[j] + 1 << " ";
        }
        cout << solution[0] + 1 << endl;
        return;
      }
    }
  }

  cout << "no arbitrage sequence exists" << endl;
}

int main() {
  int currencies;
  while (cin >> currencies) {
    // Create 3D matrix to store from currency to currency using n currencies
    // what is the result.
    vector<vector<vector<double> > > dp_currency_table(
        currencies, vector<vector<double> >(
          currencies, vector<double>(currencies, 0.0)));
    vector<vector<vector<int> > > dp_path_table(
        currencies, vector<vector<int> >(currencies,
          vector<int>(currencies, 0)));
    for (int i = 0; i < currencies; ++i) {
      for (int j = 0; j < currencies; ++j) {
        // Shortest path from i to j in 0 trades is just i.
        dp_path_table[i][j][0] = i;
        if (i == j) {
          dp_currency_table[i][j][0] = 1.0;
          continue;
        }
        cin >> dp_currency_table[i][j][0];
      }
    }
    SolveProblem(dp_currency_table, dp_path_table);
  }
  return 0;
}
