#include <iostream>
#include <vector>

using namespace std;

void PrintResults(const vector<bool>& v) {
  cout << 2;
  for (int i = 3; i < static_cast<int>(v.size()); i += 2) {
    if (v[i]) {
      cout << " " << i;
    }
  }
  cout << endl;
}

int main() {
  const int kLimit = 100001;
  vector<bool> result(kLimit, true);
  result[0] = false;
  result[1] = false;
  for (int i = 3; i*i < kLimit; i += 2) {
    if (!result[i]) {
      continue;
    }
    for (int j = i*i; j < kLimit; j += 2*i) {
      result[j] = false;
    }
  }
  PrintResults(result);
}
