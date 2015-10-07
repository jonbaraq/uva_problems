// http://www.codercharts.com/puzzle/magic-words

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string GetBestScoreArray(const string& input) {
  int size = static_cast<int> (input.size());
  string result = input;
  vector<bool> visited(size, false);
  int number_swaps = size / 2;
  while (number_swaps > 0) {
    int max_value = -1;
    int min_value = 1000;
    int position_max = -1;
    int position_min = -1;
    for (int i = 0; i < size; ++i) {
      if (static_cast<int>(input[i]) > max_value and not visited[i]) {
        max_value = static_cast<int> (input[i]);
        position_max = i;
      }
      if (min_value > static_cast<int>(input[i]) and not visited[i]) {
        min_value = static_cast<int>(input[i]);
        position_min = i;
      }
    }
    char tmp = input[position_min];
    result[position_min] = input[position_max];
    result[position_max] = tmp;
    visited[position_min] = true;
    visited[position_max] = true;
    --number_swaps;
  }
  return result;
}

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  string line;
  while (getline(file, line)) {
    istringstream iss(line);
    string word;
    for (bool start = true; iss >> word; start = false) {
      cout << (start ? "" : " ");
      int size = static_cast<int> (word.size());
      if (size > 3) {
        cout << word[0];
        cout << GetBestScoreArray(word.substr(1, size - 2));
        cout << word[size - 1];
      } else {
        cout << word;
      }
    }
    cout << endl;
  }
}
