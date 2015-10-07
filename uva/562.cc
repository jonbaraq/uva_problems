#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int cases;
  cin >> cases;
  while (cases > 0) {
    int coins;
    cin >> coins;
    // Maximum we will be able to add up to 500 * 100 EUR. 100 coins max value 
    // 500.
    vector<bool> dp_table(50001, false);
    vector<int> coin_types(coins, 0);
    // If we don't use any coint we sum 0.
    dp_table[0] = true;
    int total_value = 0;
    for (int i = 0; i < coins; ++i) {
      int coin;
      cin >> coin_types[i];
      total_value += coin_types[i];
    }

    int goal = total_value / 2;
    int current_diff = goal;
    int current_value = 0;
    int value = 0;
    bool found = false;
    for (int i = 0; i < coin_types.size(); ++i) {
      vector<int> values_to_add;
      for (int j = 0; j < dp_table.size(); ++j) {
        current_value = j + coin_types[i];
        if (dp_table[j] && !dp_table[current_value]) {
          values_to_add.push_back(current_value);
          if (current_diff > abs(goal - current_value)) {
            current_diff = abs(goal - current_value);
            value = current_value;
            if (current_diff == 0) {
              found = true;
            }
          }
        }
      }
      for (int j = 0; j < values_to_add.size(); ++j) {
        dp_table[values_to_add[j]] = true;
      }
      if (found) {
        break;
      }
    }

    int difference = abs(total_value - 2 * value);
    cout << difference << endl;
    --cases;
  }
  return 0;
}
