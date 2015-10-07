#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int cases;
  cin >> cases;
  bool first = true;
  while (cases > 0) {
    string line;
    if (first) {
      first = false;
      getline(cin, line);
    }
    getline(cin, line);
    vector<int> weights;
    int total_weight = 0;
    istringstream iss(line);
    int weight;
    while (iss >> weight) {
      weights.push_back(weight);
      total_weight += weight;
    }
    int dp_size = 20 * weights.size() + 1;
    vector<bool> dp_weight(dp_size, false);
    dp_weight[0] = true;
    if (total_weight % 2 == 1) {
      cout << "NO" << endl;
      --cases;
      continue;
    }

    int goal = total_weight / 2;
    bool found = false;
    for (int i = 0; i < weights.size(); ++i) {
      vector<int> weights_to_add;
      for (int j = 0; j < dp_weight.size(); ++j) {
        int current_value = j + weights[i];
        if (dp_weight[j] && !dp_weight[current_value]) {
          weights_to_add.push_back(current_value);
          if (current_value == goal) {
            found = true;
          }
        }
      }
      if (found) {
        break;
      }
      for (int j = 0; j < weights_to_add.size(); ++j) {
        dp_weight[weights_to_add[j]] = true;
      }
    }

    if (found) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }

    --cases;
  }
  return 0;
}
