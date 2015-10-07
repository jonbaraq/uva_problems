#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int main () {
  string input;
  char* cstr;
  while (cin >> input) {
    if (input == "#") {
      break;
    }
    cstr = new char [input.size()+1];
    strcpy(cstr, input.c_str());
    if (next_permutation(cstr, cstr + input.size())) {
      cout << cstr << endl;
    } else {
      cout << "No Successor" << endl;
    }
  }
}
