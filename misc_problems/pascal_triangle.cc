#include <iostream>
#include <vector>

using namespace std;

void PrintVector(const vector<int>& v) {
  cout << v[0];
  for (int i = 1; i < static_cast<int>(v.size()); ++i) {
    cout << " " << v[i];
  }
  cout << endl;
}

int main() {
  const int kNumberLines = 10;
  vector<int> previous_line(1, 1);
  PrintVector(previous_line);
  for (int i = 1; i < kNumberLines; ++i) {
    vector<int> present_line(i + 1, 1);
    for (int j = 1; j < i; ++j) {
      present_line[j] = previous_line[j] + previous_line[j - 1];
    }
    PrintVector(present_line);
    previous_line = present_line;
  }
}
