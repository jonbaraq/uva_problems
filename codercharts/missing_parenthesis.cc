// http://www.codercharts.com/puzzle/missing-parenthesis

#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

int GetResult(const int a, const int b, const char x) {
  if (x == '+') {
    return a + b;
  }
  if (x == '-') {
    return a - b;
  }
  if (x == '*') {
    return a * b;
  }
}

int GetHighestResult(const int a, const int b, const int c,
                     const char x, const char y) {
  int result1 = GetResult(GetResult(a, b, x), c, y);
  int result2 = GetResult(a, GetResult(b, c, y), x);
  return max(result1, result2);
}

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  int operations;
  file >> operations;
  while (operations--) {
    int a, b, c;
    char x, y;
    file >> a >> x >> b >> y >> c;
    cout << GetHighestResult(a, b, c, x, y) << endl;
  }
}
