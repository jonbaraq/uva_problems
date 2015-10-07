// http://www.codercharts.com/puzzle/fast-grep

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
  string word = argv[1];
  ifstream file(argv[2]);
  string line;
  int line_number = 1;
  bool found = false;
  while (file >> line) {
    if (line == word) {
      cout << line_number << endl;
      found = true;
      break;
    }
    ++line_number;
  }
  if (!found) {
    cout << 0 << endl;
  }
}
